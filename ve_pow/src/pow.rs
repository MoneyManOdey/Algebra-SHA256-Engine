use sha2::{Digest, Sha256};

/// V-Energy PoW resolver in Rust (symbolic entropy collapse).
/// Applies logic-based folding of header entropy to directly derive a nonce
/// without brute-force search. Returns Some(nonce) if the computed PoW hash
/// meets the target, otherwise None.
pub fn ve_pow(header: [u8; 80], target: [u8; 32]) -> Option<u32> {
    // 1. Fold 76-byte header entropy into XOR accumulator and Hamming-weight sum
    let (xor_acc, hw_sum) = header[..76]
        .chunks(4)
        .map(|chunk| {
            let mut arr = [0u8; 4];
            arr.copy_from_slice(chunk);
            let w = u32::from_be_bytes(arr);
            let rot = w.rotate_left((w & 0x1F) as u32);
            let hw = w.count_ones();
            (rot, hw)
        })
        .fold((0u32, 0u32), |(xa, hs), (rot, hw)| {
            (xa ^ rot, hs.wrapping_add(hw))
        });

    // 2. Collapse into a single 32-bit nonce via mix of XOR-accumulator and Hamming sum
    let mut nonce = xor_acc.wrapping_mul(0x9E3779B1).wrapping_add(hw_sum);

    // 3. Inject nonce into header bytes (little-endian) and compute Double SHA-256
    let mut block = header;
    block[76..80].copy_from_slice(&nonce.to_le_bytes());
    let hash1 = Sha256::digest(&block);
    let hash2 = Sha256::digest(&hash1);

    // 4. Compare big-endian hash output against target; accept or reject
    if hash2.as_slice() <= &target[..] {
        Some(nonce)
    } else {
        None
    }
}
