use sha2::{Digest, Sha256};

/// V-Energy PoW resolver in Rust (symbolic entropy collapse).
/// Applies logic-based folding of header entropy to directly derive a nonce
/// without brute-force search. Returns Some(nonce) if the computed PoW hash
/// meets the target, otherwise None.
pub fn ve_pow(header: [u8; 80], target: [u8; 32]) -> Option<u32> {
    // 1. Primary collapse: XOR-rotate folding of 4-byte words and Hamming-weight sum
    let (xor_acc, hw_sum) = header[..76]
        .chunks(4)
        .map(|chunk| {
            let mut arr = [0u8; 4];
            arr.copy_from_slice(chunk);
            let w = u32::from_be_bytes(arr);
            (w.rotate_left((w & 0x1F) as u32), w.count_ones())
        })
        .fold((0u32, 0u32), |(acc, sum), (rot, hw)| {
            (acc ^ rot, sum.wrapping_add(hw))
        });

    // 2. Skew bias: difference between high-bit and low-bit byte counts
    let (hi_cnt, lo_cnt) = header[..76].iter().fold((0u32, 0u32), |(hi, lo), &b| {
        if b & 0x80 != 0 {
            (hi + 1, lo)
        } else {
            (hi, lo + 1)
        }
    });
    let skew = hi_cnt.wrapping_sub(lo_cnt);

    // 3. Symmetry pairing: XOR each byte with its mirrored counterpart
    let sym_acc = header[..76]
        .iter()
        .zip(header[..76].iter().rev())
        .fold(0u32, |acc, (&a, &b)| {
            acc ^ ((a as u32) << ((b & 0x07) as u32))
        });

    // 4. Prime-index folding: sum bytes at prime offsets to capture sparse entropy
    const PRIMES: [usize; 21] = [
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
    ];
    let prime_sum = PRIMES
        .iter()
        .fold(0u32, |sum, &i| sum.wrapping_add(header[i] as u32));

    // 5. Mix all entropy features into initial nonce
    let mut nonce = xor_acc
        .wrapping_mul(0x9E3779B1)
        .wrapping_add(hw_sum)
        .wrapping_add(skew.rotate_left(5))
        .wrapping_add(sym_acc.wrapping_mul(0x3C6EF372))
        .wrapping_add(prime_sum.rotate_right(7));

    // 6. Final avalanche mix: rotate by low-order bits and avalanche constant
    nonce = nonce.rotate_left((hw_sum & 0x1F) as u32);
    nonce = nonce.wrapping_mul(0x85EBCA6B).wrapping_add(0xC2B2AE35);

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
