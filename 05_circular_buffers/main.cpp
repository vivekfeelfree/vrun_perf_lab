/**
 * EXPERIMENT: Circular Buffers and Power-of-Two Optimization
 * 
 * GOAL: Measure the performance difference between the modulo operator (%)
 * and bitwise masking (&) for circular indexing.
 */

#include "../include/harness.hpp"
#include <vector>

/**
 * Standard Circular Buffer using the modulo (%) operator.
 * Can be any size.
 */
class ModuloBuffer {
    std::vector<int> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t size;

public:
    ModuloBuffer(size_t s) : size(s) {
        buffer.resize(size);
    }

    void push(int val) {
        buffer[tail] = val;
        tail = (tail + 1) % size; // Expensive Modulo
    }

    int pop() {
        int val = buffer[head];
        head = (head + 1) % size; // Expensive Modulo
        return val;
    }
};

/**
 * Optimized Circular Buffer using bitwise masking (&).
 * MUST be a power of two.
 */
class MaskBuffer {
    std::vector<int> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t mask;

public:
    MaskBuffer(size_t size_pow2) {
        buffer.resize(size_pow2);
        mask = size_pow2 - 1; // e.g., if size is 1024 (0b10000000000), mask is 1023 (0b01111111111)
    }

    void push(int val) {
        buffer[tail] = val;
        tail = (tail + 1) & mask; // Lightning fast AND
    }

    int pop() {
        int val = buffer[head];
        head = (head + 1) & mask; // Lightning fast AND
        return val;
    }
};

const int OPERATIONS = 10'000'000;

int main() {
    std::cout << "--- Circular Buffer Laboratory (" << OPERATIONS << " ops) ---" << std::endl;

    // We compare 1000 (Non-Power-of-Two) vs 1024 (Power-of-Two)
    lab::print_qor("Modulo Buffer", 1000 * sizeof(int));
    ModuloBuffer mod_buf(1000);
    
    lab::print_qor("Mask Buffer", 1024 * sizeof(int));
    MaskBuffer mask_buf(1024);

    {
        lab::Benchmark bench("Modulo Buffer (%) Push/Pop");
        for (int i = 0; i < OPERATIONS; ++i) {
            mod_buf.push(i);
            int val = mod_buf.pop();
            lab::escape(&val);
        }
    }

    {
        lab::Benchmark bench("Mask Buffer (&) Push/Pop");
        for (int i = 0; i < OPERATIONS; ++i) {
            mask_buf.push(i);
            int val = mask_buf.pop();
            lab::escape(&val);
        }
    }

    return 0;
}
