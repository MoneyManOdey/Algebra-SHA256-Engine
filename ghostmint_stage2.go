// ghostmint_stage2.go - End-to-end V-Energy block build and submission
package main

import (
	"bytes"
	"crypto/sha256"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
	"time"

	"github.com/btcsuite/btcd/blockchain"
	"github.com/btcsuite/btcd/chaincfg"
	"github.com/btcsuite/btcd/chaincfg/chainhash"
	"github.com/btcsuite/btcd/txscript"
	"github.com/btcsuite/btcd/wire"
	"github.com/btcsuite/btcutil"
)

// rpcCall performs a simple JSON-RPC call to Bitcoin Core.
func rpcCall(method string, params []interface{}, result interface{}) error {
	reqObj := map[string]interface{}{"jsonrpc": "2.0", "id": 1, "method": method, "params": params}
	reqBytes, _ := json.Marshal(reqObj)
	httpReq, _ := http.NewRequest("POST", "http://127.0.0.1:8332", bytes.NewBuffer(reqBytes))
	httpReq.SetBasicAuth("Oliver", "satoshi")
	httpReq.Header.Set("Content-Type", "application/json")
	resp, err := http.DefaultClient.Do(httpReq)
	if err != nil {
		return err
	}
	defer resp.Body.Close()
	respBytes, _ := io.ReadAll(resp.Body)
	var respObj struct {
		Result json.RawMessage `json:"result"`
		Error  interface{}     `json:"error"`
	}
	json.Unmarshal(respBytes, &respObj)
	if respObj.Error != nil {
		return fmt.Errorf("RPC error: %v", respObj.Error)
	}
	return json.Unmarshal(respObj.Result, result)
}

// rpcCallHTTP is like rpcCall but returns raw error for reachability check.
func rpcCallHTTP(method string, params []interface{}) (json.RawMessage, error) {
	var tmp json.RawMessage
	err := rpcCall(method, params, &tmp)
	return tmp, err
}

// reverseBytes reverses a byte slice.
func reverseBytes(b []byte) []byte {
	n := len(b)
	out := make([]byte, n)
	for i := range b {
		out[i] = b[n-1-i]
	}
	return out
}

// submitBlockRPC sends the hex-encoded block via JSON-RPC.
func submitBlockRPC(hexBlock string) error {
	return rpcCall("submitblock", []interface{}{hexBlock}, nil)
}

