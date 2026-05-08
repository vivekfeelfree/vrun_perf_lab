/**
 * EXPERIMENT: Engineering Change Order (ECO) Logic Patch
 * 
 * GOAL: Apply a logic change to a fixed layout by locating and 
 * utilizing nearby "spare cells" to minimize routing disruption.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

struct Cell {
    int id;
    int x, y;
    bool is_spare;
    bool in_use;
};

class ECOEngine {
    std::vector<Cell> placement;

public:
    void add_cell(int id, int x, int y, bool spare) {
        placement.push_back({id, x, y, spare, !spare});
    }

    int apply_patch(int target_x, int target_y, int cells_needed) {
        int utilized = 0;
        
        // Find nearest available spare cells
        std::vector<std::pair<float, int>> spares;
        for (int i = 0; i < (int)placement.size(); ++i) {
            if (placement[i].is_spare && !placement[i].in_use) {
                float dist = std::sqrt(std::pow(placement[i].x - target_x, 2) + std::pow(placement[i].y - target_y, 2));
                spares.push_back({dist, i});
            }
        }
        std::sort(spares.begin(), spares.end());

        float total_dist = 0;
        for (int i = 0; i < std::min((int)spares.size(), cells_needed); ++i) {
            int idx = spares[i].second;
            placement[idx].in_use = true;
            total_dist += spares[i].first;
            utilized++;
        }
        
        if (utilized > 0) {
            std::cout << "[METRICS] Average Patch Distance: " << total_dist / utilized << " units" << std::endl;
        }
        return utilized;
    }

    size_t memory_usage() const { return placement.size() * sizeof(Cell); }
};

int main() {
    int TOTAL_CELLS = 5000;
    int SPARE_COUNT = 100;
    std::cout << "--- ECO Logic Patch Laboratory ---" << std::endl;

    ECOEngine eco;
    for (int i = 0; i < TOTAL_CELLS; ++i) {
        eco.add_cell(i, rand() % 1000, rand() % 1000, i < SPARE_COUNT);
    }

    lab::print_qor("Placement Map", eco.memory_usage());

    int patched = 0;
    {
        lab::Benchmark b("ECO Patch Application");
        patched = eco.apply_patch(500, 500, 5); // Need 5 cells for a patch at center
    }

    std::cout << "[METRICS] Spare Cells Utilized: " << patched << std::endl;
    lab::print_qor("Final ECO Result", 0, patched);

    return 0;
}
