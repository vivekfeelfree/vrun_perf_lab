/**
 * EXPERIMENT: Move Semantics and RVO
 * 
 * GOAL: Measure the performance difference between deep copying 
 * and "stealing" resources (Move Semantics).
 */

#include "../include/harness.hpp"
#include <vector>
#include <cstring>

class HeavyObject {
    int* data;
    size_t size;

public:
    static size_t copies;
    static size_t moves;

    HeavyObject(size_t n) : size(n) {
        data = new int[n];
    }

    // Copy Constructor (Expensive)
    HeavyObject(const HeavyObject& other) : size(other.size) {
        data = new int[size];
        std::memcpy(data, other.data, size * sizeof(int));
        copies++;
    }

    // Move Constructor (Cheap)
    HeavyObject(HeavyObject&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        moves++;
    }

    ~HeavyObject() { delete[] data; }

    // Dummy method to prevent optimization
    void work() { if(data) data[0] = 1; }
};

size_t HeavyObject::copies = 0;
size_t HeavyObject::moves = 0;

// Function returning by value (Tests RVO/Move)
HeavyObject create_heavy() {
    return HeavyObject(1000);
}

const int ITERATIONS = 1'000'000;

int main() {
    std::cout << "--- Move Semantics Laboratory (" << ITERATIONS << " ops) ---" << std::endl;

    // 1. Benchmark Copying
    {
        HeavyObject base(1000);
        HeavyObject::copies = 0;
        lab::Benchmark b("Deep Copying");
        for(int i = 0; i < ITERATIONS; ++i) {
            HeavyObject copy(base);
            lab::escape(&copy);
        }
        std::cout << "   (Copies made: " << HeavyObject::copies << ")" << std::endl;
    }

    // 2. Benchmark Moving
    {
        HeavyObject::moves = 0;
        lab::Benchmark b("Move Semantics");
        for(int i = 0; i < ITERATIONS; ++i) {
            HeavyObject source(1000);
            HeavyObject target(std::move(source));
            lab::escape(&target);
        }
        std::cout << "   (Moves made: " << HeavyObject::moves << ")" << std::endl;
    }

    // 3. Benchmark RVO (The compiler "Cheating")
    {
        HeavyObject::copies = 0;
        HeavyObject::moves = 0;
        lab::Benchmark b("RVO (Return Value Optimization)");
        for(int i = 0; i < ITERATIONS; ++i) {
            HeavyObject obj = create_heavy();
            lab::escape(&obj);
        }
        std::cout << "   (Copies: " << HeavyObject::copies << ", Moves: " << HeavyObject::moves << ")" << std::endl;
        std::cout << "   Note: If both are 0, RVO elided the operation entirely!" << std::endl;
    }

    return 0;
}
