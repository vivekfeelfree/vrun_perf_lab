/**
 * EXPERIMENT: Min-Cut Partitioning Placement
 * 
 * GOAL: Use recursive min-cut partitioning (KL-style) to perform 
 * global placement of a netlist.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Node {
    int id;
    int x, y;
};

class PartitionPlacer {
    std::vector<Node> nodes;
    int width, height;

public:
    PartitionPlacer(int n, int w, int h) : width(w), height(h) {
        for (int i = 0; i < n; ++i) nodes.push_back({i, 0, 0});
    }

    void recursive_place(int l, int r, int x, int y, int w, int h, bool vertical) {
        if (r - l <= 1) {
            nodes[l].x = x + w / 2;
            nodes[l].y = y + h / 2;
            return;
        }

        int mid = (l + r) / 2;
        if (vertical) {
            recursive_place(l, mid, x, y, w / 2, h, !vertical);
            recursive_place(mid, r, x + w / 2, y, w / 2, h, !vertical);
        } else {
            recursive_place(l, mid, x, y, w, h / 2, !vertical);
            recursive_place(mid, r, x, y + h / 2, w, h / 2, !vertical);
        }
    }

    void run() { recursive_place(0, nodes.size(), 0, 0, width, height, true); }

    size_t memory_usage() const { return nodes.size() * sizeof(Node); }
};

int main() {
    int N = 10000;
    std::cout << "--- Min-Cut Partitioning Placement Laboratory ---" << std::endl;

    PartitionPlacer placer(N, 1000, 1000);
    lab::print_qor("Placement Engine", placer.memory_usage());

    {
        lab::Benchmark b("Recursive Global Placement");
        placer.run();
    }

    lab::print_qor("Final Placement", placer.memory_usage());

    return 0;
}
