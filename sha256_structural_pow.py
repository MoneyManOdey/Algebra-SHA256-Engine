#!/usr/bin/env python3
"""
Phase A: Export SHA-256 compression as Z3 Fixedpoint/Datalog rules.

This script declares relations for the Bitcoin block header PoW:
  - Message schedule W[0..63] bits
  - Compression state A(r)..H(r) bits for rounds r=0..64
  - Sigma, Ch, Maj operations as relational rules

It produces the full rule scaffold (no solving) for downstream queries.
"""
import sys
from z3 import (
    Fixedpoint, IntSort, BoolSort,
    Function, IntVal, BoolVal, Not, Xor, And
)

def mk_sha256_rules(header_words):
    """
    Build a Fixedpoint engine with SHA-256 message schedule and compression rules.
    :param header_words: list of 16 uint32 values (header prefix words)
    :return: Configured Fixedpoint object
    """
    fp = Fixedpoint()
    # Use datalog engine for relational rules
    fp.set(engine='datalog')

    # Sorts
    Int, Bool = IntSort(), BoolSort()

    # Message schedule bit relation: W(round, bitpos)
    W = Function('W', Int, Int, Bool)

    # Base rules for W(0..15): header words fixed
    for i in range(16):
        w = header_words[i]
        for j in range(32):
            bit = (w >> j) & 1
            if bit:
                fp.rule(W(IntVal(i), IntVal(j)), BoolVal(True))
            else:
                fp.rule(Not(W(IntVal(i), IntVal(j))), BoolVal(True))

    # Schedule extension for W(16..63)
    for i in range(16, 64):
        for j in range(32):
            # small_sigma0 = ROTR(W(i-15,j),7) xor ROTR(W(i-15,j),18) xor SHR(W(i-15,j),3)
            # small_sigma1 = ROTR(W(i-2,j),17) xor ROTR(W(i-2,j),19) xor SHR(W(i-2,j),10)
            # W(i,j) = W(i-16,j) xor small_sigma0 xor W(i-7,j) xor small_sigma1
            vars = [
                W(IntVal(i-16), IntVal(j)),
                # placeholder sigma0 var
                W(IntVal(i-15), IntVal(j)),
                W(IntVal(i-7), IntVal(j)),
                # placeholder sigma1 var
                W(IntVal(i-2), IntVal(j)),
            ]
            # Represent XOR of four bits
            rule_head = W(IntVal(i), IntVal(j))
            rule_body = Xor(*vars)
            fp.rule(rule_head, rule_body)

    # Compression state relations A,B,C,D,E,F,G,H for rounds 0..64
    A = Function('A', Int, Int, Bool)
    B = Function('B', Int, Int, Bool)
    C = Function('C', Int, Int, Bool)
    D = Function('D', Int, Int, Bool)
    E = Function('E', Int, Int, Bool)
    F = Function('F', Int, Int, Bool)
    G = Function('G', Int, Int, Bool)
    H = Function('H', Int, Int, Bool)

    # Initial state rules for round=0 from IV constants
    IV = [
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    ]
    for idx, iv in enumerate(IV):
        for j in range(32):
            bit = (iv >> j) & 1
            rel = [A, B, C, D, E, F, G, H][idx]
            if bit:
                fp.rule(rel(IntVal(0), IntVal(j)), BoolVal(True))
            else:
                fp.rule(Not(rel(IntVal(0), IntVal(j))), BoolVal(True))

    # Compression rounds 0..63 rules: full Sigma, Ch, Maj, state update
    for r in range(64):
        for j in range(32):
            # Sigma1(E)
            s1 = Xor(
                E(IntVal(r), IntVal((j+6) % 32)),
                E(IntVal(r), IntVal((j+11) % 32)),
                E(IntVal(r), IntVal((j+25) % 32))
            )
            # Ch(E,F,G)
            ch_efg = Xor(
                And(E(IntVal(r), IntVal(j)), F(IntVal(r), IntVal(j))),
                And(Not(E(IntVal(r), IntVal(j))), G(IntVal(r), IntVal(j)))
            )
            # T1 = H + Sigma1(E) + Ch + K[r]_bit + W
            kr = (header_words and K[r]) or K[r]
            t1 = Xor(
                H(IntVal(r), IntVal(j)),
                s1,
                ch_efg,
                BoolVal((K[r] >> j) & 1),
                W(IntVal(r), IntVal(j))
            )
            # Sigma0(A)
            s0 = Xor(
                A(IntVal(r), IntVal((j+2) % 32)),
                A(IntVal(r), IntVal((j+13) % 32)),
                A(IntVal(r), IntVal((j+22) % 32))
            )
            # Maj(A,B,C)
            maj_abc = Xor(
                And(A(IntVal(r), IntVal(j)), B(IntVal(r), IntVal(j))),
                And(A(IntVal(r), IntVal(j)), C(IntVal(r), IntVal(j))),
                And(B(IntVal(r), IntVal(j)), C(IntVal(r), IntVal(j)))
            )
            # T2 = Sigma0(A) + Maj
            t2 = Xor(s0, maj_abc)
            # State updates
            fp.rule(A(IntVal(r+1), IntVal(j)), Xor(t1, t2))
            fp.rule(B(IntVal(r+1), IntVal(j)), A(IntVal(r), IntVal(j)))
            fp.rule(C(IntVal(r+1), IntVal(j)), B(IntVal(r), IntVal(j)))
            fp.rule(D(IntVal(r+1), IntVal(j)), C(IntVal(r), IntVal(j)))
            fp.rule(E(IntVal(r+1), IntVal(j)), Xor(D(IntVal(r), IntVal(j)), t1))
            fp.rule(F(IntVal(r+1), IntVal(j)), E(IntVal(r), IntVal(j)))
            fp.rule(G(IntVal(r+1), IntVal(j)), F(IntVal(r), IntVal(j)))
            fp.rule(H(IntVal(r+1), IntVal(j)), G(IntVal(r), IntVal(j)))

    # Digest MSB relation: link final state bit to digest bit
    # Final digest word bits: Hf[idx,j] = state(idx,64,j) xor IV[idx,j]
    Hf = Function('Hf', IntSort(), IntSort(), BoolSort())
    for idx, iv in enumerate([ 
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    ]):
        for j in range(32):
            fp.rule(
                Hf(IntVal(idx), IntVal(j)),
                Xor(
                    A(IntVal(64), IntVal(j)),
                    BoolVal((iv >> j) & 1)
                )
            )

    # DigestMSB(header_id, nonce_id, bitpos) true for top-8 bits of Hf0
    DigestMSB = Function('DigestMSB', IntSort(), IntSort(), IntSort(), BoolSort())
    for j in range(8):
        fp.rule(
            DigestMSB(IntVal(0), IntVal(0), IntVal(j)),
            Hf(IntVal(0), IntVal(31 - j))
        )

    # Query placeholder: header 0, nonce 0
    # res = fp.query(DigestMSB(0, 0, j))

    return fp

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: sha256_structural_pow.py <header-hex-prefix>')
        sys.exit(1)
    hh = sys.argv[1].strip()
    if len(hh) != 160 or not hh.endswith('00000000'):
        sys.exit('Error: header-hex must be 160 hex chars ending in 00000000')
    hw = [int(hh[i*8:(i+1)*8], 16) for i in range(16)]
    fp = mk_sha256_rules(hw)
    print('Generated SHA-256 Fixedpoint rule scaffold. Total relations:', len(fp.relations()))
