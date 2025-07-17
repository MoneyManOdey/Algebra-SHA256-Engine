use sha2::{Digest, Sha256};

/// V-Energy PoW resolver in Rust (symbolic entropy collapse).
/// Applies logic-based folding of header entropy to directly derive a nonce
/// without brute-force search. Returns Some(nonce) if the computed PoW hash
/// meets the target, otherwise None.
pub fn ve_pow(header: [u8; 80], target: [u8; 32]) -> Option<u32> {
    // 1. Enhanced collapse: XOR-rotate and Hamming-weight profiling, skew, symmetry, primes
    let (xor_acc, hw_sum, skew_sum, skew_max) = header[..76]
        .chunks(4)
        .map(|chunk| {
            let mut arr = [0u8; 4];
            arr.copy_from_slice(chunk);
            let w = u32::from_be_bytes(arr);
            let rot = w.rotate_left((w & 0x1F) as u32);
            let hw = w.count_ones();
            // skew = ones - zeros in 32-bit word
            let sk = hw as i32 - (32 - hw) as i32;
            (rot, hw, sk, sk.abs() as u32)
        })
        .fold(
            (0u32, 0u32, 0i32, 0u32),
            |(acc, sum_hw, sum_sk, max_sk), (rot, hw, sk, abs_sk)| {
                (
                    acc ^ rot,
                    sum_hw.wrapping_add(hw),
                    sum_sk.wrapping_add(sk),
                    max_sk.max(abs_sk),
                )
            },
        );

    // average skew per segment
    let avg_skew = (skew_sum / (76 / 4) as i32) as u32;

    // symmetry reinforcement: fold 4-byte chunk pairs
    let sym_acc = header[..76]
        .chunks(4)
        .zip(header[..76].rchunks(4))
        .fold(0u32, |acc, (a, b)| {
            let wa = u32::from_be_bytes([a[0], a[1], a[2], a[3]]);
            let wb = u32::from_be_bytes([b[0], b[1], b[2], b[3]]);
            acc.wrapping_add((wa ^ wb).rotate_left(((wa ^ wb) & 0x0F) as u32))
        });

    // prime-byte focus: emphasize bytes at prime offsets
    const PRIMES: [usize; 21] = [
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
    ];
    let prime_sum = PRIMES
        .iter()
        .fold(0u32, |s, &i| s.wrapping_add(header[i] as u32));

    // 2. Combine features into initial nonce with weighted mixing constants
    let mut nonce = xor_acc
        .wrapping_mul(0x9E3779B1)
        .wrapping_add(hw_sum)
        .wrapping_add(avg_skew.rotate_left(3))
        .wrapping_add(skew_max.rotate_right(4))
        .wrapping_add(sym_acc.wrapping_mul(0x561CCF1F))
        .wrapping_add(prime_sum.wrapping_mul(0xDEADBEEF));

    // 3. Final avalanche mix to diffuse entropy
    nonce = nonce.rotate_left(((hw_sum & 0x1F) ^ ((avg_skew & 0x1F) << 1)) as u32);
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
