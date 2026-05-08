/**
 * EXPERIMENT: Layout vs. Schematic (LVS) Check
 * 
 * GOAL: Compare two circuit graphs (Schematic vs. Extracted Layout) 
 * using vertex signatures to identify topological mismatches.
 */

#include "../include/harness.hpp"
#include <vector>
#include <map>
#include <algorithm>

struct Netlist {
    struct Node {
        std::string type;
        std::vector<int> adj;
    };
    std::vector<Node> nodes;

    void add_node(std::string type) { nodes.push_back({type, {}}); }
    void add_edge(int u, int v) {
        nodes[u].adj.push_back(v);
        nodes[v].adj.push_back(u);
    }

    std::vector<long long> compute_signatures() {
        std::vector<long long> sigs(nodes.size());
        for (int i = 0; i < (int)nodes.size(); ++i) {
            long long s = std::hash<std::string>{}(nodes[i].type);
            s ^= (nodes[i].adj.size() << 1);
            sigs[i] = s;
        }
        // Simple 1-hop refinement
        std::vector<long long> refined = sigs;
        for (int i = 0; i < (int)nodes.size(); ++i) {
            for (int neighbor : nodes[i].adj) refined[i] += sigs[neighbor];
        }
        std::sort(refined.begin(), refined.end());
        return refined;
    }
};

int main() {
    std::cout << "--- LVS Connectivity Check Laboratory ---" << std::endl;

    Netlist schematic, layout;
    // Circuit: INV -> AND
    schematic.add_node("INV"); schematic.add_node("AND"); schematic.add_edge(0, 1);
    layout.add_node("INV");    layout.add_node("AND");    layout.add_edge(0, 1);

    bool match = false;
    {
        lab::Benchmark b("LVS Signature Matching (Identical)");
        auto s1 = schematic.compute_signatures();
        auto s2 = layout.compute_signatures();
        match = (s1 == s2);
    }
    std::cout << "[METRICS] LVS Match: " << (match ? "PASSED" : "FAILED") << std::endl;

    // Introduce a mismatch in layout
    layout.add_node("CAP"); layout.add_edge(1, 2);
    {
        lab::Benchmark b("LVS Signature Matching (Mismatched)");
        auto s1 = schematic.compute_signatures();
        auto s2 = layout.compute_signatures();
        match = (s1 == s2);
    }
    std::cout << "[METRICS] LVS Match (Modified): " << (match ? "PASSED" : "FAILED") << std::endl;

    lab::print_qor("LVS Database", schematic.nodes.size() * sizeof(Netlist::Node));

    return 0;
}
