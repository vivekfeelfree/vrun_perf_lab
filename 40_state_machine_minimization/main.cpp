/**
 * EXPERIMENT: State Machine Minimization
 * 
 * GOAL: Use Moore's algorithm to identify equivalent states in a 
 * Finite State Machine (FSM) and reduce state count.
 */

#include "../include/harness.hpp"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

struct State {
    int id;
    int next[2]; // Next state for input 0 and 1
    int output;
};

class FSMMinimizer {
    std::vector<State> states;

public:
    void add_state(int next0, int next1, int out) {
        states.push_back({(int)states.size(), next0, next1, out});
    }

    int minimize() {
        int n = states.size();
        if (n == 0) return 0;

        // Initial partition by output
        std::vector<int> partition(n);
        int p_count = 0;
        std::map<int, int> out_to_p;
        for (int i = 0; i < n; ++i) {
            if (out_to_p.find(states[i].output) == out_to_p.end()) {
                out_to_p[states[i].output] = p_count++;
            }
            partition[i] = out_to_p[states[i].output];
        }

        bool changed = true;
        while (changed) {
            changed = false;
            std::vector<int> next_partition(n);
            std::map<std::vector<int>, int> sig_to_p;
            int next_p_count = 0;

            for (int i = 0; i < n; ++i) {
                std::vector<int> sig = {partition[i], partition[states[i].next[0]], partition[states[i].next[1]]};
                if (sig_to_p.find(sig) == sig_to_p.end()) {
                    sig_to_p[sig] = next_p_count++;
                }
                next_partition[i] = sig_to_p[sig];
            }

            if (next_p_count != p_count) {
                changed = true;
                partition = next_partition;
                p_count = next_p_count;
            }
        }
        return p_count;
    }

    size_t memory_usage() const {
        return states.size() * sizeof(State) + sizeof(*this);
    }
};

int main() {
    std::cout << "--- FSM Minimization Laboratory ---" << std::endl;

    FSMMinimizer fsm;
    // Simple FSM with redundant states
    fsm.add_state(1, 2, 0); // S0
    fsm.add_state(3, 4, 0); // S1 (Same as S0)
    fsm.add_state(0, 0, 1); // S2
    fsm.add_state(1, 2, 0); // S3 (Same as S0)
    fsm.add_state(0, 0, 1); // S4 (Same as S2)

    lab::print_qor("Initial FSM", fsm.memory_usage(), 5);

    int minimized_states = 0;
    {
        lab::Benchmark b("Moore's State Minimization");
        minimized_states = fsm.minimize();
    }

    std::cout << "[METRICS] Minimized States: " << minimized_states << std::endl;
    lab::print_qor("Final FSM", fsm.memory_usage(), minimized_states);

    return 0;
}
