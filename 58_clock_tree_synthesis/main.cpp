/**
 * EXPERIMENT: Clock Tree Synthesis (H-Tree)
 * 
 * GOAL: Construct a balanced H-tree to distribute a clock signal 
 * with minimal skew to all registers.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

struct Point { float x, y; };

class HTreeSynthesizer {
    std::vector<Point> sinks;
    float total_wirelength = 0;

public:
    void add_sink(float x, float y) { sinks.push_back({x, y}); }

    void build_h_tree(float x, float y, float size, int depth) {
        if (depth == 0) return;

        // Draw horizontal segment
        total_wirelength += size;
        float x1 = x - size / 2;
        float x2 = x + size / 2;

        // Draw vertical segments at ends
        total_wirelength += size; 
        
        build_h_tree(x1, y - size / 2, size / 2, depth - 1);
        build_h_tree(x1, y + size / 2, size / 2, depth - 1);
        build_h_tree(x2, y - size / 2, size / 2, depth - 1);
        build_h_tree(x2, y + size / 2, size / 2, depth - 1);
    }

    float get_wirelength() { return total_wirelength; }
};

int main() {
    std::cout << "--- Clock Tree Synthesis (H-Tree) Laboratory ---" << std::endl;

    HTreeSynthesizer cts;
    float initial_size = 500.0f;
    int depth = 6; // 4^6 sinks

    {
        lab::Benchmark b("Recursive H-Tree Construction");
        cts.build_h_tree(500, 500, initial_size, depth);
    }

    std::cout << "[METRICS] Total H-Tree Wirelength: " << cts.get_wirelength() << std::endl;
    std::cout << "[METRICS] Number of Leaves (Sinks): " << std::pow(4, depth) << std::endl;

    lab::print_qor("CTS Result", 0, (size_t)cts.get_wirelength());

    return 0;
}
