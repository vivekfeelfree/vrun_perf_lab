/**
 * EXPERIMENT: SIMD-Accelerated String Search (ARM NEON)
 * 
 * GOAL: Compare a byte-by-byte search against a 16-byte parallel
 * search using ARM64 NEON intrinsics.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>
#include <arm_neon.h>

/**
 * NAIVE: Standard byte-by-byte search.
 */
size_t count_char_naive(const char* data, size_t len, char target) {
    size_t count = 0;
    for (size_t i = 0; i < len; ++i) {
        if (data[i] == target) count++;
    }
    return count;
}

/**
 * OPTIMIZED: ARM NEON SIMD search.
 * Processes 16 bytes at a time.
 */
size_t count_char_neon(const char* data, size_t len, char target) {
    size_t count = 0;
    size_t i = 0;

    // Create a vector filled with the target character (16 times)
    uint8x16_t v_target = vdupq_n_u8(static_cast<uint8_t>(target));

    // Process in 16-byte chunks
    for (; i + 16 <= len; i += 16) {
        // 1. Load 16 bytes from memory
        uint8x16_t v_data = vld1q_u8(reinterpret_cast<const uint8_t*>(data + i));

        // 2. Compare data against target (Parallel comparison)
        // Returns 0xFF for match, 0x00 for no match
        uint8x16_t v_mask = vceqq_u8(v_data, v_target);

        // 3. Horizontal check: If any matches found
        // Note: For a true 'count', we would sum the bits, but for this lab
        // we will use a simpler check or bit-counting approach.
        // Let's perform a simple sum of the mask.
        // Since match = 0xFF (-1 in signed), we can use horizontal addition.
        uint8_t max_val = vmaxvq_u8(v_mask);
        if (max_val > 0) {
            // If there's at least one match, fallback to check which ones 
            // (or use more complex bit-manipulation for exact count)
            for (size_t j = 0; j < 16; ++j) {
                if (data[i + j] == target) count++;
            }
        }
    }

    // Clean up remaining bytes
    for (; i < len; ++i) {
        if (data[i] == target) count++;
    }

    return count;
}

const size_t STR_SIZE = 10'000'000;

int main() {
    std::cout << "--- ARM NEON SIMD Laboratory (" << STR_SIZE << " chars) ---" << std::endl;

    // Create a large string with some matches
    std::string text(STR_SIZE, 'a');
    for(size_t i = 0; i < STR_SIZE; i += 100) {
        text[i] = 'z'; // The target
    }

    char target = 'z';

    {
        lab::Benchmark b("Naive Search (Byte-by-Byte)");
        size_t count = count_char_naive(text.data(), text.size(), target);
        lab::escape(&count);
        std::cout << "   (Matches found: " << count << ")" << std::endl;
    }

    {
        lab::Benchmark b("NEON SIMD Search (16-byte)");
        size_t count = count_char_neon(text.data(), text.size(), target);
        lab::escape(&count);
        std::cout << "   (Matches found: " << count << ")" << std::endl;
    }

    return 0;
}
