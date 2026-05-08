/**
 * EXPERIMENT: Design Rule Checking (DRC)
 * 
 * GOAL: Use spatial data structures (simplified) to efficiently 
 * check for spacing violations between metal rectangles.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Rect {
    int id;
    int x1, y1, x2, y2;
    int layer;
};

class DRCEngine {
    std::vector<Rect> objects;
    int min_spacing = 2;

public:
    void add_rect(int id, int x1, int y1, int x2, int y2, int l) {
        objects.push_back({id, x1, y1, x2, y2, l});
    }

    int check_violations() {
        int violations = 0;
        int n = objects.size();
        
        // Naive O(N^2) for small N, but we'll benchmark it
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (objects[i].layer != objects[j].layer) continue;

                // Check distance between rectangles
                int dx = std::max(0, std::max(objects[i].x1 - objects[j].x2, objects[j].x1 - objects[i].x2));
                int dy = std::max(0, std::max(objects[i].y1 - objects[j].y2, objects[j].y1 - objects[i].y2));
                
                if (dx < min_spacing && dy < min_spacing) {
                    // This is a simplified check for overlaps or close proximity
                    violations++;
                }
            }
        }
        return violations;
    }

    size_t memory_usage() const { return objects.size() * sizeof(Rect); }
};

int main() {
    int RECTS = 1000;
    std::cout << "--- Design Rule Checking Laboratory (" << RECTS << " objects) ---" << std::endl;

    DRCEngine drc;
    for (int i = 0; i < RECTS; ++i) {
        int x = rand() % 500;
        int y = rand() % 500;
        drc.add_rect(i, x, y, x + 5, y + 5, 1);
    }

    lab::print_qor("Layout DB", drc.memory_usage());

    int violations = 0;
    {
        lab::Benchmark b("DRC Spacing Checks");
        violations = drc.check_violations();
    }

    std::cout << "[METRICS] DRC Violations: " << violations << std::endl;
    lab::print_qor("Final Violations", 0, violations);

    return 0;
}
