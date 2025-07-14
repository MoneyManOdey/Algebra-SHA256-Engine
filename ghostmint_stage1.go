//go:build ignore
// +build ignore

// ghostmint_stage1.go - Stage 1: fetch live header fields & nonce via aci_resolver.py, validate PoW
package main

import (
	"bytes"
	"crypto/sha256"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"math/big"
	"os/exec"
	"strings"
)

// HeaderInfo holds the JSON output from aci_resolver.py
type HeaderInfo struct {
	PrevBlock string `json:"PrevBlock"`
	Bits      uint32 `json:"Bits"`
	Timestamp uint32 `json:"Timestamp"`
	Nonce     uint32 `json:"Nonce"`
}

func reverseBytes(b []byte) []byte {
	n := len(b)
	out := make([]byte, n)
	for i := 0; i < n; i++ {
		out[i] = b[n-1-i]
	}
	return out
}

// compactToBig converts Bitcoin compact difficulty to a big.Int target
func compactToBig(bits uint32) *big.Int {
	exp := bits >> 24
	mant := bits & 0x007fffff
	target := new(big.Int).SetUint64(uint64(mant))
	shift := 8 * (int(exp) - 3)
	if shift > 0 {
		target.Lsh(target, uint(shift))
	}
	return target
}

// doubleSHA256 computes SHA256(SHA256(data)) using Go's crypto/sha256
func doubleSHA256(data []byte) []byte {
	first := sha256.Sum256(data)
	second := sha256.Sum256(first[:])
	return second[:]
}

func main() {
	// Call aci_resolver.py and capture JSON
	out, err := exec.Command("python3", "aci_resolver.py").CombinedOutput()
	if err != nil {
		fmt.Fatalf("aci_resolver.py error: %v\n%s", err, string(out))
	}
	// Expect last line to be JSON
	lines := bytes.Split(bytes.TrimSpace(out), []byte{'\n'})
	last := lines[len(lines)-1]
	var info HeaderInfo
	if err := json.Unmarshal(last, &info); err != nil {
		fmt.Fatalf("failed to parse JSON: %v\n%s", err, last)
	}

	// Construct header bytes
	const version = 0x20000000
	// fixed dummy merkle root from aci_resolver.py
	merkHex := "" + strings.Repeat("00", 31) + "01"
	prevHash, _ := hex.DecodeString(info.PrevBlock)
	merkBytes, _ := hex.DecodeString(merkHex)

	hdr := make([]byte, 80)
	binary.LittleEndian.PutUint32(hdr[0:4], version)
	copy(hdr[4:36], reverseBytes(prevHash))
	copy(hdr[36:68], reverseBytes(merkBytes))
	binary.LittleEndian.PutUint32(hdr[68:72], info.Timestamp)
	binary.LittleEndian.PutUint32(hdr[72:76], info.Bits)
	binary.LittleEndian.PutUint32(hdr[76:80], info.Nonce)

	// Compute PoW hash
	hashRaw := doubleSHA256(hdr)
	hashBE := reverseBytes(hashRaw)
	hashInt := new(big.Int).SetBytes(hashBE)
	target := compactToBig(info.Bits)

	valid := hashInt.Cmp(target) <= 0

	// Print confirmation
	fmt.Printf("PrevBlock: %s\n", info.PrevBlock)
	fmt.Printf("Bits: %d\n", info.Bits)
	fmt.Printf("Timestamp: %d\n", info.Timestamp)
	fmt.Printf("Nonce: %d\n", info.Nonce)
	fmt.Printf("BlockHash: %064x\n", hashInt)
	fmt.Printf("Valid PoW: %v\n", valid)
}
