use reqwest::blocking::Client;
use serde::{de::DeserializeOwned, Deserialize};
use serde_json::{json, Value};
use std::time::Duration;

/// Simplified header info: previous hash, bits, timestamp
pub struct HeaderInfo {
    pub prev_hash: String,
    pub bits: u32,
    pub timestamp: u32,
}

/// Execute a JSON-RPC call and parse result as T
fn rpc_call<T: DeserializeOwned>(method: &str, params: &[Value]) -> anyhow::Result<T> {
    let client = Client::builder().timeout(Duration::from_secs(5)).build()?;
    let req = json!({"jsonrpc":"2.0","id":1,"method":method,"params":params});
    let resp = client
        .post("http://127.0.0.1:8332")
        .basic_auth("Oliver", Some("satoshi"))
        .json(&req)
        .send()?;
    let resp_json: Value = resp.json()?;
    if let Some(err) = resp_json.get("error") {
        anyhow::bail!("RPC error: {}", err);
    }
    let result = resp_json
        .get("result")
        .ok_or_else(|| anyhow::anyhow!("no result field"))?;
    let parsed = serde_json::from_value(result.clone())?;
    Ok(parsed)
}

/// Fetch current tip height via getblockchaininfo
pub fn fetch_tip_height() -> anyhow::Result<u64> {
    #[derive(Deserialize)]
    struct Info {
        blocks: u64,
    }
    let info: Info = rpc_call("getblockchaininfo", &[])?;
    Ok(info.blocks)
}

/// Fetch previous block hash via getblockhash
pub fn fetch_prev_block_hash(height: u64) -> anyhow::Result<String> {
    let hash: String = rpc_call("getblockhash", &[json!(height)])?;
    Ok(hash)
}

/// Fetch bits and timestamp for given block hash via getblockheader
pub fn fetch_block_header(hash: &str) -> anyhow::Result<(u32, u32)> {
    #[derive(Deserialize)]
    struct Hdr {
        bits: String,
        time: u32,
    }
    let hdr: Hdr = rpc_call("getblockheader", &[json!(hash)])?;
    // Core returns bits as hex string, e.g. "17023aa6"
    let bits_val = u32::from_str_radix(&hdr.bits, 16)
        .map_err(|e| anyhow::anyhow!("invalid bits hex '{}': {}", hdr.bits, e))?;
    Ok((bits_val, hdr.time + 1))
}

/// Submit a hex-encoded block via submitblock RPC
pub fn submit_block(block_hex: &str) -> anyhow::Result<String> {
    let res: Option<String> = rpc_call("submitblock", &[json!(block_hex)])?;
    Ok(res.unwrap_or_default())
}

/// Generate 'count' blocks (regtest only) via RPC generate
pub fn generate_block(count: usize) -> anyhow::Result<Vec<String>> {
    // For Core v24+, use generatetoaddress RPC in regtest
    // Acquire a new regtest address
    // Ensure a wallet is loaded for regtest (deprecated default wallet)
    let _ = rpc_call::<serde_json::Value>(
        "createwallet",
        &[json!("ve_pow"), json!(false), json!(false), json!("")],
    );
    // Get an address to mine to
    let addr: String = rpc_call("getnewaddress", &[])?;
    // Mine 'count' blocks to that address
    let resp: Vec<String> = rpc_call("generatetoaddress", &[json!(count), json!(addr)])?;
    Ok(resp)
}

/// Retrieve block hex via RPC getblock
pub fn get_block_hex(hash: &str) -> anyhow::Result<String> {
    let resp: String = rpc_call("getblock", &[json!(hash), json!(false)])?;
    Ok(resp)
}
