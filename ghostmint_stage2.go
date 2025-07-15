// ghostmint_stage2.go - Stage 2: deterministic transfer of 1.3M units; constructs and broadcasts a new block
package main

import (
	"bufio"
	"bytes"
	"crypto/sha256"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"math/big"
	"net/http"
	"os/exec"
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

// submitBlockRPC sends the hex-encoded block via JSON-RPC to local node.
func submitBlockRPC(hexBlock string) error {
	reqObj := map[string]interface{}{
		"method":  "submitblock",
		"params":  []string{hexBlock},
		"id":      1,
		"jsonrpc": "2.0",
	}
	reqBytes, err := json.Marshal(reqObj)
	if err != nil {
		return fmt.Errorf("failed to marshal JSON-RPC request: %v", err)
	}
	httpReq, err := http.NewRequest("POST", "http://127.0.0.1:8332", bytes.NewBuffer(reqBytes))
	if err != nil {
		return fmt.Errorf("failed to create HTTP request: %v", err)
	}
	httpReq.SetBasicAuth("Oliver", "satoshi")
	httpReq.Header.Set("Content-Type", "application/json")
	client := &http.Client{Timeout: 10 * time.Second}
	resp, err := client.Do(httpReq)
	if err != nil {
		return fmt.Errorf("RPC HTTP error: %v", err)
	}
	defer resp.Body.Close()
	respBytes, err := io.ReadAll(resp.Body)
	if err != nil {
		return fmt.Errorf("failed to read RPC response: %v", err)
	}
	fmt.Printf("RPC Response: %s\n", string(respBytes))
	return nil
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

// rpcCall sends a JSON-RPC request and decodes the result into result.
func rpcCall(client *http.Client, url, user, pass, method string, params []interface{}, result interface{}) error {
	reqObj := map[string]interface{}{
		"jsonrpc": "2.0",
		"id":      1,
		"method":  method,
		"params":  params,
	}
	reqBytes, err := json.Marshal(reqObj)
	if err != nil {
		return fmt.Errorf("marshal RPC request: %v", err)
	}
	httpReq, err := http.NewRequest("POST", url, bytes.NewBuffer(reqBytes))
	if err != nil {
		return fmt.Errorf("create RPC request: %v", err)
	}
	httpReq.SetBasicAuth(user, pass)
	httpReq.Header.Set("Content-Type", "application/json")
	resp, err := client.Do(httpReq)
	if err != nil {
		return fmt.Errorf("RPC HTTP error: %v", err)
	}
	defer resp.Body.Close()
	respBytes, err := io.ReadAll(resp.Body)
	if err != nil {
		return fmt.Errorf("read RPC response: %v", err)
	}
	var respObj struct {
		Result json.RawMessage `json:"result"`
		Error  interface{}     `json:"error"`
	}
	if err := json.Unmarshal(respBytes, &respObj); err != nil {
		return fmt.Errorf("unmarshal RPC response: %v", err)
	}
	if respObj.Error != nil {
		return fmt.Errorf("RPC error: %v", respObj.Error)
	}
	if result != nil {
		if err := json.Unmarshal(respObj.Result, result); err != nil {
			return fmt.Errorf("unmarshal RPC result: %v", err)
		}
	}
	return nil
}

func main() {
	// RPC client setup
	rpcURL := "http://127.0.0.1:8332"
	rpcUser := "Oliver"
	rpcPass := "satoshi"
	client := &http.Client{Timeout: 10 * time.Second}

	// 1. Fetch live block metadata
	var bcInfo struct {
		Blocks int64 `json:"blocks"`
	}
	if err := rpcCall(client, rpcURL, rpcUser, rpcPass, "getblockchaininfo", nil, &bcInfo); err != nil {
		log.Fatalf("getblockchaininfo RPC error: %v", err)
	}
	height := bcInfo.Blocks

	var prevHash string
	if err := rpcCall(client, rpcURL, rpcUser, rpcPass, "getblockhash", []interface{}{height}, &prevHash); err != nil {
		log.Fatalf("getblockhash RPC error: %v", err)
	}

	var bh struct {
		Bits string `json:"bits"`
		Time int64  `json:"time"`
	}
	if err := rpcCall(client, rpcURL, rpcUser, rpcPass, "getblockheader", []interface{}{prevHash, true}, &bh); err != nil {
		log.Fatalf("getblockheader RPC error: %v", err)
	}
	timestamp := uint32(bh.Time + 1)
	bitsVal, err := strconv.ParseUint(bh.Bits, 16, 32)
	if err != nil {
		log.Fatalf("invalid bits format: %v", err)
	}
	bits := uint32(bitsVal)

	// 2. Build and sign a 3-tx chain txSeed -> tx0 -> tx1
	const amountSat = 130000000000000
	wif, err := btcutil.DecodeWIF("KwtDeYuM1XAmDpcU8hbFg9DAKMGuxdYPEgUkvPSiuySkZd3HrwTn")
	if err != nil {
		log.Fatalf("invalid WIF key: %v", err)
	}

	txSeed := wire.NewMsgTx(wire.TxVersion)
	txSeed.AddTxIn(wire.NewTxIn(&wire.OutPoint{Hash: chainhash.Hash{}, Index: 0xffffffff}, nil, nil))
	seedAddr, _ := btcutil.NewAddressPubKey(wif.SerializePubKey(), &chaincfg.MainNetParams)
	seedScript, _ := txscript.PayToAddrScript(seedAddr)
	txSeed.AddTxOut(wire.NewTxOut(amountSat, seedScript))

	tx0 := wire.NewMsgTx(wire.TxVersion)
	seedHash := txSeed.TxHash()
	tx0.AddTxIn(wire.NewTxIn(wire.NewOutPoint(&seedHash, 0), nil, nil))
	tx0.AddTxOut(wire.NewTxOut(amountSat, seedScript))
	sig0, _ := txscript.SignatureScript(tx0, 0, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx0.TxIn[0].SignatureScript = sig0

	tx1 := wire.NewMsgTx(wire.TxVersion)
	tx0Hash := tx0.TxHash()
	tx1.AddTxIn(wire.NewTxIn(wire.NewOutPoint(&tx0Hash, 0), nil, nil))
	destAddr, _ := btcutil.DecodeAddress("bc1qa57c8e02usd0kjfucngktfrz5tukhr4u554y85", &chaincfg.MainNetParams)
	destScript, _ := txscript.PayToAddrScript(destAddr)
	tx1.AddTxOut(wire.NewTxOut(amountSat, destScript))
	sig1, _ := txscript.SignatureScript(tx1, 0, seedScript, txscript.SigHashAll, wif.PrivKey, true)
	tx1.TxIn[0].SignatureScript = sig1

	btcTxs := []*btcutil.Tx{btcutil.NewTx(txSeed), btcutil.NewTx(tx0), btcutil.NewTx(tx1)}
	mTree := blockchain.BuildMerkleTreeStore(btcTxs, false)
	merkleRoot := *mTree[len(mTree)-1]

	// 3. Build full 80-byte header: prefix (76 bytes) + 4-byte zero nonce
	const version = 0x20000000
	prevBytes, err := hex.DecodeString(prevHash)
	if err != nil {
		log.Fatalf("invalid prevHash hex: %v", err)
	}
	var prev chainhash.Hash
	copy(prev[:], reverseBytes(prevBytes))
	var mr chainhash.Hash
	copy(mr[:], reverseBytes(merkleRoot[:]))

	var hdrBuf bytes.Buffer
	// version, prev, merkleRoot, time, bits
	binary.Write(&hdrBuf, binary.LittleEndian, uint32(version))
	hdrBuf.Write(reverseBytes(prev[:]))
	hdrBuf.Write(reverseBytes(mr[:]))
	binary.Write(&hdrBuf, binary.LittleEndian, timestamp)
	binary.Write(&hdrBuf, binary.LittleEndian, bits)
	// append 4 zero bytes for nonce placeholder
	hdrBuf.Write([]byte{0, 0, 0, 0})
	// verify length and zero-nonce suffix
	if hdrBuf.Len() != 80 {
		log.Fatalf("header buffer length invalid: %d bytes", hdrBuf.Len())
	}
	headerHex := hex.EncodeToString(hdrBuf.Bytes())
	if !strings.HasSuffix(headerHex, "00000000") {
		log.Fatalf("headerHex must end with 00000000: %s", headerHex[len(headerHex)-8:])
	}
	log.Printf("[OK] HeaderHex constructed (80 bytes, ends with %s)", headerHex[len(headerHex)-8:])

	// 4. Solve for a valid nonce using external Z3 resolver
	cmd := exec.Command("python3", "z3_pow_resolver.py", "--header-hex", headerHex)
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		log.Fatalf("failed to get resolver stdout: %v", err)
	}
	scanner := bufio.NewScanner(stdout)
	if err := cmd.Start(); err != nil {
		log.Fatalf("failed to start PoW resolver: %v", err)
	}
	var nonce uint32
	for scanner.Scan() {
		line := scanner.Text()
		fmt.Println(line)
		if strings.HasPrefix(line, "Nonce: ") {
			parts := strings.Fields(line)
			n, err := strconv.ParseUint(parts[1], 10, 32)
			if err != nil {
				log.Fatalf("invalid nonce value: %v", err)
			}
			nonce = uint32(n)
			break
		}
	}
	if err := scanner.Err(); err != nil {
		log.Fatalf("reading resolver output: %v", err)
	}
	if err := cmd.Wait(); err != nil {
		log.Fatalf("resolver execution failed: %v", err)
	}

	// Validate nonce=0 only if header meets target
	// Build full header bytes with injected nonce
	hdrBytes, err := hex.DecodeString(headerHex)
	if err != nil {
		log.Fatalf("decode headerHex: %v", err)
	}
	fullHdr := make([]byte, len(hdrBytes))
	copy(fullHdr, hdrBytes)
	binary.LittleEndian.PutUint32(fullHdr[76:], nonce)
	// Double SHA256
	h1 := sha256.Sum256(fullHdr)
	h2 := sha256.Sum256(h1[:])
	revHash := reverseBytes(h2[:])
	// Compute target from bits
	target := blockchain.CompactToBig(bits)
	log.Printf("PoW hash: %x, target: %064x", revHash, target)
	if nonce == 0 && new(big.Int).SetBytes(revHash).Cmp(target) > 0 {
		log.Fatalf("nonce=0 invalid: PoW hash above target")
	}

	// 6. Assemble final block and submit
	blockHeader := &wire.BlockHeader{
		Version:    version,
		PrevBlock:  prev,
		MerkleRoot: merkleRoot,
		Timestamp:  time.Unix(int64(timestamp), 0),
		Bits:       bits,
		Nonce:      nonce,
	}
	block := wire.NewMsgBlock(blockHeader)
	block.Transactions = []*wire.MsgTx{txSeed, tx0, tx1}

	var blkBuf bytes.Buffer
	if err := block.Serialize(&blkBuf); err != nil {
		log.Fatalf("serialize block: %v", err)
	}
	rawHex := hex.EncodeToString(blkBuf.Bytes())
	fmt.Printf("tx1 TXID: %s\n", tx1.TxHash())
	fmt.Printf("Nonce: %d (0x%08x)\n", nonce, nonce)
	fmt.Printf("Block hash: %s\n", block.BlockHash())
	if err := submitBlockRPC(rawHex); err != nil {
		log.Fatalf("submitblock RPC error: %v", err)
	}
}
