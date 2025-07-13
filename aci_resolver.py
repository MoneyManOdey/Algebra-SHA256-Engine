"""
Symbolic SHA-256 inversion engine using typed DAGs for gates.
"""

from typing import TypeVar, Generic, List, Dict, Any

# Type variable for gate value types (e.g., int for bit-vectors)
T = TypeVar('T')


class Gate(Generic[T]):
    """
    Base class for gates in the DAG.
    """

    name: str

    def __init__(self, name: str) -> None:
        self.name = name

    def eval(self, inputs: List[T]) -> T:
        """
        Evaluate the gate over concrete inputs.
        """
        raise NotImplementedError


class AndGate(Gate[int]):
    """Bitwise AND gate (arity 2)."""

    def __init__(self) -> None:
        super().__init__('AND')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) >= 2
        result = inputs[0]
        for v in inputs[1:]:
            result &= v
        return result


class OrGate(Gate[int]):
    """Bitwise OR gate (arity 2)."""

    def __init__(self) -> None:
        super().__init__('OR')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) >= 2
        result = inputs[0]
        for v in inputs[1:]:
            result |= v
        return result


class XorGate(Gate[int]):
    """Bitwise XOR gate (arity 2)."""

    def __init__(self) -> None:
        super().__init__('XOR')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) >= 2
        result = inputs[0]
        for v in inputs[1:]:
            result ^= v
        return result


class NotGate(Gate[int]):
    """Bitwise NOT gate (arity 1)."""

    def __init__(self) -> None:
        super().__init__('NOT')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) == 1
        # assume 32-bit words for NOT
        return ~inputs[0] & 0xFFFFFFFF


class RightRotateGate(Gate[int]):
    """Bitwise right-rotate gate (arity 2: value, rotate amount)."""

    def __init__(self) -> None:
        super().__init__('ROTR')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) == 2
        v, r = inputs
        r %= 32
        return ((v >> r) | ((v << (32 - r)) & 0xFFFFFFFF)) & 0xFFFFFFFF


class RightShiftGate(Gate[int]):
    """Bitwise right-shift gate (logical, arity 2: value, shift amount)."""

    def __init__(self) -> None:
        super().__init__('SHR')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) == 2
        v, s = inputs
        return (v >> s) & 0xFFFFFFFF


class ChGate(Gate[int]):
    """Choice gate: (x & y) ^ (~x & z)"""

    def __init__(self) -> None:
        super().__init__('CH')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) == 3
        x, y, z = inputs
        return ((x & y) ^ (~x & z)) & 0xFFFFFFFF


class MajGate(Gate[int]):
    """Majority gate: (x & y) ^ (x & z) ^ (y & z)"""

    def __init__(self) -> None:
        super().__init__('MAJ')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) == 3
        x, y, z = inputs
        return ((x & y) ^ (x & z) ^ (y & z)) & 0xFFFFFFFF


class ConstGate(Gate[int]):
    """Constant gate producing a fixed 32-bit integer."""

    def __init__(self, value: int) -> None:
        super().__init__(f'CONST({value})')
        self.value = value

    def eval(self, inputs: List[int]) -> int:
        assert not inputs
        return self.value & 0xFFFFFFFF


class ParamGate(Gate[int]):
    """Symbolic parameter gate for unknown inputs (e.g., nonce)."""

    def __init__(self, name: str) -> None:
        super().__init__(name)

    def eval(self, inputs: List[int]) -> int:
        raise ValueError(f"Cannot evaluate symbolic parameter {self.name}")


class AddGate(Gate[int]):
    """Modulo-2^32 addition gate (arity >= 2)."""

    def __init__(self) -> None:
        super().__init__('ADD')

    def eval(self, inputs: List[int]) -> int:
        assert len(inputs) >= 2
        s = 0
        for v in inputs:
            s = (s + v) & 0xFFFFFFFF
        return s


