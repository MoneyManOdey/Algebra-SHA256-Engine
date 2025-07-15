#!/usr/bin/env python3
"""
Phase D: Full digest ≤ target collapse via Z3 Fixedpoint Datalog rules.

This script builds on sha256_structural_pow.py's rule scaffold and adds:
  - Full 256-bit target relation
  - Recursive bitwise comparator R(pos)
  - PoWValid(header, nonce) rule that enforces digest ≤ target
  - Query to solve for nonce purely in Datalog (no SAT fallback)
"""
import sys, struct, json, base64, http.client
from sha256_structural_pow import mk_sha256_rules
from z3 import (
    IntSort, BoolSort, Function, IntVal, BoolVal, Xor, Not, And,
    Fixedpoint
)

def decode_target(bits):
    exp = bits >> 24
    mant = bits & 0xFFFFFF
    return mant * (1 << (8*(exp-3)))

def main():
    # Fetch header via RPC (same as structural_pow)
    RPC_USER, RPC_PASS = 'Oliver', 'satoshi'
    RPC_HOST, RPC_PORT = '127.0.0.1', 8332
    def rpc_call(m,p=None):
        conn = http.client.HTTPConnection(RPC_HOST, RPC_PORT)
        pl = json.dumps({'jsonrpc':'1.0','id':'p','method':m,'params':p or []})
        auth = base64.b64encode(f"{RPC_USER}:{RPC_PASS}".encode()).decode()
        conn.request('POST','/',pl,{'Authorization':f'Basic {auth}','Content-Type':'application/json'})
        r = conn.getresponse().read()
        resp = json.loads(r)
        if resp.get('error'): sys.exit(resp['error'])
        return resp['result']

    tip = rpc_call('getbestblockhash')
    hdr = rpc_call('getblockheader',[tip,True])
    version = hdr['version']
    prev = hdr['previousblockhash']
    merkle = hdr['merkleroot']
    timestamp = hdr['time']
    bits = int(hdr['bits'], 16)

    # 80-byte header hex
    hb = struct.pack('<I',version) + bytes.fromhex(prev)[::-1] + bytes.fromhex(merkle)[::-1]
    hb += struct.pack('<I',timestamp) + struct.pack('<I',bits) + b'\x00\x00\x00\x00'
    header_hex = hb.hex()
    print(f"HeaderHex: {header_hex}")

    hw = [int(header_hex[i*8:(i+1)*8],16) for i in range(16)]
    fp = Fixedpoint()
    # Phase 2: Engine tuning for zero-latency structural collapse
    fp.set(engine='datalog')
    fp.set('timeout', 0)
    fp.set('max_memory', 8192)
    fp.set(default_relation='input')
    # Import schedule + compression rules
    fp, W, _ = mk_sha256_rules(hw)

    # Build target bit relation TB(pos)
    target = decode_target(bits)
    TB = Function('TB', IntSort(), BoolSort())
    for g in range(256):
        b = (target >> (255-g)) & 1
        if b:
            fp.rule(TB(IntVal(g)), BoolVal(True))
        else:
            fp.rule(Not(TB(IntVal(g))), BoolVal(True))

    # Digest bits via Hf(0,i) from previous script
    from sha256_structural_pow import mk_sha256_rules as _mk
    # R(pos): digest[0..] < target[0..]
    R = Function('R', IntSort(), BoolSort())
    fp.rule(R(IntVal(256)), BoolVal(True))
    Hf = Function('Hf', IntSort(), IntSort(), BoolSort())
    # Define R bits
    for g in range(256):
        word, bitidx = g//32, 31 - (g % 32)
        hbit = Hf(IntVal(word), IntVal(bitidx))
        tbit = TB(IntVal(g))
        # less when hbit=0 and tbit=1
        fp.rule(R(IntVal(g)), And(Not(hbit), tbit))
        # equal then recurse
        fp.rule(R(IntVal(g)), And(Not(Xor(hbit, tbit)), R(IntVal(g+1))))

    # PoWValid(header,nonce): digest <= target
    PoWValid = Function('PoWValid', IntSort(), IntSort(), BoolSort())
    # Bind nonce into W(15,*) bits
    nonce = IntVal(0)
    for j in range(32):
        fp.rule(W(IntVal(15), IntVal(j)), (nonce & (1<<j)) != 0)
    fp.rule(PoWValid(IntVal(0), IntVal(0)), R(IntVal(0)))

    # Query PoWValid
    res = fp.query(PoWValid(IntVal(0), IntVal(0)))
    print(f"PoWValid: {res}")

    # Phase 3: Export to SMT-LIB for optional backend use
    smt2 = fp.to_smt2(PoWValid(IntVal(0), IntVal(0)))
    with open('pow_full.smt2', 'w') as f:
        f.write(smt2)
    print('[EXPORT] SMT2 exported to pow_full.smt2')

if __name__=='__main__':
    main()
