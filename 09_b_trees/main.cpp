/**
 * EXPERIMENT: B-Trees vs. Binary Search Trees (std::set)
 * 
 * GOAL: Demonstrate how increasing the branching factor reduces 
 * memory latency by minimizing the number of cache misses.
 */

#include "../include/harness.hpp"
#include <vector>
#include <set>
#include <algorithm>

/**
 * A simplified, memory-resident B-Tree.
 * M is the order (max children).
 */
template <typename T, int M>
class BTree {
    struct Node {
        int count = 0;
        T keys[M-1];
        Node* children[M] = {nullptr};
        bool leaf = true;
    };

    Node* root;

    void split_child(Node* parent, int i, Node* full_node) {
        Node* next_node = new Node();
        next_node->leaf = full_node->leaf;
        next_node->count = (M/2) - 1;

        for (int j = 0; j < (M/2) - 1; j++)
            next_node->keys[j] = full_node->keys[j + M/2];

        if (!full_node->leaf) {
            for (int j = 0; j < M/2; j++)
                next_node->children[j] = full_node->children[j + M/2];
        }

        full_node->count = (M/2) - 1;

        for (int j = parent->count; j >= i + 1; j--)
            parent->children[j + 1] = parent->children[j];
        
        parent->children[i + 1] = next_node;

        for (int j = parent->count - 1; j >= i; j--)
            parent->keys[j + 1] = parent->keys[j];

        parent->keys[i] = full_node->keys[(M/2) - 1];
        parent->count++;
    }

    void insert_non_full(Node* node, T k) {
        int i = node->count - 1;
        if (node->leaf) {
            while (i >= 0 && k < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = k;
            node->count++;
        } else {
            while (i >= 0 && k < node->keys[i]) i--;
            i++;
            if (node->children[i]->count == M - 1) {
                split_child(node, i, node->children[i]);
                if (k > node->keys[i]) i++;
            }
            insert_non_full(node->children[i], k);
        }
    }

public:
    BTree() { root = new Node(); }

    void insert(T k) {
        if (root->count == M - 1) {
            Node* s = new Node();
            s->leaf = false;
            s->children[0] = root;
            split_child(s, 0, root);
            root = s;
        }
        insert_non_full(root, k);
    }

    bool search(T k) const {
        Node* curr = root;
        while (curr) {
            int i = 0;
            while (i < curr->count && k > curr->keys[i]) i++;
            if (i < curr->count && k == curr->keys[i]) return true;
            if (curr->leaf) return false;
            curr = curr->children[i];
        }
        return false;
    }
};

const int COUNT = 100'000;

int main() {
    std::cout << "--- B-Tree Laboratory (" << COUNT << " elements) ---" << std::endl;

    std::vector<int> data(COUNT);
    for(int i=0; i<COUNT; ++i) data[i] = rand();

    // Comparison set
    std::set<int> bst;
    BTree<int, 16> btree; // Order 16: Roughly two cache lines per node

    for(int x : data) {
        bst.insert(x);
        btree.insert(x);
    }

    lab::print_qor("std::set (BST)", COUNT * 32);
    {
        lab::Benchmark b("std::set Lookup");
        long long found = 0;
        for(int x : data) if(bst.count(x)) found++;
        lab::escape(&found);
    }

    lab::print_qor("B-Tree (Order 16)", COUNT * sizeof(int) * 2); // Heuristic: ~2x overhead for keys + pointers
    {
        lab::Benchmark b("B-Tree (Order 16) Lookup");
        long long found = 0;
        for(int x : data) if(btree.search(x)) found++;
        lab::escape(&found);
    }

    return 0;
}