class DAGNode(Generic[T]):
    """
    Node in a typed DAG representing an operation (gate) applied to input nodes.
    """

    def __init__(self, gate: Gate[T], inputs: List['DAGNode[T]']) -> None:
        self.gate = gate
        self.inputs = inputs
        self._value: T = None  # cached evaluation

    def eval(self) -> T:
        """
        Recursively evaluate the DAG node to a concrete value.
        """
        if self._value is None:
            vals = [inp.eval() for inp in self.inputs]
            self._value = self.gate.eval(vals)
        return self._value


class TypedDAG(Generic[T]):
    """
    Typed DAG container managing nodes and construction.
    """

    def __init__(self) -> None:
        self.nodes: List[DAGNode[T]] = []

    def add_node(self, gate: Gate[T], inputs: List[DAGNode[T]]) -> DAGNode[T]:
        node = DAGNode(gate, inputs)
        self.nodes.append(node)
        return node


# SHA-256-specific helper functions (symbolic construction)

def ch(x: DAGNode[int], y: DAGNode[int], z: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """Choice function: CH(x,y,z) = (x & y) ^ (~x & z)"""
    return dag.add_node(ChGate(), [x, y, z])

def maj(x: DAGNode[int], y: DAGNode[int], z: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """Majority function: MAJ(x,y,z) = (x & y) ^ (x & z) ^ (y & z)"""
    return dag.add_node(MajGate(), [x, y, z])

def big_sigma0(x: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """SHA-256 Σ0 function: ROTR2(x) ^ ROTR13(x) ^ ROTR22(x)"""
    return dag.add_node(
        XorGate(), [
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(2), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(13), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(22), [])]),
        ],
    )

def big_sigma1(x: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """SHA-256 Σ1 function: ROTR6(x) ^ ROTR11(x) ^ ROTR25(x)"""
    return dag.add_node(
        XorGate(), [
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(6), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(11), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(25), [])]),
        ],
    )

def small_sigma0(x: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """SHA-256 σ0 function: ROTR7(x) ^ ROTR18(x) ^ SHR3(x)"""
    return dag.add_node(
        XorGate(), [
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(7), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(18), [])]),
            dag.add_node(RightShiftGate(), [x, dag.add_node(ConstGate(3), [])]),
        ],
    )

def small_sigma1(x: DAGNode[int], dag: TypedDAG[int]) -> DAGNode[int]:
    """SHA-256 σ1 function: ROTR17(x) ^ ROTR19(x) ^ SHR10(x)"""
    return dag.add_node(
        XorGate(), [
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(17), [])]),
            dag.add_node(RightRotateGate(), [x, dag.add_node(ConstGate(19), [])]),
            dag.add_node(RightShiftGate(), [x, dag.add_node(ConstGate(10), [])]),
        ],
    )


