/**
 * EXPERIMENT: Parasitic Extraction (Elmore Delay)
 * 
 * GOAL: Calculate the Elmore delay for an RC tree network representing 
 * a routed net.
 */

#include "../include/harness.hpp"
#include <vector>

struct RCNode {
    int parent;
    float R; // Resistance of the branch to parent
    float C; // Parasitic capacitance at this node
    float total_cap_subtree = 0.0f;
};

class DelayExtractor {
    std::vector<RCNode> nodes;

public:
    void add_node(int parent, float r, float c) {
        nodes.push_back({parent, r, c, 0.0f});
    }

    void compute_subtree_capacitance() {
        for (int i = nodes.size() - 1; i >= 0; --i) {
            nodes[i].total_cap_subtree += nodes[i].C;
            if (nodes[i].parent != -1) {
                nodes[nodes[i].parent].total_cap_subtree += nodes[i].total_cap_subtree;
            }
        }
    }

    float compute_elmore_delay(int target) {
        float delay = 0;
        int curr = target;
        while (curr != -1) {
            delay += nodes[curr].R * nodes[curr].total_cap_subtree;
            curr = nodes[curr].parent;
        }
        return delay;
    }

    size_t memory_usage() const { return nodes.size() * sizeof(RCNode); }
};

int main() {
    std::cout << "--- Parasitic Extraction (Elmore Delay) Laboratory ---" << std::endl;

    DelayExtractor de;
    de.add_node(-1, 0, 1.0); // Source (Node 0)
    for (int i = 1; i < 1000; ++i) {
        de.add_node(i - 1, 0.5f, 2.0f); // Long RC chain
    }

    lab::print_qor("RC Network", de.memory_usage());

    float delay = 0;
    {
        lab::Benchmark b("Elmore Delay Computation");
        de.compute_subtree_capacitance();
        delay = de.compute_elmore_delay(999);
    }

    std::cout << "[METRICS] Elmore Delay to Sink: " << delay << " ps" << std::endl;
    lab::print_qor("Final Delay", 0, (size_t)delay);

    return 0;
}
