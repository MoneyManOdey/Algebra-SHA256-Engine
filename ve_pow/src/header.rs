use crate::rpc::HeaderInfo;
use bitcoin::blockdata::block::BlockHeader;
use bitcoin::consensus::encode;
use bitcoin::hash_types::TxMerkleNode;
use bitcoin::BlockHash;
use hex;

/// Build a header (without nonce) from fetched chain data.
/// Build a block header with given fields; nonce is zeroed initially.
pub fn build_header(info: &HeaderInfo) -> anyhow::Result<BlockHeader> {
    // Parse previous block hash from hex
    let prev: BlockHash = info.prev_hash.parse()?;
    // Placeholder merkle root of zeroes; replace with real merkle root later
    let merkle_root: TxMerkleNode = TxMerkleNode::default();
    Ok(BlockHeader {
        version: 0x20000000,
        prev_blockhash: prev,
        merkle_root,
        time: info.timestamp.into(),
        bits: info.bits,
        nonce: 0,
    })
}

/// After solving nonce, assemble full block and return hex-encoded wire format.
/// Inject nonce into header, serialize only header to hex (80 bytes).
pub fn assemble_block_hex(header: &BlockHeader, nonce: u32) -> anyhow::Result<String> {
    let mut hdr = header.clone();
    hdr.nonce = nonce;
    let bytes = encode::serialize(&hdr);
    Ok(hex::encode(bytes))
}

/// Parse a 76-byte header prefix (with zero nonce suffix) from hex into BlockHeader
pub fn parse_header_hex(hx: &str) -> anyhow::Result<BlockHeader> {
    let bytes = hex::decode(hx)?;
    // Header prefix must be exactly 80 bytes (76-byte prefix + 4-byte nonce)
    if bytes.len() != 80 {
        anyhow::bail!("header hex length is {}, expected 80 bytes", bytes.len());
    }
    let hdr: BlockHeader = encode::deserialize(&bytes)?;
    Ok(hdr)
}
