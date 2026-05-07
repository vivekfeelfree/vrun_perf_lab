/**
 * EXPERIMENT: Lock-Free Stack vs. Mutex Stack
 * 
 * GOAL: Measure the impact of thread contention on standard 
 * mutexes vs. atomic compare-and-swap operations.
 */

#include "../include/harness.hpp"
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <stack>

/**
 * Baseline: Stack protected by a std::mutex.
 */
template <typename T>
class MutexStack {
    std::stack<T> s;
    std::mutex m;
public:
    void push(T val) {
        std::lock_guard<std::mutex> lock(m);
        s.push(val);
    }

    bool pop(T& res) {
        std::lock_guard<std::mutex> lock(m);
        if (s.empty()) return false;
        res = s.top();
        s.pop();
        return true;
    }
};

/**
 * Optimized: Lock-Free Stack using CAS.
 */
template <typename T>
class LockFreeStack {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::atomic<Node*> head{nullptr};

public:
    void push(T val) {
        Node* new_node = new Node(val);
        // "compare_exchange_weak" is the CAS operation
        new_node->next = head.load(std::memory_order_relaxed);
        while (!head.compare_exchange_weak(new_node->next, new_node,
                                           std::memory_order_release,
                                           std::memory_order_relaxed)) {
            // If it failed, new_node->next is automatically updated 
            // to the current head, so we just try again in the loop.
        }
    }

    bool pop(T& res) {
        Node* old_head = head.load(std::memory_order_acquire);
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next,
                                                      std::memory_order_release,
                                                      std::memory_order_relaxed)) {
            // Try again
        }

        if (old_head) {
            res = old_head->data;
            // Note: In a real system, we'd need a "Hazard Pointer" or 
            // "Epoch-based Reclamation" to safely delete this node.
            // For the lab, we'll leak it or use an Arena.
            return true;
        }
        return false;
    }
};

const int OPS_PER_THREAD = 100'000;
const int NUM_THREADS = 4;

template <typename StackType>
void run_bench(const char* name) {
    StackType s;
    std::vector<std::thread> threads;

    lab::Benchmark b(name);
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&s]() {
            for (int i = 0; i < OPS_PER_THREAD; ++i) {
                s.push(i);
                int val;
                s.pop(val);
            }
        });
    }

    for (auto& t : threads) t.join();
}

int main() {
    std::cout << "--- Lock-Free Laboratory (" << NUM_THREADS << " threads) ---" << std::endl;

    lab::print_qor("Mutex-based Stack", sizeof(MutexStack<int>));
    run_bench<MutexStack<int>>("Mutex-based Stack");
    
    lab::print_qor("Lock-Free Stack", sizeof(LockFreeStack<int>));
    run_bench<LockFreeStack<int>>("Lock-Free Stack");

    return 0;
}
