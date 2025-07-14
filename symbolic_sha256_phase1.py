#!/usr/bin/env python3
"""
symbolic_sha256_phase1.py

Compute ANF polynomials for the first 8 output bits of SHA-256 round 0 (a_new) as functions
of the 32-bit nonce word W0 (x0..x31). Outputs monomial dictionaries and an ANF matrix.
"""
import json


class ANF:
    """Algebraic normal form polynomial over GF(2)."""
    def __init__(self, terms=None):
        # terms is a set of frozenset of var indices; empty frozenset is constant term
        self.terms = set(terms) if terms is not None else set()

    def __xor__(self, other):
        res = ANF()
        res.terms = self.terms.symmetric_difference(other.terms)
        return res

    def __and__(self, other):
        res = ANF()
        for t1 in self.terms:
            for t2 in other.terms:
                res.terms.add(frozenset(t1.union(t2)))
        return res

    @staticmethod
    def const(c):
        p = ANF()
        if c & 1:
            p.terms.add(frozenset())
        return p

    @staticmethod
    def var(i):
        return ANF({frozenset({i})})

    def coef_dict(self):
        # return mapping tuple->0/1
        return {tuple(sorted(m)): 1 for m in self.terms}

    def __repr__(self):
        mons = []
        for m in sorted(self.terms, key=lambda s: (len(s), sorted(s))):
            if not m:
                mons.append('1')
            else:
                mons.append('*'.join(f'x{i}' for i in sorted(m)))
        return ' ⊕ '.join(mons) or '0'


def rotr(bits, n):
    return bits[-n:] + bits[:-n]

def sigma0(bits):
    r2 = rotr(bits, 2)
    r13 = rotr(bits, 13)
    r22 = rotr(bits, 22)
    return [r2[i] ^ r13[i] ^ r22[i] for i in range(len(bits))]

def sigma1(bits):
    r6 = rotr(bits, 6)
    r11 = rotr(bits, 11)
    r25 = rotr(bits, 25)
    return [r6[i] ^ r11[i] ^ r25[i] for i in range(len(bits))]

def ch(e, f, g):
    # (e & f) ⊕ (~e & g)
    not_e = ANF.const(1) ^ e
    return (e & f) ^ (not_e & g)

def maj(a, b, c):
    # (a & b) ⊕ (a & c) ⊕ (b & c)
    return (a & b) ^ (a & c) ^ (b & c)


class SHA256SymbolicPropagator:
    def __init__(self):
        # initial SHA-256 constants H0..H7 bits
        H = [0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
             0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19]
        self.h0 = [(H[7] >> i) & 1 for i in range(32)]
        self.e0 = [(H[4] >> i) & 1 for i in range(32)]
        self.f0 = [(H[5] >> i) & 1 for i in range(32)]
        self.g0 = [(H[6] >> i) & 1 for i in range(32)]
        self.a0 = [(H[0] >> i) & 1 for i in range(32)]
        self.b0 = [(H[1] >> i) & 1 for i in range(32)]
        self.c0 = [(H[2] >> i) & 1 for i in range(32)]
        # round constant K0
        K0 = 0x428a2f98
        self.K0 = [(K0 >> i) & 1 for i in range(32)]

    def propagate(self, nbits=8):
        # symbolic W0 bits x0..x31
        W0 = [ANF.var(i) for i in range(32)]

        # build ANF bit arrays for constants
        h = [ANF.const(b) for b in self.h0]
        e = [ANF.const(b) for b in self.e0]
        f = [ANF.const(b) for b in self.f0]
        g = [ANF.const(b) for b in self.g0]
        a = [ANF.const(b) for b in self.a0]
        b = [ANF.const(b) for b in self.b0]
        c = [ANF.const(b) for b in self.c0]
        K = [ANF.const(b) for b in self.K0]

        # compute round0 T1 and T2 for all bits
        s1_e = sigma1(e)
        ch_efg = [ch(e[i], f[i], g[i]) for i in range(32)]
        T1 = [h[i] ^ s1_e[i] ^ ch_efg[i] ^ K[i] ^ W0[i] for i in range(32)]

        s0_a = sigma0(a)
        maj_abc = [maj(a[i], b[i], c[i]) for i in range(32)]
        T2 = [s0_a[i] ^ maj_abc[i] for i in range(32)]

        # new a bits after round0
        a1 = [T1[i] ^ T2[i] for i in range(32)]

        # collect first nbits bits
        digest_map = {}
        for i in range(nbits):
            # stringify monomial keys for JSON compatibility
            cd = a1[i].coef_dict()
            digest_map[i] = {','.join(map(str, m)): coeff for m, coeff in cd.items()}
        return digest_map


def main():
    propagator = SHA256SymbolicPropagator()
    digest_anf_map = propagator.propagate(nbits=8)

    # collect all monomials
    all_mons = set()
    for row in digest_anf_map.values():
        all_mons.update(row.keys())
    cols = sorted(all_mons, key=lambda m: (len(m), m))

    # build flattened matrix and constant vector
    matrix = []
    const_vec = []
    for i in range(8):
        row = digest_anf_map[i]
        const_vec.append(row.get((), 0))
        matrix.append([ row.get(col, 0) for col in cols ])

    out = {
        'header_inputs': [f'x{i}' for i in range(32)],
        'digest_anf_map': {str(i): digest_anf_map[i] for i in range(8)},
        'flattened_matrix': matrix,
        'constant_vector': const_vec,
        'monomials': cols,
    }
    with open('symbolic_sha256_phase1.json', 'w') as f:
        json.dump(out, f, indent=2)
    print('Wrote symbolic_sha256_phase1.json')


if __name__ == '__main__':
    main()
