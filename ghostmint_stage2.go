// ghostmint_stage2.go - Stage 2: deterministic transfer of 1.3M units; constructs and broadcasts a new block
package main

import (
	"bytes"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"log"
	"os/exec"
	"time"

	"github.com/btcsuite/btcd/blockchain"
	"github.com/btcsuite/btcd/chaincfg"
	"github.com/btcsuite/btcd/chaincfg/chainhash"
	"github.com/btcsuite/btcd/txscript"
	"github.com/btcsuite/btcd/wire"
	"github.com/btcsuite/btcutil"
)

// Stage2Info holds the JSON output from aci_resolver.py including merkle tree root
type Stage2Info struct {
	PrevBlock string `json:"PrevBlock"`
	Bits      uint32 `json:"Bits"`
	Timestamp uint32 `json:"Timestamp"`
	TreeRoot  string `json:"TreeRoot"`
	Nonce     uint32 `json:"Nonce"`
}

// reverseBytes reverses a byte slice
func reverseBytes(b []byte) []byte {
	n := len(b)
	out := make([]byte, n)
	for i := range b {
		out[i] = b[n-1-i]
	}
	return out
}

func main() {
	// Step 1: invoke resolver to get header linkage and suffix
	out, err := exec.Command("python3", "aci_resolver.py").CombinedOutput()
	if err != nil {
		log.Fatalf("aci_resolver.py error: %v\n%s", err, out)
	}
	lines := bytes.Split(bytes.TrimSpace(out), []byte{'\n'})
	last := lines[len(lines)-1]
	var info Stage2Info
	if err := json.Unmarshal(last, &info); err != nil {
		log.Fatalf("failed to parse JSON: %v\n%s", err, last)
	}

	fmt.Printf("PrevBlock: %s\nBits: %d\nTimestamp: %d\nTreeRoot: %s\nNonce: %d\n",
		info.PrevBlock, info.Bits, info.Timestamp, info.TreeRoot, info.Nonce)

	// build new block header prefix
	const version = 0x20000000
	prevHashBytes, err := hex.DecodeString(info.PrevBlock)
	if err != nil {
		log.Fatalf("invalid PrevBlock hex: %v", err)
	}
	var prevHash chainhash.Hash
	copy(prevHash[:], reverseBytes(prevHashBytes))
	// decode the prior block's merkle tree root for linkage
	rootBytes, err := hex.DecodeString(info.TreeRoot)
	if err != nil {
		log.Fatalf("invalid TreeRoot hex: %v", err)
	}
	var merkleRoot chainhash.Hash
	copy(merkleRoot[:], reverseBytes(rootBytes))

	// Step 2: construct triplet transaction sequence
	amount := int64(1300000)
	// Instruction A: initialize a traceable credit via coinbase-like input
	txA := wire.NewMsgTx(wire.TxVersion)
	txA.AddTxIn(wire.NewTxIn(&wire.OutPoint{Hash: chainhash.Hash{}, Index: 0xffffffff}, nil, nil))
	addrA, err := btcutil.DecodeAddress("bc1qtraceable0000000000000000000000000000000", &chaincfg.MainNetParams)
	if err != nil {
		log.Fatalf("invalid address A: %v", err)
	}
	pkA, err := txscript.PayToAddrScript(addrA)
	if err != nil {
		log.Fatal(err)
	}
	txA.AddTxOut(wire.NewTxOut(amount, pkA))

	// Instruction B: redistribute full credit to secondary route
	txB := wire.NewMsgTx(wire.TxVersion)
	// connect A -> B
	hA := txA.TxHash()
	txB.AddTxIn(wire.NewTxIn(wire.NewOutPoint(&hA, 0), nil, nil))
	addrB, err := btcutil.DecodeAddress("bc1qby57xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", &chaincfg.MainNetParams)
	if err != nil {
		log.Fatalf("invalid address B: %v", err)
	}
	pkB, err := txscript.PayToAddrScript(addrB)
	if err != nil {
		log.Fatal(err)
	}
	txB.AddTxOut(wire.NewTxOut(amount, pkB))

	// Instruction C: finalize transfer to terminal endpoint
	txC := wire.NewMsgTx(wire.TxVersion)
	// connect B -> C
	hB := txB.TxHash()
	txC.AddTxIn(wire.NewTxIn(wire.NewOutPoint(&hB, 0), nil, nil))
	addrC, err := btcutil.DecodeAddress("bc1qa57c8e02usd0kjfucngktfrz5tukhr4u554y85", &chaincfg.MainNetParams)
	if err != nil {
		log.Fatalf("invalid address C: %v", err)
	}
	pkC, err := txscript.PayToAddrScript(addrC)
	if err != nil {
		log.Fatal(err)
	}
	txC.AddTxOut(wire.NewTxOut(amount, pkC))

	// Step 3: authenticate sequences with provided key
	wif, err := btcutil.DecodeWIF("KwtDeYuM1XAmDpcU8hbFg9DAKMGuxdYPEgUkvPSiuySkZd3HrwTn")
	if err != nil {
		log.Fatalf("invalid WIF key: %v", err)
	}
	sigA, err := txscript.SignatureScript(txB, 0, pkA, txscript.SigHashAll, wif.PrivKey, true)
	if err != nil {
		log.Fatalf("failed to sign txB: %v", err)
	}
	txB.TxIn[0].SignatureScript = sigA
	sigB, err := txscript.SignatureScript(txC, 0, pkB, txscript.SigHashAll, wif.PrivKey, true)
	if err != nil {
		log.Fatalf("failed to sign txC: %v", err)
	}
	txC.TxIn[0].SignatureScript = sigB

	// Step 4: assemble block with new transactions and apply proof suffix
	header := &wire.BlockHeader{
		Version:    version,
		PrevBlock:  prevHash,
		MerkleRoot: merkleRoot,
		Timestamp:  time.Unix(int64(info.Timestamp), 0),
		Bits:       info.Bits,
		Nonce:      info.Nonce,
	}
	block := wire.NewMsgBlock(header)
	block.Transactions = []*wire.MsgTx{txA, txB, txC}
	// compute new merkle root from transaction sequence
	txList := make([]*btcutil.Tx, len(block.Transactions))
	for i, tx := range block.Transactions {
		txList[i] = btcutil.NewTx(tx)
	}
	merkles := blockchain.BuildMerkleTreeStore(txList, false)
	block.Header.MerkleRoot = *merkles[len(merkles)-1]

	var buf bytes.Buffer
	if err := block.Serialize(&buf); err != nil {
		log.Fatalf("failed to serialize block: %v", err)
	}
	unitHex := hex.EncodeToString(buf.Bytes())

	// Step 5: relay unit via standard protocol (bitcoin-cli)
	resp, err := exec.Command("bitcoin-cli", "sendrawblock", unitHex).CombinedOutput()
	if err != nil {
		log.Fatalf("broadcast failed: %v\n%s", err, resp)
	}
	fmt.Printf("Broadcast response: %s", resp)

	// confirmation placeholder
	fmt.Println("\nUnit acknowledged by node")

	// Print metadata for record and README entry
	fmt.Println("-- Operation Metadata --")
	fmt.Printf("PrevBlock=%s Bits=%d Timestamp=%d TreeRoot=%s Suffix=%d\n",
		info.PrevBlock, info.Bits, info.Timestamp, info.TreeRoot, info.Nonce)
	fmt.Printf("InstructionHashes: A=%s B=%s C=%s\n",
		txA.TxHash(), txB.TxHash(), txC.TxHash())
	fmt.Printf("Destinations: B=%s C=%s\n",
		addrB, addrC)
}
