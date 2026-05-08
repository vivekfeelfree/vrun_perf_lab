/**
 * EXPERIMENT: Signal Integrity (Crosstalk Estimation)
 * 
 * GOAL: Estimate coupling capacitance and crosstalk voltage 
 * between parallel wires on the same layer.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

struct Wire {
    int id;
    int y; // Horizontal wires at different Y offsets
    int l, r; // Left and right endpoints
};

class SignalIntegrityAnalyzer {
    std::vector<Wire> wires;
    float coupling_k = 0.5f; // Coupling constant

public:
    void add_wire(int id, int y, int l, int r) {
        wires.push_back({id, y, l, r});
    }

    float estimate_max_crosstalk() {
        float max_xtalk = 0;
        int n = wires.size();

        for (int i = 0; i < n; ++i) {
            float total_xtalk_i = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;

                // Overlap length
                int overlap_l = std::max(wires[i].l, wires[j].l);
                int overlap_r = std::min(wires[i].r, wires[j].r);
                int overlap = std::max(0, overlap_r - overlap_l);

                if (overlap > 0) {
                    int dist = std::abs(wires[i].y - wires[j].y);
                    if (dist < 5) { // Only consider nearby wires
                        total_xtalk_i += (float)overlap / (dist * dist + 1.0f) * coupling_k;
                    }
                }
            }
            if (total_xtalk_i > max_xtalk) max_xtalk = total_xtalk_i;
        }
        return max_xtalk;
    }

    size_t memory_usage() const { return wires.size() * sizeof(Wire); }
};

int main() {
    int WIRES = 500;
    std::cout << "--- Signal Integrity Laboratory ---" << std::endl;

    SignalIntegrityAnalyzer si;
    for (int i = 0; i < WIRES; ++i) {
        int y = rand() % 100;
        int l = rand() % 500;
        si.add_wire(i, y, l, l + rand() % 100 + 10);
    }

    lab::print_qor("Wire Database", si.memory_usage());

    float xtalk = 0;
    {
        lab::Benchmark b("Crosstalk Estimation");
        xtalk = si.estimate_max_crosstalk();
    }

    std::cout << "[METRICS] Maximum Estimated Crosstalk: " << xtalk << " units" << std::endl;
    lab::print_qor("Final Analysis", 0, (size_t)(xtalk * 100));

    return 0;
}
