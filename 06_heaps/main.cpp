/**
 * EXPERIMENT: Cache-Friendly Heaps (Binary vs. 4-ary)
 * 
 * GOAL: Observe how branching factor affects performance by balancing
 * comparison count against cache locality.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>
#include <queue>

/**
 * Standard Binary Heap (2-way)
 */
template <typename T>
class BinaryHeap {
    std::vector<T> data;

    void sift_up(size_t i) {
        while (i > 0) {
            size_t p = (i - 1) / 2;
            if (data[i] < data[p]) {
                std::swap(data[i], data[p]);
                i = p;
            } else break;
        }
    }

    void sift_down(size_t i) {
        while (true) {
            size_t l = 2 * i + 1;
            size_t r = 2 * i + 2;
            size_t smallest = i;

            if (l < data.size() && data[l] < data[smallest]) smallest = l;
            if (r < data.size() && data[r] < data[smallest]) smallest = r;

            if (smallest != i) {
                std::swap(data[i], data[smallest]);
                i = smallest;
            } else break;
        }
    }

public:
    void push(T val) {
        data.push_back(val);
        sift_up(data.size() - 1);
    }

    T pop() {
        T top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
        return top;
    }

    bool empty() const { return data.empty(); }
};

/**
 * 4-ary Heap (Each node has 4 children)
 */
template <typename T>
class QuadHeap {
    std::vector<T> data;

    void sift_up(size_t i) {
        while (i > 0) {
            size_t p = (i - 1) / 4;
            if (data[i] < data[p]) {
                std::swap(data[i], data[p]);
                i = p;
            } else break;
        }
    }

    void sift_down(size_t i) {
        while (true) {
            size_t base_child = 4 * i + 1;
            if (base_child >= data.size()) break;

            size_t smallest = i;
            // Check all 4 children
            for (size_t k = 0; k < 4; ++k) {
                size_t child = base_child + k;
                if (child < data.size() && data[child] < data[smallest]) {
                    smallest = child;
                }
            }

            if (smallest != i) {
                std::swap(data[i], data[smallest]);
                i = smallest;
            } else break;
        }
    }

public:
    void push(T val) {
        data.push_back(val);
        sift_up(data.size() - 1);
    }

    T pop() {
        T top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
        return top;
    }

    bool empty() const { return data.empty(); }
};

const int COUNT = 1'000'000;

int main() {
    std::cout << "--- Heap Laboratory (" << COUNT << " elements) ---" << std::endl;

    // Generate random data
    std::vector<int> raw_data(COUNT);
    for(int i=0; i<COUNT; ++i) raw_data[i] = rand();

    {
        lab::print_qor("std::priority_queue", COUNT * sizeof(int));
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        lab::Benchmark bench("std::priority_queue");
        for(int x : raw_data) pq.push(x);
        while(!pq.empty()) {
            int val = pq.top();
            pq.pop();
            lab::escape(&val);
        }
    }

    {
        lab::print_qor("BinaryHeap", COUNT * sizeof(int));
        BinaryHeap<int> bh;
        lab::Benchmark bench("Hand-rolled BinaryHeap");
        for(int x : raw_data) bh.push(x);
        while(!bh.empty()) {
            int val = bh.pop();
            lab::escape(&val);
        }
    }

    {
        lab::print_qor("QuadHeap", COUNT * sizeof(int));
        QuadHeap<int> qh;
        lab::Benchmark bench("Hand-rolled QuadHeap (4-ary)");
        for(int x : raw_data) qh.push(x);
        while(!qh.empty()) {
            int val = qh.pop();
            lab::escape(&val);
        }
    }

    return 0;
}
