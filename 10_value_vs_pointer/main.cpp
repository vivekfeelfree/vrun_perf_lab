/**
 * EXPERIMENT: Value Semantics vs. Pointer Semantics
 * 
 * GOAL: Demonstrate the impact of memory fragmentation and indirection
 * on CPU cache performance.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>
#include <random>

/**
 * A typical "Entity" in a system (e.g., a gate in EDA or a node in a compiler).
 */
struct Entity {
    float x, y, z;
    int id;
    char padding[32]; // Simulate a medium-sized object

    void update() {
        x += 1.0f;
        y += 2.0f;
    }
};

/**
 * Data-Oriented version: Structure of Arrays (SoA)
 * We only store the "hot" data (x, y) contiguously.
 */
struct EntitySoA {
    std::vector<float> x;
    std::vector<float> y;

    EntitySoA(size_t n) {
        x.resize(n, 0.0f);
        y.resize(n, 0.0f);
    }

    void update_all() {
        for(size_t i = 0; i < x.size(); ++i) {
            x[i] += 1.0f;
            y[i] += 2.0f;
        }
    }
};

const int COUNT = 1'000'000;

int main() {
    std::cout << "--- Value vs. Pointer Semantics (" << COUNT << " objects) ---" << std::endl;

    // 1. Vector of Pointers (OOD approach)
    // We intentionally allocate them individually to simulate heap fragmentation.
    std::vector<Entity*> pointer_vec;
    for(int i = 0; i < COUNT; ++i) {
        pointer_vec.push_back(new Entity());
    }

    // 2. Vector of Values (AoS - Array of Structures)
    std::vector<Entity> value_vec(COUNT);

    // 3. Structure of Arrays (SoA)
    EntitySoA soa_vec(COUNT);

    // Experiment A: Pointer Update
    {
        lab::Benchmark b("Pointer Semantics (Scattered)");
        for(auto* e : pointer_vec) {
            e->update();
        }
        lab::clobber();
    }

    // Experiment B: Value Update (AoS)
    {
        lab::Benchmark b("Value Semantics (Contiguous)");
        for(auto& e : value_vec) {
            e.update();
        }
        lab::clobber();
    }

    // Experiment C: SoA Update
    {
        lab::Benchmark b("SoA (Structure of Arrays)");
        soa_vec.update_all();
        lab::clobber();
    }

    // CRITICAL TEST: What if the pointers are shuffled?
    // This happens in real-world systems as objects are created/destroyed.
    std::shuffle(pointer_vec.begin(), pointer_vec.end(), std::mt19937(std::random_device()()));
    
    {
        lab::Benchmark b("Pointer Semantics (SHUFFLED)");
        for(auto* e : pointer_vec) {
            e->update();
        }
        lab::clobber();
    }

    // Cleanup
    for(auto* e : pointer_vec) delete e;

    return 0;
}
