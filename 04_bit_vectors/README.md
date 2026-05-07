# Module 04: Bit-Vectors & Bit-Parallelism (SWAR)

## The Core Problem: Set Operations at Scale
Imagine a compiler performing "Liveness Analysis." For every instruction, it needs to keep track of which variables (out of maybe 1,000) are "alive."
- A `std::vector<int>` would be slow to search.
- A `std::set<int>` would involve 1,000 node allocations and pointer chasing.

## 1. The Bit-Vector Solution
A Bit-Vector stores each boolean "presence" as a single bit. A set of 64 items fits into a single `uint64_t` register.

### Memory Density:
- `std::vector<char>`: 8,000 bits for 1,000 items.
- `lab::BitVector`: 1,000 bits for 1,000 items (8x saving).

## 2. Mechanical Sympathy: SWAR
**SWAR** stands for "SIMD Within A Register." Instead of looping through every bit, we treat the data as a series of 64-bit "words."

If we want to find the **Union** of two sets:
- **Naive:** Loop 64 times, check each bit.
- **SWAR:** `word_c = word_a | word_b;` (1 instruction handles 64 items).

If we want to count the number of items in a set:
- **Naive:** Loop 64 times, increment counter if bit is 1.
- **Hardware:** `__builtin_popcountll(word_a);` (1 instruction uses dedicated CPU circuitry).

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **Naive Loop:** Checking bits one by one.
2.  **Word-level Logic:** Using bitwise operators on entire blocks.
3.  **Hardware Intrinsics:** Using the `popcount` instruction.

## 🎛 Experimental Controls
- **Bit Density:** How does performance change if the bit-vector is 90% full vs 1% full?
- **Vector Size:** Increase the size beyond the L1 cache (approx 32KB) and see how the gap between naive and SWAR widening.
