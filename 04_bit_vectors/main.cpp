/**
 * EXPERIMENT: Bit-Vectors and SWAR (SIMD Within A Register)
 * 
 * GOAL: Compare bit-by-bit processing against word-level processing
 * to see the impact of bit-parallelism.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cstdint>

/**
 * A minimal Bit-Vector implementation designed for experimentation.
 */
class BitVector {
    std::vector<uint64_t> words;
    size_t n_bits;

public:
    BitVector(size_t bits) : n_bits(bits) {
        // We need (bits/64) rounded up words
        words.resize((bits + 63) / 64, 0);
    }

    void set(size_t bit_idx) {
        // Find which 64-bit word it falls into
        size_t word_idx = bit_idx / 64;
        // Find the bit offset within that word
        size_t bit_offset = bit_idx % 64;
        // Shift '1' to that position and OR it
        words[word_idx] |= (1ULL << bit_offset);
    }

    bool get(size_t bit_idx) const {
        size_t word_idx = bit_idx / 64;
        size_t bit_offset = bit_idx % 64;
        return (words[word_idx] >> bit_offset) & 1ULL;
    }

    /**
     * NAIVE: Count set bits by checking every single bit.
     * This simulates how a high-level programmer might do it.
     */
    size_t count_naive() const {
        size_t count = 0;
        for (size_t i = 0; i < n_bits; ++i) {
            if (get(i)) count++;
        }
        return count;
    }

    /**
     * OPTIMIZED (SWAR): Count set bits word-by-word using 
     * hardware-accelerated instructions.
     */
    size_t count_swar() const {
        size_t count = 0;
        for (uint64_t word : words) {
            // __builtin_popcountll translates to a single CPU 
            // instruction (e.g., 'popcnt' on x86 or 'cnt' on ARM64)
            count += __builtin_popcountll(word);
        }
        return count;
    }

    /**
     * NAIVE: Compute the union (OR) of two bit-vectors bit-by-bit.
     */
    static void union_naive(BitVector& res, const BitVector& a, const BitVector& b) {
        for (size_t i = 0; i < res.n_bits; ++i) {
            if (a.get(i) || b.get(i)) res.set(i);
        }
    }

    /**
     * OPTIMIZED (SWAR): Compute the union 64-bits at a time.
     */
    static void union_swar(BitVector& res, const BitVector& a, const BitVector& b) {
        for (size_t i = 0; i < res.words.size(); ++i) {
            res.words[i] = a.words[i] | b.words[i];
        }
    }
};

const int BIT_COUNT = 1'000'000;

int main() {
    std::cout << "--- Bit-Vector Laboratory (" << BIT_COUNT << " bits) ---" << std::endl;

    size_t mem = ((BIT_COUNT + 63) / 64) * sizeof(uint64_t);
    lab::print_qor("BitVector Footprint", mem);

    BitVector a(BIT_COUNT), b(BIT_COUNT), res(BIT_COUNT);
    
    // Fill every 3rd bit to give the population count some work
    for(int i=0; i < BIT_COUNT; i += 3) {
        a.set(i);
        if (i % 2 == 0) b.set(i);
    }

    // Benchmark 1: Population Count (The "Popcount" instruction)
    {
        lab::Benchmark bench("Count Bits (Naive)");
        size_t count = a.count_naive();
        lab::escape(&count);
    }

    {
        lab::Benchmark bench("Count Bits (SWAR/Popcount)");
        size_t count = a.count_swar();
        lab::escape(&count);
    }

    // Benchmark 2: Union Operation (The "OR" instruction)
    {
        lab::Benchmark bench("Union/OR (Naive)");
        BitVector::union_naive(res, a, b);
        lab::escape(&res);
    }

    {
        lab::Benchmark bench("Union/OR (SWAR)");
        BitVector::union_swar(res, a, b);
        lab::escape(&res);
    }

    return 0;
}
