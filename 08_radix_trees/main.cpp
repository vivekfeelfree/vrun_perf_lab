/**
 * EXPERIMENT: Radix Trees for Longest Prefix Match
 * 
 * GOAL: Compare a prefix-aware tree against a standard balanced 
 * binary search tree (std::set).
 */

#include "../include/harness.hpp"
#include <vector>
#include <set>
#include <cstdint>

/**
 * A bit-level Radix Tree (Binary Trie).
 * This stores uint32_t keys by treating them as 32-bit paths.
 */
class BinaryRadixTree {
    struct Node {
        Node* children[2] = {nullptr, nullptr};
        bool is_end = false;
        uint32_t value = 0;
    };

    Node* root;

public:
    BinaryRadixTree() {
        root = new Node();
    }

    void insert(uint32_t key) {
        Node* curr = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (key >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = new Node();
            }
            curr = curr->children[bit];
        }
        curr->is_end = true;
        curr->value = key;
    }

    // Finds the longest prefix match for a key
    uint32_t longest_prefix_match(uint32_t key) const {
        Node* curr = root;
        uint32_t last_match = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (key >> i) & 1;
            if (!curr->children[bit]) break;
            curr = curr->children[bit];
            if (curr->is_end) last_match = curr->value;
        }
        return last_match;
    }
};

const int COUNT = 100'000;

int main() {
    std::cout << "--- Radix Tree Laboratory (" << COUNT << " keys) ---" << std::endl;

    std::vector<uint32_t> keys(COUNT);
    for(int i=0; i<COUNT; ++i) keys[i] = rand();

    // In a real scenario, we'd be matching against a smaller set 
    // of CIDR ranges. Here we simulate lookups.
    BinaryRadixTree radix;
    std::set<uint32_t> bst;

    for(int i=0; i < 1000; ++i) {
        radix.insert(keys[i]);
        bst.insert(keys[i]);
    }

    {
        lab::Benchmark b("std::set lower_bound (BST)");
        uint32_t sum = 0;
        for(int i=0; i<COUNT; ++i) {
            auto it = bst.lower_bound(keys[i]);
            if(it != bst.end()) sum += *it;
        }
        lab::escape(&sum);
    }

    {
        lab::Benchmark b("Radix Tree Match");
        uint32_t sum = 0;
        for(int i=0; i<COUNT; ++i) {
            sum += radix.longest_prefix_match(keys[i]);
        }
        lab::escape(&sum);
    }

    return 0;
}
