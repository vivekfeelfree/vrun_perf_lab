/**
 * EXPERIMENT: Disjoint Set Union (DSU)
 * 
 * GOAL: Measure the efficiency of DSU with Path Compression and 
 * Union by Rank, which achieves nearly O(1) amortized time.
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_i] = root_j;
                rank[root_j]++;
            }
        }
    }

    size_t memory_usage() const {
        return parent.size() * sizeof(int) + rank.size() * sizeof(int) + sizeof(*this);
    }
};

const int N = 1'000'000;
const int OPS = 2'000'000;

int main() {
    std::cout << "--- DSU Laboratory (" << N << " nodes) ---" << std::endl;

    DSU dsu(N);
    lab::print_qor("Initial DSU", dsu.memory_usage());

    {
        lab::Benchmark b("Batch Unions (2M)");
        for (int i = 0; i < OPS; ++i) {
            dsu.unite(rand() % N, rand() % N);
        }
    }

    {
        lab::Benchmark b("Batch Finds (2M)");
        int checksum = 0;
        for (int i = 0; i < OPS; ++i) {
            checksum ^= dsu.find(rand() % N);
        }
        lab::escape(&checksum);
    }

    lab::print_qor("Final DSU", dsu.memory_usage());

    return 0;
}