func main() {
	// 1. Ensure Bitcoin Core RPC is running (with user Oliver/satoshi)
	// Try a simple ping; if it fails, generate basic bitcoin.conf and launch bitcoind
	if _, err := rpcCallHTTP("getblockchaininfo", nil); err != nil {
		log.Printf("RPC unreachable, writing bitcoin.conf and launching bitcoind...: %v", err)
		home, _ := os.UserHomeDir()
		cfg := fmt.Sprintf(
			"server=1\nrpcbind=127.0.0.1\nrpcallowip=127.0.0.1\nrpcuser=Oliver\nrpcpassword=satoshi\n",
		)
		os.MkdirAll(filepath.Join(home, ".bitcoin"), 0755)
		os.WriteFile(filepath.Join(home, ".bitcoin", "bitcoin.conf"), []byte(cfg), 0644)
		bd := exec.Command("bitcoind", "-daemon")
		bd.Stdout = os.Stdout
		bd.Stderr = os.Stderr
		if err := bd.Run(); err != nil {
			log.Fatalf("failed to start bitcoind: %v", err)
		}
		// wait for RPC
		time.Sleep(3 * time.Second)
	}
	// Fetch live chain metadata from Bitcoin Core
	var bcInfo struct {
		Chain                string  `json:"chain"`
		Blocks               int64   `json:"blocks"`
		Headers              int64   `json:"headers"`
		Difficulty           float64 `json:"difficulty"`
		MedianTime           int64   `json:"mediantime"`
		InitialBlockDownload bool    `json:"initialblockdownload"`
		ChainWork            string  `json:"chainwork"`
	}
	if err := rpcCall("getblockchaininfo", nil, &bcInfo); err != nil {
		log.Fatalf("getblockchaininfo: %v", err)
	}

	var netInfo struct {
		Version     int     `json:"version"`
		Subversion  string  `json:"subversion"`
		Connections int     `json:"connections"`
		RelayFee    float64 `json:"relayfee"`
		Warnings    string  `json:"warnings"`
	}
	if err := rpcCall("getnetworkinfo", nil, &netInfo); err != nil {
		log.Fatalf("getnetworkinfo: %v", err)
	}

	var bestHash string
	if err := rpcCall("getbestblockhash", nil, &bestHash); err != nil {
		log.Fatalf("getbestblockhash: %v", err)
	}

	var bestBlk struct {
		Hash              string `json:"hash"`
		Height            int64  `json:"height"`
		PreviousBlockHash string `json:"previousblockhash"`
		Time              int64  `json:"time"`
		Bits              string `json:"bits"`
		Nonce             uint32 `json:"nonce"`
		MerkleRoot        string `json:"merkleroot"`
		Version           int32  `json:"version"`
	}
	if err := rpcCall("getblock", []interface{}{bestHash}, &bestBlk); err != nil {
		log.Fatalf("getblock: %v", err)
	}

	// Named variables for later use
	prevBlockHash := bestBlk.Hash
	prevBlockTime := bestBlk.Time
	difficultyBitsHex := bestBlk.Bits
	blockHeight := bestBlk.Height
	networkVersion := netInfo.Version
	chainwork := bcInfo.ChainWork
	mediantime := bcInfo.MedianTime

	log.Printf("Chain: %s Height: %d Headers: %d Difficulty: %f", bcInfo.Chain, bcInfo.Blocks, bcInfo.Headers, bcInfo.Difficulty)
	log.Printf("Mediantime: %d InitialDownload: %v Chainwork: %s", bcInfo.MedianTime, bcInfo.InitialBlockDownload, bcInfo.ChainWork)
	log.Printf("Network version: %d Subversion: %s Connections: %d RelayFee: %f", netInfo.Version, netInfo.Subversion, netInfo.Connections, netInfo.RelayFee)
	if netInfo.Warnings != "" {
		log.Printf("Warnings: %s", netInfo.Warnings)
	}
	log.Printf("Best block height: %d hash: %s prev: %s", bestBlk.Height, bestBlk.Hash, bestBlk.PreviousBlockHash)
	log.Printf("Best block time: %d bits: %s nonce: %d merkle: %s version: %d", bestBlk.Time, bestBlk.Bits, bestBlk.Nonce, bestBlk.MerkleRoot, bestBlk.Version)

	// Regtest fallback: generate a block if on regtest
	var ci struct{ Chain string }
	if err := rpcCall("getblockchaininfo", nil, &ci); err != nil {
		log.Fatalf("getblockchaininfo: %v", err)
	}
	if ci.Chain == "regtest" {
		// Ensure a wallet is loaded or created (regtest default wallet deprecated)
		var _res interface{}
		rpcCall("createwallet", []interface{}{"ve_pow", false, false, "", false, false, false, false, false}, &_res)
		// Get a new address to mine to
		var addr string
		rpcCall("getnewaddress", nil, &addr)
		// Mine a block to that address
		var hashes []string
		if err := rpcCall("generatetoaddress", []interface{}{1, addr}, &hashes); err != nil {
			log.Fatalf("generatetoaddress: %v", err)
		}
		fmt.Printf("[regtest] Block generated: %s\n", hashes[0])
		return
	}

	// Parse difficulty bits from best block
	bitsVal, err := strconv.ParseUint(difficultyBitsHex, 16, 32)
	if err != nil {
		log.Fatalf("Failed to parse bits hex: %v", err)
	}
	bits := uint32(bitsVal)
	timestamp := uint32(prevBlockTime + 1)

	// 2. Create 3‑tx chain txSeed -> tx0 -> tx1
	const amountSat = 130000000000000
	wif, err := btcutil.DecodeWIF("KwtDeYuM1XAmDpcU8hbFg9DAKMGuxdYPEgUkvPSiuySkZd3HrwTn")
	if err != nil {
		log.Fatalf("wif: %v", err)
	}
	// Build txSeed
	txSeed := wire.NewMsgTx(wire.TxVersion)
	txSeed.AddTxIn(wire.NewTxIn(&wire.OutPoint{Hash: chainhash.Hash{}, Index: 0xffffffff}, nil, nil))
	seedAddr, _ := btcutil.NewAddressPubKey(wif.SerializePubKey(), &chaincfg.MainNetParams)
	seedScript, _ := txscript.PayToAddrScript(seedAddr)
	txSeed.AddTxOut(wire.NewTxOut(amountSat, seedScript))
	// Sign txSeed here if needed (no signature for coinbase-style input)
	// Compute txSeed txid after building/signing
	txSeedHash := txSeed.TxHash() // <-- Compute txSeed txid in-memory for chaining

	// Build tx0
	tx0 := wire.NewMsgTx(wire.TxVersion)
	// Reference txSeed output using txSeed's txid as input
	tx0.AddTxIn(wire.NewTxIn(
		&wire.OutPoint{
			Hash:  txSeedHash, // <-- Use txSeed computed txid as OutPoint.Hash
			Index: 0,          // refer to output 0
		},
		nil,
		nil,
	)) // Input to tx0 now linked to txSeed output
	tx0.AddTxOut(wire.NewTxOut(amountSat, seedScript))
	sig0, _ := txscript.SignatureScript(tx0, 0, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx0.TxIn[0].SignatureScript = sig0
	hashes0 := txscript.NewTxSigHashes(tx0)
	witness0, _ := txscript.WitnessSignature(tx0, hashes0, 0, amountSat, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx0.TxIn[0].Witness = witness0
	// Compute tx0 txid after signing
	tx0Hash := tx0.TxHash() // <-- Compute tx0 txid in-memory for chaining

	// Build tx1
	tx1 := wire.NewMsgTx(wire.TxVersion)
	// Reference tx0 output using tx0's txid as input
	tx1.AddTxIn(wire.NewTxIn(
		&wire.OutPoint{
			Hash:  tx0Hash, // <-- Use tx0 computed txid as OutPoint.Hash
			Index: 0,
		},
		nil,
		nil,
	)) // Input to tx1 now linked to tx0 output
	dest, _ := btcutil.DecodeAddress("bc1qa57c8e02usd0kjfucngktfrz5tukhr4u554y85", &chaincfg.MainNetParams)
	destScript, _ := txscript.PayToAddrScript(dest)
	tx1.AddTxOut(wire.NewTxOut(amountSat, destScript))
	sig1, _ := txscript.SignatureScript(tx1, 0, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx1.TxIn[0].SignatureScript = sig1
	hashes1 := txscript.NewTxSigHashes(tx1)
	witness1, _ := txscript.WitnessSignature(tx1, hashes1, 0, amountSat, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx1.TxIn[0].Witness = witness1
	// Compute tx1 txid after signing
	tx1Hash := tx1.TxHash() // <-- Compute tx1 txid in-memory (for further chaining or printing)

	// 3. Compute Merkle root
	txs := []*btcutil.Tx{btcutil.NewTx(txSeed), btcutil.NewTx(tx0), btcutil.NewTx(tx1)}
	merkle := blockchain.BuildMerkleTreeStore(txs, false)
	merkleRoot := *merkle[len(merkle)-1]

	// 4. Build header prefix (76 bytes)
	const version = 0x20000000
	prevBytes, _ := hex.DecodeString(prevBlockHash)
	var prev chainhash.Hash
	copy(prev[:], reverseBytes(prevBytes))
	var mr chainhash.Hash
	copy(mr[:], reverseBytes(merkleRoot[:]))
	var buf bytes.Buffer
	binary.Write(&buf, binary.LittleEndian, uint32(version))
	buf.Write(reverseBytes(prev[:]))
	buf.Write(reverseBytes(mr[:]))
	binary.Write(&buf, binary.LittleEndian, timestamp)
	binary.Write(&buf, binary.LittleEndian, bits)
	// Append 4 zero bytes placeholder for nonce (80-byte header)
	buf.Write([]byte{0, 0, 0, 0})
	// headerHex: full 80-byte prefix->hex
	headerHex := hex.EncodeToString(buf.Bytes())

	// 5. Ensure Rust V-Energy engine is built and resolve nonce
	solverPath := filepath.Join("target", "debug", "ve_pow")
	if _, err := os.Stat(solverPath); os.IsNotExist(err) {
		log.Printf("Building V-Energy Rust engine (cargo build)...")
		build := exec.Command("cargo", "build", "--package", "ve_pow")
		build.Stdout = os.Stdout
		build.Stderr = os.Stderr
		if err := build.Run(); err != nil {
			log.Fatalf("Failed to build ve_pow: %v", err)
		}
	}
	// Invoke the Rust V-Energy engine with real headerHex
	out, err := exec.Command(
		solverPath,
		"--auto",
		"--header-hex", headerHex,
		"--json",
		"--submit",
	).CombinedOutput()
	if err != nil {
		log.Fatalf("V-Energy solver error: %v\n%s", err, out)
	}
	var nonce uint32
	for _, line := range strings.Split(string(out), "\n") {
		if strings.HasPrefix(line, "Determined nonce:") {
			parts := strings.Fields(line)
			n, _ := strconv.ParseUint(parts[2], 10, 32)
			nonce = uint32(n)
		}
	}

	// 6. Assemble full block and submit
	blkHdr := &wire.BlockHeader{version, prev, merkleRoot, time.Unix(int64(timestamp), 0), bits, nonce}
	block := wire.NewMsgBlock(blkHdr)
	block.Transactions = []*wire.MsgTx{txSeed, tx0, tx1}
	// update Merkle root
	blkMerk := blockchain.BuildMerkleTreeStore(txs, false)
	block.Header.MerkleRoot = *blkMerk[len(blkMerk)-1]
	var outBuf bytes.Buffer
	block.Serialize(&outBuf)
	blockHex := hex.EncodeToString(outBuf.Bytes())
	fmt.Printf("tx1 TXID: %s\n", tx1.TxHash())
	fmt.Printf("Nonce: %d (0x%08x)\n", nonce, nonce)
	fmt.Printf("Block hash: %s\n", block.BlockHash())
	// 7. Compute block hash and mark as symbolic (do not broadcast to mainnet)
	blkHash := block.BlockHash()
	// Compute proof-of-work hash
	hdrBytes := make([]byte, 80)
	binary.LittleEndian.PutUint32(hdrBytes[0:], block.Header.Version)
	copy(hdrBytes[4:], reverseBytes(block.Header.PrevBlock[:]))
	copy(hdrBytes[36:], reverseBytes(block.Header.MerkleRoot[:]))
	binary.LittleEndian.PutUint32(hdrBytes[68:], uint32(block.Header.Timestamp.Unix()))
	binary.LittleEndian.PutUint32(hdrBytes[72:], block.Header.Bits)
	binary.LittleEndian.PutUint32(hdrBytes[76:], block.Header.Nonce)
	h1 := sha256.Sum256(hdrBytes)
	h2 := sha256.Sum256(h1[:])
	powHash := reverseBytes(h2[:])
	// Compute target from bits
	target := blockchain.CompactToBig(block.Header.Bits)
	// Output symbolic block details
	fmt.Printf("tx1 TXID: %s\n", tx1.TxHash())
	fmt.Printf("Nonce: %d (0x%08x)\n", block.Header.Nonce, block.Header.Nonce)
	fmt.Printf("Block hash: %s\n", blkHash)
	fmt.Printf("PoW hash: %x\n", powHash)
	fmt.Printf("Target  : %064x\n", target)
	fmt.Println("WARNING: This is a symbolic simulation block, not for mainnet broadcast.")
}
