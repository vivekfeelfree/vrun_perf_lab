/**
 * EXPERIMENT: Technology Mapping via Dynamic Programming
 * 
 * GOAL: Compare Area-Optimized vs. Delay-Optimized mapping 
 * in a logic synthesis context.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>
#include <limits>

struct Gate {
    std::string name;
    int inputs;
    float area;
    float delay;
};

struct Node {
    Node *left = nullptr, *right = nullptr;
    float best_area = std::numeric_limits<float>::max();
    float best_delay = std::numeric_limits<float>::max();
};

/**
 * Technology Mapper (DP)
 */
class TechMapper {
    std::vector<Gate> library;

public:
    TechMapper() {
        // Simple Library
        library.push_back({"AND2", 2, 2.0f, 1.0f});
        library.push_back({"AND3", 3, 3.5f, 1.2f}); // Better area than 2x AND2
    }

    // DP for Area
    void map_area(Node* n) {
        if (!n->left && !n->right) {
            n->best_area = 0; // Leaf
            return;
        }

        if (n->left) map_area(n->left);
        if (n->right) map_area(n->right);

        // Option 1: Use AND2
        float cost_and2 = 2.0f;
        if (n->left) cost_and2 += n->left->best_area;
        if (n->right) cost_and2 += n->right->best_area;
        
        n->best_area = cost_and2;
        
        // Option 2: Use AND3 (Matches a node and its child)
        // This is a simplified tree match
        if (n->left && n->left->left) {
             float cost_and3 = 3.5f + n->right->best_area + n->left->left->best_area + n->left->right->best_area;
             n->best_area = std::min(n->best_area, cost_and3);
        }
    }

    // DP for Delay
    void map_delay(Node* n) {
        if (!n->left && !n->right) {
            n->best_delay = 0; // Arrival time 0
            return;
        }

        if (n->left) map_delay(n->left);
        if (n->right) map_delay(n->right);

        // Arrival time = max(input arrival) + gate delay
        float d_left = n->left ? n->left->best_delay : 0;
        float d_right = n->right ? n->right->best_delay : 0;
        
        n->best_delay = std::max(d_left, d_right) + 1.0f; // Using AND2
    }
};

/**
 * Helper to build a deep tree
 */
Node* build_tree(int depth) {
    if (depth <= 0) return new Node();
    Node* n = new Node();
    n->left = build_tree(depth - 1);
    n->right = build_tree(depth - 1);
    return n;
}

int main() {
    int DEPTH = 12;
    std::cout << "--- Technology Mapping Laboratory (Depth " << DEPTH << ") ---" << std::endl;

    Node* root = build_tree(DEPTH);
    TechMapper mapper;

    {
        lab::Benchmark b("Area-Optimized Mapping");
        mapper.map_area(root);
        lab::print_qor("Area Result", (size_t)root->best_area, 0);
    }

    {
        lab::Benchmark b("Delay-Optimized Mapping");
        mapper.map_delay(root);
        lab::print_qor("Delay Result", (size_t)root->best_delay, 0);
    }

    return 0;
}
