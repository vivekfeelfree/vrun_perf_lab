/**
 * EXPERIMENT: Idiomatic C++ Iterators for Intrusive Structures
 * 
 * GOAL: Demonstrate that high-level C++ abstractions (iterators, range-loops)
 * have zero performance overhead compared to raw pointer arithmetic.
 */

#include "../include/harness.hpp"
#include "../include/intrusive_list.hpp"
#include "../include/arena.hpp"
#include <algorithm>

struct DataNode {
    int value;
    lab::ListLink link;
};

const int COUNT = 10'000'000;

int main() {
    std::cout << "--- Idiomatic C++ Intrusive List Laboratory ---" << std::endl;

    lab::Arena arena;
    lab::IntrusiveList list;

    // Population
    for(int i = 0; i < COUNT; ++i) {
        auto* n = (DataNode*)arena.alloc(sizeof(DataNode));
        n->value = i;
        list.push_back(&n->link);
    }

    // 1. Raw Manual Loop (C-style)
    {
        long long sum = 0;
        lab::Benchmark b("Manual Pointer Loop (C-style)");
        lab::ListLink* sentinel = &list.head;
        for(lab::ListLink* curr = list.head.next; curr != sentinel; curr = curr->next) {
            DataNode* obj = lab::IntrusiveList::container_of<DataNode, &DataNode::link>(curr);
            sum += obj->value;
        }
        lab::escape(&sum);
    }

    // 2. Idiomatic Iterator Loop
    {
        long long sum = 0;
        lab::Benchmark b("Idiomatic Iterator Loop");
        auto start = list.begin_at<DataNode, &DataNode::link>();
        auto end = list.end_at<DataNode, &DataNode::link>();
        for(auto it = start; it != end; ++it) {
            sum += it->value;
        }
        lab::escape(&sum);
    }

    return 0;
}
