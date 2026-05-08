/**
 * EXPERIMENT: Event-Driven Logic Simulation
 * 
 * GOAL: Measure the efficiency of event-driven simulation where only 
 * affected gates are re-evaluated.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>

struct Gate {
    int id;
    int f1, f2;
    bool out_val;
    std::vector<int> fanouts;
};

class EventSimulator {
    std::vector<Gate> gates;
    std::vector<bool> pi_vals;

public:
    EventSimulator(int n_pi) : pi_vals(n_pi, false) {}

    void add_gate(int id, int f1, int f2) {
        gates.push_back({id, f1, f2, false, {}});
    }

    void build_fanouts(int n_pi) {
        for (size_t i = 0; i < gates.size(); ++i) {
            if (gates[i].f1 >= n_pi) gates[gates[i].f1 - n_pi].fanouts.push_back(i + n_pi);
            if (gates[i].f2 >= n_pi) gates[gates[i].f2 - n_pi].fanouts.push_back(i + n_pi);
        }
    }

    int simulate(int pi_idx, bool new_val, int n_pi) {
        if (pi_vals[pi_idx] == new_val) return 0;
        pi_vals[pi_idx] = new_val;

        std::queue<int> event_queue;
        // In a real simulator, we'd have fanouts for PIs too.
        // For simplicity, find gates connected to this PI.
        for (size_t i = 0; i < gates.size(); ++i) {
            if (gates[i].f1 == pi_idx || gates[i].f2 == pi_idx) {
                event_queue.push(i + n_pi);
            }
        }

        int evaluations = 0;
        while (!event_queue.empty()) {
            int g_idx = event_queue.front() - n_pi;
            event_queue.pop();
            evaluations++;

            bool v1 = (gates[g_idx].f1 < n_pi) ? pi_vals[gates[g_idx].f1] : gates[gates[g_idx].f1 - n_pi].out_val;
            bool v2 = (gates[g_idx].f2 < n_pi) ? pi_vals[gates[g_idx].f2] : gates[gates[g_idx].f2 - n_pi].out_val;
            
            bool new_out = v1 && v2;
            if (new_out != gates[g_idx].out_val) {
                gates[g_idx].out_val = new_out;
                for (int fanout : gates[g_idx].fanouts) {
                    event_queue.push(fanout);
                }
            }
        }
        return evaluations;
    }

    size_t memory_usage() const {
        size_t total = gates.size() * sizeof(Gate);
        for (const auto& g : gates) total += g.fanouts.size() * sizeof(int);
        return total;
    }
};

int main() {
    int PI = 100;
    int GATES = 5000;
    std::cout << "--- Event-Driven Simulation Laboratory ---" << std::endl;

    EventSimulator sim(PI);
    for (int i = 0; i < GATES; ++i) {
        sim.add_gate(PI + i, rand() % (PI + i), rand() % (PI + i));
    }
    sim.build_fanouts(PI);

    lab::print_qor("Simulator Memory", sim.memory_usage());

    int total_evals = 0;
    {
        lab::Benchmark b("Event-Driven Simulation (1000 toggles)");
        for (int i = 0; i < 1000; ++i) {
            total_evals += sim.simulate(rand() % PI, rand() % 2, PI);
        }
    }

    std::cout << "[METRICS] Average Evaluations per Toggle: " << total_evals / 1000.0f << std::endl;

    return 0;
}
