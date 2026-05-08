/**
 * EXPERIMENT: Synthesis Report Generation
 * 
 * GOAL: Aggregate metrics from various synthesis stages into a 
 * comprehensive summary report.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>
#include <map>

struct SynthesisReport {
    int gate_count;
    float total_area;
    float max_delay;
    int flip_flops;
    std::map<std::string, int> gate_distribution;
};

void print_report(const SynthesisReport& report) {
    std::cout << "\n================ SYNTHESIS REPORT ================" << std::endl;
    std::cout << " Gate Count: " << report.gate_count << std::endl;
    std::cout << " Total Area: " << report.total_area << " um^2" << std::endl;
    std::cout << " Max Delay:  " << report.max_delay << " ns" << std::endl;
    std::cout << " Flip-Flops: " << report.flip_flops << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (const auto& entry : report.gate_distribution) {
        std::cout << " " << entry.first << ": " << entry.second << std::endl;
    }
    std::cout << "================================================\n" << std::endl;
}

int main() {
    std::cout << "--- Synthesis Report Laboratory ---" << std::endl;

    SynthesisReport report;
    {
        lab::Benchmark b("Metric Aggregation");
        report.gate_count = 15000;
        report.total_area = 45200.5f;
        report.max_delay = 1.45f;
        report.flip_flops = 1200;
        report.gate_distribution["AND2"] = 5000;
        report.gate_distribution["OR2"] = 3000;
        report.gate_distribution["INV"] = 4000;
        report.gate_distribution["DFF"] = 1200;
        report.gate_distribution["XOR2"] = 1800;
    }

    print_report(report);
    lab::print_qor("Report Generation", sizeof(report));

    return 0;
}
