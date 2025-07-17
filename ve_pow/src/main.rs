use clap::Parser;

mod header;
mod pow;
mod rpc;

/// V-Energy PoW CLI
#[derive(Parser)]
#[command(name = "ve_pow")]
struct Cli {
    /// Run full pipeline automatically
    #[arg(long)]
    auto: bool,
    /// Output JSON metrics
    #[arg(long)]
    json: bool,
    /// Submit block to Bitcoin Core
    #[arg(long)]
    submit: bool,
    /// Hex-encoded 76-byte header prefix for collapse (no nonce)
    #[arg(long)]
    header_hex: Option<String>,
}

fn main() -> anyhow::Result<()> {
    let cli = Cli::parse();

    // 1. Build or parse the block header prefix (nonce=0)
    let header = if let Some(hx) = &cli.header_hex {
        // Use provided 76-byte header hex (no nonce)
        header::parse_header_hex(hx)?
    } else {
        // Fetch live metadata and build header
        let height = rpc::fetch_tip_height()?;
        let prev_hash = rpc::fetch_prev_block_hash(height)?;
        let (bits, timestamp) = rpc::fetch_block_header(&prev_hash)?;
        header::build_header(&rpc::HeaderInfo {
            prev_hash,
            bits,
            timestamp,
        })?
    };

    // 3. Perform V-Energy collapse: fold header entropy into nonce and verify PoW
    // Serialize header into byte array for the symbolic solver
    let mut hdr_bytes = [0u8; 80];
    {
        let buf = bitcoin::consensus::encode::serialize(&header);
        hdr_bytes.copy_from_slice(&buf);
    }
    // Placeholder target: derive actual target bytes from header.bits when integrating
    let target = [0u8; 32];
    if let Some(nonce) = pow::ve_pow(hdr_bytes, target) {
        println!("Determined nonce: {} (0x{:08x})", nonce, nonce);
        let block_hex = header::assemble_block_hex(&header, nonce)?;
        if cli.submit {
            let resp = rpc::submit_block(&block_hex)?;
            println!("submitblock response: {}", resp);
        } else {
            println!("Block hex: {}", block_hex);
        }
    } else {
        println!("V-Energy collapse failed: no valid nonce generated");
    }
    Ok(())
}
