/**
 * EXPERIMENT: Memory Layout and Cache Efficiency
 * 
 * GOAL: Demonstrate how struct member ordering affects memory footprint
 * and iteration speed.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>
#include <cstddef>

/**
 * SCENARIO A: The "Naive" Layout
 * Variables are placed without regard for alignment, forcing the compiler
 * to insert padding bytes to satisfy the CPU's alignment requirements.
 */
struct BadStruct {
    char a;      // 1 byte. Next member 'b' is 8-bytes, requires 8-byte alignment.
                 // Compiler inserts 7 bytes of padding here.
    double b;    // 8 bytes.
    char c;      // 1 byte. Next member 'd' is 4-bytes, requires 4-byte alignment.
                 // Compiler inserts 3 bytes of padding here.
    int d;       // 4 bytes.
                 // Total size must be a multiple of the largest member (8).
                 // Compiler inserts 4 bytes of tail padding.
};

/**
 * SCENARIO B: The "Optimized" Layout
 * Members are sorted by size (Descending). This allows smaller types to 
 * "fill the holes" left by larger types, minimizing waste.
 */
struct GoodStruct {
    double b;    // 8 bytes. No padding needed before.
    int d;       // 4 bytes. 4 is a divisor of 8, so it fits nicely.
    char a;      // 1 byte.
    char c;      // 1 byte.
                 // Total: 14 bytes used. Padded to 16 to keep 8-byte alignment.
};

/**
 * Introspection: Prints the exact memory map of the structs.
 */
void inspect_layouts() {
    std::cout << "--- Memory Layout Introspection ---" << std::endl;
    
    std::cout << "BadStruct (" << sizeof(BadStruct) << " bytes):" << std::endl;
    std::cout << "  [Offset 0]  char a   (1 byte)" << std::endl;
    std::cout << "  [Offset 1]  PADDING  (7 bytes)" << std::endl;
    std::cout << "  [Offset 8]  double b (8 bytes)" << std::endl;
    std::cout << "  [Offset 16] char c   (1 byte)" << std::endl;
    std::cout << "  [Offset 17] PADDING  (3 bytes)" << std::endl;
    std::cout << "  [Offset 20] int d    (4 bytes)" << std::endl;
    std::cout << "  [Offset 24] PADDING  (4 bytes)" << std::endl;

    std::cout << "\nGoodStruct (" << sizeof(GoodStruct) << " bytes):" << std::endl;
    std::cout << "  [Offset 0]  double b (8 bytes)" << std::endl;
    std::cout << "  [Offset 8]  int d    (4 bytes)" << std::endl;
    std::cout << "  [Offset 12] char a   (1 byte)" << std::endl;
    std::cout << "  [Offset 13] char c   (1 byte)" << std::endl;
    std::cout << "  [Offset 14] PADDING  (2 bytes)" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

const int ELEMENT_COUNT = 10'000'000;

int main() {
    inspect_layouts();

    std::cout << "Running iteration benchmark with " << ELEMENT_COUNT << " elements..." << std::endl;

    // Experiment 1: Measuring the impact of the larger struct
    {
        std::vector<BadStruct> data(ELEMENT_COUNT);
        lab::print_qor("Bad Layout", sizeof(BadStruct) * ELEMENT_COUNT);
        lab::Benchmark b("Bad Layout (24 bytes)");
        double sum = 0;
        for(auto& item : data) {
            sum += item.b; // High-frequency access
            item.d += 1;
        }
        lab::escape(&sum);
    }

    // Experiment 2: Measuring the impact of the packed struct
    {
        std::vector<GoodStruct> data(ELEMENT_COUNT);
        lab::print_qor("Good Layout", sizeof(GoodStruct) * ELEMENT_COUNT);
        lab::Benchmark b("Good Layout (16 bytes)");
        double sum = 0;
        for(auto& item : data) {
            sum += item.b; // High-frequency access
            item.d += 1;
        }
        lab::escape(&sum);
    }

    return 0;
}