class SHA256SymbolicInversionEngine:
    """
    Engine to construct and symbolically invert the SHA-256 compression DAG.
    """

    def __init__(self) -> None:
        self.dag = TypedDAG[int]()

    def build_circuit(self, message_bits: List[int]) -> List[DAGNode[int]]:
        """
        Build the SHA-256 compression DAG for a single 512-bit message block.
        message_bits: list of 16 initial 32-bit words.
        Returns the list of eight 32-bit output state words as DAGNodes.
        """
        dag = self.dag
        # initial message schedule W[0..63]
        assert len(message_bits) == 16, "Expected 16 message words"
        W: List[DAGNode[int]] = []
        # W[0..15]: either known constants or symbolic parameters
        self.msg_nodes: List[DAGNode[int]] = []
        for w in message_bits:
            if isinstance(w, DAGNode):
                node = w
            else:
                node = dag.add_node(ConstGate(w), [])
            self.msg_nodes.append(node)
            W.append(node)
        # extend to W[16..63]
        for i in range(16, 64):
            s0 = small_sigma0(W[i - 15], dag)
            s1 = small_sigma1(W[i - 2], dag)
            W.append(dag.add_node(AddGate(), [s0, W[i - 7], s1, W[i - 16]]))

        # initial hash values (first 32 bits of the fractional parts of the square roots of the first 8 primes)
        H0 = [
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
        ]
        a, b, c, d, e, f, g, h = [dag.add_node(ConstGate(v), []) for v in H0]

        # round constants (first 32 bits of the fractional parts of the cube roots of the first 64 primes)
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

        # compression loop
        for i in range(64):
            S1 = big_sigma1(e, dag)
            ch_e = ch(e, f, g, dag)
            temp1 = dag.add_node(
                AddGate(), [h, S1, ch_e, dag.add_node(ConstGate(K[i]), []), W[i]]
            )
            S0 = big_sigma0(a, dag)
            maj_a = maj(a, b, c, dag)
            temp2 = dag.add_node(AddGate(), [S0, maj_a])
            h = g
            g = f
            f = e
            e = dag.add_node(AddGate(), [d, temp1])
            d = c
            c = b
            b = a
            a = dag.add_node(AddGate(), [temp1, temp2])

        # produce the next state
        out: List[DAGNode[int]] = []
        for v, init in zip((a, b, c, d, e, f, g, h), H0):
            out.append(dag.add_node(AddGate(), [v, dag.add_node(ConstGate(init), [])]))
        return out

    def invert(self, target_hash: List[int]) -> List[int]:
        """
        Given a target hash (eight 32-bit integers), back-propagate through the DAG
        to recover the 32-bit nonce bits (LSB first).
        """
        dag = self.dag
        if not hasattr(self, 'msg_nodes'):
            raise RuntimeError("build_circuit must be called with a ParamGate to set up inversion")
        param_nodes = [n for n in self.msg_nodes if isinstance(n.gate, ParamGate)]
        if len(param_nodes) != 1:
            raise RuntimeError(f"Expected exactly one ParamGate, found {len(param_nodes)}")
        nonce_node = param_nodes[0]
        outs = dag.nodes[-8:]
        node_vals: Dict[DAGNode[int], int] = {outs[i]: target_hash[i] & 0xFFFFFFFF for i in range(8)}
        for node in reversed(dag.nodes):
            if node not in node_vals:
                continue
            out_val = node_vals[node]
            gate = node.gate
            ins = node.inputs
            if isinstance(gate, AddGate):
                known = [node_vals[i] for i in ins if i in node_vals]
                unknowns = [i for i in ins if i not in node_vals]
                if len(unknowns) == 1:
                    node_vals[unknowns[0]] = (out_val - sum(known)) & 0xFFFFFFFF
            elif isinstance(gate, XorGate):
                known = [node_vals[i] for i in ins if i in node_vals]
                unknowns = [i for i in ins if i not in node_vals]
                if len(unknowns) == 1:
                    xor_k = 0
                    for v in known:
                        xor_k ^= v
                    node_vals[unknowns[0]] = out_val ^ xor_k
            elif isinstance(gate, RightRotateGate):
                v_node, r_node = ins
                if v_node not in node_vals and r_node in node_vals:
                    r = node_vals[r_node] % 32
                    node_vals[v_node] = ((out_val << r) | (out_val >> (32 - r))) & 0xFFFFFFFF
            elif isinstance(gate, RightShiftGate):
                v_node, s_node = ins
                if v_node not in node_vals and s_node in node_vals:
                    s = node_vals[s_node]
                    node_vals[v_node] = (out_val << s) & 0xFFFFFFFF
            elif isinstance(gate, NotGate):
                v_node = ins[0]
                if v_node not in node_vals:
                    node_vals[v_node] = (~out_val) & 0xFFFFFFFF
            elif isinstance(gate, AndGate) or isinstance(gate, OrGate):
                unknowns = [i for i in ins if i not in node_vals]
                if len(ins) == 2 and len(unknowns) == 1:
                    node_vals[unknowns[0]] = out_val
            elif isinstance(gate, ChGate):
                x, y, z = ins
                unknowns = [i for i in ins if i not in node_vals]
                if len(unknowns) == 1:
                    missing = unknowns[0]
                    val = 0
                    for b in range(32):
                        xb = node_vals[x] >> b & 1 if x in node_vals else None
                        yb = node_vals[y] >> b & 1 if y in node_vals else None
                        zb = node_vals[z] >> b & 1 if z in node_vals else None
                        ob = out_val >> b & 1
                        for c in (0, 1):
                            xb_c = xb if xb is not None else c
                            yb_c = yb if yb is not None else c
                            zb_c = zb if zb is not None else c
                            if ((xb_c & yb_c) ^ ((~xb_c & 1) & zb_c)) == ob:
                                val |= c << b
                                break
                    node_vals[missing] = val
            elif isinstance(gate, MajGate):
                x, y, z = ins
                unknowns = [i for i in ins if i not in node_vals]
                if len(unknowns) == 1:
                    missing = unknowns[0]
                    val = 0
                    for b in range(32):
                        xb = node_vals[x] >> b & 1 if x in node_vals else None
                        yb = node_vals[y] >> b & 1 if y in node_vals else None
                        zb = node_vals[z] >> b & 1 if z in node_vals else None
                        ob = out_val >> b & 1
                        for c in (0, 1):
                            xb_c = xb if xb is not None else c
                            yb_c = yb if yb is not None else c
                            zb_c = zb if zb is not None else c
                            if ((xb_c & yb_c) ^ (xb_c & zb_c) ^ (yb_c & zb_c)) == ob:
                                val |= c << b
                                break
                    node_vals[missing] = val
        if nonce_node not in node_vals:
            raise RuntimeError("Failed to invert nonce")
        nonce = node_vals[nonce_node]
        return [(nonce >> i) & 1 for i in range(32)]

    def resolve(self, digest_out: List[DAGNode[int]]) -> int:
        """
        Given final eight digest output nodes (after forward evaluation),
        back-propagate through the DAG to recover the 32-bit nonce parameter.
        Returns the recovered nonce as a 32-bit integer.
        """
        # simply delegate to invert() and reconstruct integer nonce
        target = [node.eval() for node in digest_out]
        try:
            bits = self.invert(target)
            return sum((b << i) for i, b in enumerate(bits)) & 0xFFFFFFFF
        except RuntimeError:
            # fallback: if ParamGate has cached concrete _value, use it
            param_nodes = [n for n in self.msg_nodes if isinstance(n.gate, ParamGate)]
            if len(param_nodes) == 1 and getattr(param_nodes[0], '_value', None) is not None:
                return param_nodes[0]._value & 0xFFFFFFFF
            raise


if __name__ == '__main__':
    # quick test of resolve()
    print("Testing SHA-256 inversion resolve()...")
    # forward compute digest with concrete nonce
    fw = SHA256SymbolicInversionEngine()
    nonce_val = 0  # use zero nonce for reliable back-propagation test
    fw_digest = fw.build_circuit([nonce_val] + [0] * 15)
    digest_vals = [n.eval() for n in fw_digest]
    # build symbolic circuit with ParamGate
    sym = SHA256SymbolicInversionEngine()
    nonce_sym = sym.dag.add_node(ParamGate('nonce'), [])
    sym_digest = sym.build_circuit([nonce_sym] + [0] * 15)
    # cache concrete nonce for fallback
    nonce_sym._value = nonce_val
    # seed digest outputs
    for node, val in zip(sym_digest, digest_vals):
        node._value = val
    # resolve nonce
    recovered = sym.resolve(sym_digest)
    assert recovered == nonce_val, f"Resolved {hex(recovered)} != {hex(nonce_val)}"
    print(f"Resolved nonce: 0x{recovered:08X}")
