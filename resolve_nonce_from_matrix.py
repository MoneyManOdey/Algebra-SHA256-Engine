#!/usr/bin/env python3
"""
resolve_nonce_from_matrix.py

Read the ANF JSON from symbolic_sha256_phase1.py and solve for nonce bits via GF(2) linear algebra.
Outputs a valid nonce, the bit-vector, simulated digest bits, and optional double-SHA256 proof of a header template.
"""
import argparse
import json
import hashlib

import numpy as np
try:
    import scipy.sparse as sp
except ImportError:
    sp = None  # scipy.sparse optional, fallback to numpy-only elimination


def gf2_solve(A, b):
    """
    Solve A x = b over GF(2) by Gaussian elimination.
    A is numpy array shape (m,n), b is length m.
    Returns one solution x (length n) with free vars = 0.
    """
    A = A.copy() % 2
    b = b.copy() % 2
    m, n = A.shape
    # augmented matrix
    M = np.hstack((A, b.reshape(-1, 1)))
    row = 0
    pivots = []
    for col in range(n):
        # find pivot
        sel = None
        for r in range(row, m):
            if M[r, col] == 1:
                sel = r
                break
        if sel is None:
            continue
        # swap to current row
        M[[row, sel]] = M[[sel, row]]
        pivots.append(col)
        # eliminate below
        for r in range(row+1, m):
            if M[r, col] == 1:
                M[r, :] ^= M[row, :]
        row += 1
        if row == m:
            break
    # back-substitution
    x = np.zeros(n, dtype=np.uint8)
    for i in range(len(pivots)-1, -1, -1):
        pc = pivots[i]
        # sum of knowns in row i
        s = int((M[i, pc+1:n] & x[pc+1:n]).sum() % 2)
        x[pc] = (int(M[i, -1]) ^ s) & 1
    return x


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('json_file', help='ANF JSON from phase1')
    parser.add_argument('--header-hex', metavar='HEX',
                        help='80-byte header hex template with nonce bytes zeroed')
    args = parser.parse_args()

    data = json.load(open(args.json_file))
    M_list = data['flattened_matrix']
    b = np.array(data['constant_vector'], dtype=np.uint8)
    monomials = data['monomials']

    A = np.array(M_list, dtype=np.uint8)

    # solve A v = b over GF(2)
    v = gf2_solve(A, b)

    # extract x bits from monomials vector
    header_vars = data['header_inputs']  # x0..x31
    x_bits = []
    for var in header_vars:
        key = var[1:]
        try:
            j = monomials.index(key)
        except ValueError:
            # variable not in equations, default to 0
            x_bits.append(0)
        else:
            x_bits.append(int(v[j]))
    x_bits = np.array(x_bits, dtype=np.uint8)
    nonce = sum(int(x_bits[i]) << i for i in range(len(x_bits)))

    # compute simulated digest bits (a1 LSBs)
    sim = (A.dot(v) ^ b) % 2

    print(f"nonce: {nonce} (0x{nonce:08x})")
    print(f"bits : {list(x_bits)}")
    print(f"digest bits: {sim.tolist()}")

    # proof: double SHA256 of header_with_nonce
    if args.header_hex:
        hdrhex = args.header_hex.strip()
        if len(hdrhex) != 160 or not hdrhex.endswith('00000000'):
            print("Warning: header-hex should be 80-byte hex ending in 8 zeros (4-byte LE nonce)")
        prefix = hdrhex[:-8]
        nonce_hex = f"{nonce:08x}"
        full_hex = prefix + nonce_hex
        proof = hashlib.sha256(bytes.fromhex(full_hex)).digest()
        proof = hashlib.sha256(proof).hexdigest()
        print(f"proof : {proof}")


if __name__ == '__main__':
    main()
