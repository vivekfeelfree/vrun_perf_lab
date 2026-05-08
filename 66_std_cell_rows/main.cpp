/**
 * EXPERIMENT: Standard Cell Row Generation
 * 
 * GOAL: Create valid standard cell rows with power and ground 
 * rails (VDD/VSS) for cell placement.
 */

#include "../include/harness.hpp"
#include <vector>

struct Row {
    int y;
    int height;
};

class RowGenerator {
    std::vector<Row> rows;

public:
    void generate(int chip_height, int row_height) {
        for (int y = 0; y < chip_height; y += row_height) {
            rows.push_back({y, row_height});
        }
    }

    size_t count() const { return rows.size(); }
    size_t memory_usage() const { return rows.size() * sizeof(Row); }
};

int main() {
    int CHIP_H = 10000;
    int ROW_H = 10;
    std::cout << "--- Standard Cell Row Generation Laboratory ---" << std::endl;

    RowGenerator rg;
    {
        lab::Benchmark b("Row Generation");
        rg.generate(CHIP_H, ROW_H);
    }

    std::cout << "[METRICS] Total Rows Generated: " << rg.count() << std::endl;
    lab::print_qor("Layout Rows", rg.memory_usage(), rg.count());

    return 0;
}
