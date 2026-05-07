/**
 * EXPERIMENT: Arena Allocation vs. Standard Malloc
 * 
 * GOAL: Measure the performance impact of pointer-bump allocation
 * against a general-purpose memory allocator.
 */

#include "../include/harness.hpp"
#include "../include/arena.hpp"
#include <vector>

/**
 * A typical small object used in system software (e.g., a node in a 
 * compiler's Abstract Syntax Tree).
 */
struct Node {
    int id;
    Node* left;
    Node* right;
    char data[16];
};

const int ITERATIONS = 1'000'000;

/**
 * Baseline: Using standard malloc/free.
 * This incurs the overhead of the system's heap manager for every node.
 */
void bench_malloc() {
    std::vector<Node*> nodes;
    nodes.reserve(ITERATIONS);

    {
        lab::Benchmark b("Malloc Allocation");
        for (int i = 0; i < ITERATIONS; ++i) {
            Node* n = (Node*)std::malloc(sizeof(Node));
            n->id = i;
            nodes.push_back(n);
        }
        lab::clobber(); // Ensure the loop isn't optimized away
    }

    {
        lab::Benchmark b("Malloc Deallocation");
        for (auto n : nodes) {
            std::free(n);
        }
        lab::clobber();
    }
}

/**
 * Optimized: Using our Custom Arena.
 * Allocations are simple pointer increments. Deallocation is a single reset.
 */
void bench_arena() {
    // We initialize the arena with a 64MB initial block
    lab::Arena arena(64 * 1024 * 1024);
    std::vector<Node*> nodes;
    nodes.reserve(ITERATIONS);

    {
        lab::Benchmark b("Arena Allocation");
        for (int i = 0; i < ITERATIONS; ++i) {
            // No metadata overhead, no searching for free blocks.
            Node* n = (Node*)arena.alloc(sizeof(Node));
            n->id = i;
            nodes.push_back(n);
        }
        lab::clobber();
    }

    {
        lab::Benchmark b("Arena Deallocation (Reset)");
        // Instead of 1,000,000 free() calls, we just move one pointer.
        arena.reset();
        lab::clobber();
    }
}

int main() {
    std::cout << "--- Arena vs Malloc Benchmark (" << ITERATIONS << " nodes) ---" << std::endl;
    std::cout << "Size of Node: " << sizeof(Node) << " bytes" << std::endl;
    
    // Warm-up run to prime the OS heap and caches
    {
        bench_malloc();
        bench_arena();
    }
    
    // Experimental Run
    std::cout << "\nResults (Cold Run):" << std::endl;
    bench_malloc();
    bench_arena();

    return 0;
}
