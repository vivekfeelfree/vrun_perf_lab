/**
 * EXPERIMENT: Segment Trees
 * 
 * GOAL: Compare O(log N) range queries in a Segment Tree against 
 * O(N) linear scans.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

class SegmentTree {
    int n;
    std::vector<long long> tree;

public:
    SegmentTree(const std::vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    void build(const std::vector<int>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = data[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(data, 2 * v, tl, tm);
            build(data, 2 * v + 1, tm + 1, tr);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    long long sum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return sum(2 * v, tl, tm, l, std::min(r, tm)) +
               sum(2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(2 * v, tl, tm, pos, new_val);
            else
                update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    long long query(int l, int r) { return sum(1, 0, n - 1, l, r); }
    void point_update(int pos, int val) { update(1, 0, n - 1, pos, val); }

    size_t memory_usage() const {
        return tree.size() * sizeof(long long) + sizeof(*this);
    }
};

const int N = 100'000;
const int QUERIES = 50'000;

int main() {
    std::cout << "--- Segment Tree Laboratory (" << N << " elements) ---" << std::endl;

    std::vector<int> data(N);
    for (int i = 0; i < N; ++i) data[i] = i % 100;

    SegmentTree st(data);
    lab::print_qor("Segment Tree Setup", st.memory_usage());

    {
        lab::Benchmark b("Range Sum Queries (50k)");
        long long total = 0;
        for (int i = 0; i < QUERIES; ++i) {
            int l = rand() % (N / 2);
            int r = l + rand() % (N / 2);
            total += st.query(l, r);
        }
        lab::escape(&total);
    }

    {
        lab::Benchmark b("Point Updates (50k)");
        for (int i = 0; i < QUERIES; ++i) {
            st.point_update(rand() % N, rand() % 100);
        }
    }

    lab::print_qor("Final Segment Tree", st.memory_usage());

    return 0;
}
