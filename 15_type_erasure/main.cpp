/**
 * EXPERIMENT: Type Erasure and the Callback Tax
 * 
 * GOAL: Compare the performance of raw function pointers 
 * against std::function and custom type-erased wrappers.
 */

#include "../include/harness.hpp"
#include <vector>
#include <functional>

// --- Baseline: Raw Function Pointer ---
typedef int (*RawFunc)(int);
int increment(int x) { return x + 1; }

// --- Advanced: Custom Fixed-Size Function ---
// This is a common pattern in kernels to avoid the heap overhead
// of std::function.
template <size_t SBO_SIZE = 32>
class FixedFunction {
    char buffer[SBO_SIZE];
    int (*vcall)(void*, int);

public:
    template <typename F>
    FixedFunction(F f) {
        static_assert(sizeof(F) <= SBO_SIZE, "Lambda too large for SBO");
        new (buffer) F(f);
        vcall = [](void* b, int x) -> int {
            return (*reinterpret_cast<F*>(b))(x);
        };
    }

    int operator()(int x) {
        return vcall(buffer, x);
    }
};

const int ITERATIONS = 100'000'000;

int main() {
    std::cout << "--- Type Erasure Laboratory (" << ITERATIONS << " calls) ---" << std::endl;

    // 1. Raw Function Pointer
    {
        RawFunc f = increment;
        int val = 0;
        lab::Benchmark b("Raw Function Pointer");
        for(int i = 0; i < ITERATIONS; ++i) {
            val = f(val);
        }
        lab::escape(&val);
    }

    // 2. std::function
    {
        std::function<int(int)> f = [](int x) { return x + 1; };
        int val = 0;
        lab::Benchmark b("std::function");
        for(int i = 0; i < ITERATIONS; ++i) {
            val = f(val);
        }
        lab::escape(&val);
    }

    // 3. FixedFunction (Manual Type Erasure)
    {
        FixedFunction<32> f = [](int x) { return x + 1; };
        int val = 0;
        lab::Benchmark b("FixedFunction (Custom SBO)");
        for(int i = 0; i < ITERATIONS; ++i) {
            val = f(val);
        }
        lab::escape(&val);
    }

    return 0;
}
