#!/usr/bin/env python3
"""
Symbolic Bitcoin Proof-of-Work resolver using Z3 bit-vector constraint solving.

Uses a cascading structural approach: soft assertions, custom tactic pipeline,
and progressive fallback slices/anchors to steer Z3 toward a valid nonce under
live network difficulty (header bits field).
"""
import sys
import argparse
import binascii
import hashlib
import time

try:
    from z3 import (
        BitVec, BitVecVal, Concat, Extract,
        LShR, RotateRight,
        Optimize, Goal, Then, Tactic, With,
        sat
    )
except ImportError:
    print("Error: z3-solver is required. Install via 'pip install z3-solver'.")
    sys.exit(1)

# SHA-256 constants
K = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
]

def rotr(x, n):
    return RotateRight(x, n)

def shr(x, n):
    return LShR(x, n)

def ch(x, y, z):
    return (x & y) ^ (~x & z)

def maj(x, y, z):
    return (x & y) ^ (x & z) ^ (y & z)

def big_sigma0(x):
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22)

def big_sigma1(x):
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25)

def small_sigma0(x):
    return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3)

def small_sigma1(x):
    return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10)

def sha256_compress(state, w):
    for i in range(16, 64):
        s0 = small_sigma0(w[i-15])
        s1 = small_sigma1(w[i-2])
        w.append(w[i-16] + s0 + w[i-7] + s1)
    a, b, c, d, e, f, g, h = state
    for i in range(64):
        t1 = h + big_sigma1(e) + ch(e, f, g) + BitVecVal(K[i], 32) + w[i]
        t2 = big_sigma0(a) + maj(a, b, c)
        h, g, f, e, d, c, b, a = g, f, e + d, d, c, b, a, t1 + t2
    return [state[0] + a, state[1] + b, state[2] + c, state[3] + d,
            state[4] + e, state[5] + f, state[6] + g, state[7] + h]

def double_sha256_bv(prefix, nonce):
    # first block
    w1 = [BitVecVal(int.from_bytes(prefix[4*i:4*i+4], 'little'), 32)
          for i in range(16)]
    init = [BitVecVal(x, 32) for x in [
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    ]]
    mid = sha256_compress(init, list(w1))
    # second block words
    length_bits = 80 * 8
    w2 = []
    # header bytes 64..75
    for i in range(3):
        chunk = prefix[64+4*i:64+4*i+4]
        w2.append(BitVecVal(int.from_bytes(chunk, 'little'), 32))
    # nonce
    w2.append(nonce)
    # padding start
    w2.append(BitVecVal(0x00000080, 32))
    # zero pad
    for _ in range(5, 14):
        w2.append(BitVecVal(0, 32))
    # length
    w2.append(BitVecVal(length_bits & 0xFFFFFFFF, 32))
    w2.append(BitVecVal((length_bits >> 32) & 0xFFFFFFFF, 32))
    final = sha256_compress(mid, list(w2))
    return Concat(*final)

def decode_target(bits):
    exp = bits >> 24
    mant = bits & 0xFFFFFF
    return mant * (1 << (8*(exp-3)))

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--header-hex', required=True,
                   help='80-byte block header hex, nonce bytes zeroed')
    args = p.parse_args()
    header_hex = args.header_hex.strip()
    if len(header_hex) != 160 or not header_hex.endswith('00000000'):
        sys.exit('Error: header-hex must be 160 hex chars ending with 8 zeros')
    header = binascii.unhexlify(header_hex)
    prefix = header[:76]
    bits_le = int.from_bytes(header[72:76], 'little')
    target = decode_target(bits_le)

    nonce = BitVec('nonce', 32)
    digest_bv = double_sha256_bv(prefix, nonce)

    # Configure tactic stack
    tactic = Then(
        With('simplify', elim_and=True),
        Tactic('propagate-values'),
        Tactic('ctx-solver-simplify'),
        Tactic('bit-blast'),
        Tactic('sat')
    )
    model = None
    used_anchor = False

    # fallback attempts: (high_bit, low_bit, anchor_expr, description)
    attempts = [
        (255, 248, None, 'primary 8-bit slice'),
        (247, 240, None, 'secondary 8-bit slice'),
        (255, 244, None, 'expanded 12-bit slice'),
        (255, 244, LShR(nonce, 30) == BitVecVal(1, 32), 'anchor bits31:30=1, 12-bit')
    ]
    for h, l, anchor, desc in attempts:
        print(f"[INFO] Attempt slice {h}:{l}, anchor={desc}")
        start = time.time()
        opt = Optimize()
        dg = Extract(h, l, digest_bv)
        tg = Extract(h, l, BitVecVal(target, 256))
        opt.assert_soft(dg <= tg, weight=100, id='primary_digest_path')
        if anchor is not None:
            opt.add(anchor)
        g = Goal()
        for c in opt.assertions():
            g.add(c)
        res = tactic(g)
        dur = time.time() - start
        print(f"[TIME] {dur:.3f}s")
        if res and res[0].is_decided_sat():
            model = res[0].model()
            used_anchor = anchor is not None
            print(f"[OK] SAT on {desc}")
            break
        else:
            print(f"[WARN] UNSAT on {desc}")
    if model is None:
        print("[FAIL] All structural attempts failed")
        sys.exit(1)

    nonce_val = model[nonce].as_long()
    # verify real SHA256²
    full_hdr = prefix + nonce_val.to_bytes(4, 'little')
    real_digest = hashlib.sha256(
        hashlib.sha256(full_hdr).digest()
    ).digest()[::-1]
    real_int = int.from_bytes(real_digest, 'big')
    result = 'PASS' if real_int <= target else 'FAIL'

    print(f"HeaderHex: {header_hex}")
    print(f"Nonce: {nonce_val} (0x{nonce_val:08x}){' [anchor]' if used_anchor else ''}")
    print(f"Bits: 0x{bits_le:08x}")
    print(f"Target: 0x{target:064x}")
    print(f"SHA256^2 digest: {real_digest.hex()}")
    print(f"PoW result: {result}")

if __name__ == '__main__':
    main()
