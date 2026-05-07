/**
 * EXPERIMENT: Intrusive Lists and Multi-Homing
 * 
 * GOAL: Demonstrate the flexibility and performance of intrusive
 * data structures compared to standard library wrappers.
 */

#include "../include/harness.hpp"
#include "../include/intrusive_list.hpp"
#include "../include/arena.hpp"
#include <list>
#include <vector>

/**
 * A "Kernel-style" object.
 * This struct represents a process that needs to exist in multiple
 * lists simultaneously (e.g., a list of all processes, and a list 
 * of processes waiting for CPU time).
 */
struct Process {
    int pid;
    lab::ListLink all_link;   // Hook for the "Master" list
    lab::ListLink ready_link; // Hook for the "Scheduler" list
    char name[32];
};

const int COUNT = 100'000;

/**
 * Baseline: std::list allocates a wrapper node for EVERY insertion.
 */
void bench_std_list() {
    lab::Benchmark b("std::list<int> insertion");
    std::list<int> my_list;
    for(int i=0; i<COUNT; ++i) {
        my_list.push_back(i);
    }
    lab::clobber();
}

/**
 * Optimized: IntrusiveList uses the memory already inside the object.
 * Combined with an Arena, this is the fastest possible way to manage lists.
 */
void bench_intrusive_list() {
    lab::Arena arena;
    lab::IntrusiveList list;
    
    lab::Benchmark b("IntrusiveList + Arena");
    for(int i=0; i<COUNT; ++i) {
        // 1. Allocate object memory
        Process* p = (Process*)arena.alloc(sizeof(Process));
        p->pid = i;
        // 2. Link it. ZERO extra allocations occur here.
        list.push_back(&p->all_link);
    }
    lab::clobber();
}

/**
 * Demonstration of Multi-Homing:
 * One object, two lists, zero copies.
 */
void experiment_multi_homing() {
    std::cout << "\n--- Multi-Homing Experiment ---" << std::endl;
    lab::Arena arena;
    lab::IntrusiveList all_procs;
    lab::IntrusiveList ready_procs;

    // Create a single process
    Process* p1 = (Process*)arena.alloc(sizeof(Process));
    p1->pid = 999;

    // Add the SAME object to two different lists
    all_procs.push_back(&p1->all_link);
    ready_procs.push_back(&p1->ready_link);

    std::cout << "Process " << p1->pid << " is now in both lists." << std::endl;
    std::cout << "  - All list size:   " << all_procs.size() << std::endl;
    std::cout << "  - Ready list size: " << ready_procs.size() << std::endl;

    // Use our magic container_of to go from link -> process
    lab::ListLink* link_ptr = all_procs.head.next;
    Process* recovered = lab::IntrusiveList::container_of<Process, &Process::all_link>(link_ptr);
    
    std::cout << "Recovered Process PID from link: " << recovered->pid << std::endl;
}

int main() {
    std::cout << "--- Intrusive List Benchmark (" << COUNT << " elements) ---" << std::endl;
    
    lab::print_qor("std::list<int>", COUNT * (sizeof(int) + 2 * sizeof(void*)));
    bench_std_list();

    lab::print_qor("IntrusiveList + Arena", COUNT * sizeof(Process));
    bench_intrusive_list();
    
    experiment_multi_homing();

    return 0;
}
