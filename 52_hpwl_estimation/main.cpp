/**
 * EXPERIMENT: Half-Perimeter Wirelength (HPWL) Estimation
 * 
 * GOAL: Efficiently estimate total wirelength for a set of nets 
 * during placement using the HPWL metric.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Point { int x, y; };
struct Net { std::vector<int> pins; }; // Indices of pins

class HPWLManager {
    std::vector<Point> pin_locs;
    std::vector<Net> nets;

public:
    HPWLManager(int n_pins) : pin_locs(n_pins) {}

    void set_pin(int id, int x, int y) { pin_locs[id] = {x, y}; }
    void add_net(const std::vector<int>& p) { nets.push_back({p}); }

    long long compute_total_hpwl() {
        long long total = 0;
        for (const auto& net : nets) {
            int min_x = 2e9, max_x = -2e9, min_y = 2e9, max_y = -2e9;
            for (int pin_id : net.pins) {
                min_x = std::min(min_x, pin_locs[pin_id].x);
                max_x = std::max(max_x, pin_locs[pin_id].x);
                min_y = std::min(min_y, pin_locs[pin_id].y);
                max_y = std::max(max_y, pin_locs[pin_id].y);
            }
            total += (max_x - min_x) + (max_y - min_y);
        }
        return total;
    }

    size_t memory_usage() const {
        size_t total = pin_locs.size() * sizeof(Point);
        for (const auto& n : nets) total += n.pins.size() * sizeof(int);
        return total;
    }
};

int main() {
    int PINS = 10000;
    int NETS = 5000;
    std::cout << "--- HPWL Estimation Laboratory ---" << std::endl;

    HPWLManager hpwl(PINS);
    for (int i = 0; i < PINS; ++i) hpwl.set_pin(i, rand() % 1000, rand() % 1000);
    for (int i = 0; i < NETS; ++i) {
        std::vector<int> net;
        for (int j = 0; j < 3; ++j) net.push_back(rand() % PINS);
        hpwl.add_net(net);
    }

    lab::print_qor("Netlist Footprint", hpwl.memory_usage());

    long long total_hpwl = 0;
    {
        lab::Benchmark b("Total HPWL Computation");
        total_hpwl = hpwl.compute_total_hpwl();
    }

    std::cout << "[METRICS] Estimated Total HPWL: " << total_hpwl << std::endl;
    lab::print_qor("Final HPWL", 0, (size_t)total_hpwl);

    return 0;
}
