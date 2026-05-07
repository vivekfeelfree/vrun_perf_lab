/**
 * EXPERIMENT: Sparse Sets
 * 
 * GOAL: Demonstrate the Sparse Set data structure, which provides O(1) 
 * insertion, deletion, and lookup, while also allowing O(N) dense 
 * iteration (ideal for ECS systems).
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

class SparseSet {
    std::vector<int> sparse;
    std::vector<int> dense;
    int capacity;
    int size;

public:
    SparseSet(int max_val) : capacity(max_val), size(0) {
        sparse.resize(max_val, -1);
        dense.reserve(max_val);
    }

    bool contains(int x) const {
        if (x < 0 || x >= capacity) return false;
        int pos = sparse[x];
        return pos >= 0 && pos < size && dense[pos] == x;
    }

    void insert(int x) {
        if (x < 0 || x >= capacity || contains(x)) return;
        sparse[x] = size;
        if (size < (int)dense.size()) dense[size] = x;
        else dense.push_back(x);
        size++;
    }

    void remove(int x) {
        if (!contains(x)) return;
        int pos = sparse[x];
        int last_val = dense[size - 1];
        
        dense[pos] = last_val;
        sparse[last_val] = pos;
        
        size--;
    }

    int get_size() const { return size; }
    size_t memory_usage() const {
        return sparse.size() * sizeof(int) + dense.capacity() * sizeof(int) + sizeof(*this);
    }
};

const int MAX_VAL = 1'000'000;
const int OPS = 100'000;

int main() {
    std::cout << "--- Sparse Set Laboratory (" << MAX_VAL << " capacity) ---" << std::endl;

    SparseSet ss(MAX_VAL);
    lab::print_qor("Empty Set", ss.memory_usage());

    {
        lab::Benchmark b("Batch Insertion (100k)");
        for (int i = 0; i < OPS; ++i) {
            ss.insert(i * 7 % MAX_VAL);
        }
    }

    lab::print_qor("Full Set", ss.memory_usage(), ss.get_size());

    {
        lab::Benchmark b("Random Lookup (100k)");
        int found = 0;
        for (int i = 0; i < OPS; ++i) {
            if (ss.contains(i * 13 % MAX_VAL)) found++;
        }
        lab::escape(&found);
    }

    {
        lab::Benchmark b("Batch Removal (50k)");
        for (int i = 0; i < OPS / 2; ++i) {
            ss.remove(i * 7 % MAX_VAL);
        }
    }

    lab::print_qor("Final Set", ss.memory_usage(), ss.get_size());

    return 0;
}
