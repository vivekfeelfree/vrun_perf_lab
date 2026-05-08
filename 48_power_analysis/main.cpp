/**
 * EXPERIMENT: Switching Activity & Power Analysis
 * 
 * GOAL: Estimate dynamic power consumption by tracking the 
 * switching activity of logic nodes during simulation.
 */

#include "../include/harness.hpp"
#include <vector>

class PowerAnalyzer {
    struct Gate {
        int f1, f2;
        bool last_val;
        long long switches;
    };
    std::vector<Gate> gates;
    std::vector<bool> pi_vals;

public:
    PowerAnalyzer(int pi) : pi_vals(pi, false) {}

    void add_gate(int f1, int f2) {
        gates.push_back({f1, f2, false, 0});
    }

    void simulate(int pi, int n_pi) {
        for (int i = 0; i < (int)gates.size(); ++i) {
            bool v1 = (gates[i].f1 < n_pi) ? pi_vals[gates[i].f1] : gates[gates[i].f1 - n_pi].last_val;
            bool v2 = (gates[i].f2 < n_pi) ? pi_vals[gates[i].f2] : gates[gates[i].f2 - n_pi].last_val;
            bool next_val = v1 && v2;
            if (next_val != gates[i].last_val) {
                gates[i].last_val = next_val;
                gates[i].switches++;
            }
        }
    }

    void set_pi(int idx, bool val) { pi_vals[idx] = val; }

    long long total_switches() {
        long long s = 0;
        for (const auto& g : gates) s += g.switches;
        return s;
    }
};

int main() {
    int PI = 50;
    int GATES = 1000;
    std::cout << "--- Power Analysis Laboratory ---" << std::endl;

    PowerAnalyzer analyzer(PI);
    for (int i = 0; i < GATES; ++i) {
        analyzer.add_gate(rand() % (PI + i), rand() % (PI + i));
    }

    {
        lab::Benchmark b("Power Estimation (5000 vectors)");
        for (int i = 0; i < 5000; ++i) {
            analyzer.set_pi(rand() % PI, rand() % 2);
            analyzer.simulate(PI, PI);
        }
    }

    long long switches = analyzer.total_switches();
    std::cout << "[METRICS] Total Switches: " << switches << std::endl;
    std::cout << "[METRICS] Avg Activity: " << (float)switches / (GATES * 5000) << std::endl;

    lab::print_qor("Power Metrics", switches);

    return 0;
}
