/**
 * EXPERIMENT: Static Timing Analysis (Setup/Hold Sign-off)
 * 
 * GOAL: Verify setup and hold timing constraints for a path between 
 * two registers.
 */

#include "../include/harness.hpp"
#include <iostream>

struct TimingPath {
    float t_clk_q;    // Register clock-to-q delay
    float t_logic;    // Combinational logic delay
    float t_setup;    // Destination register setup time
    float t_hold;     // Destination register hold time
    float t_clk_skew; // Clock skew between launch and capture
    float period;     // Clock period
};

class STASignoff {
public:
    bool check_setup(const TimingPath& p, float& slack) {
        // T_launch + T_logic + T_setup <= T_period + T_capture + T_skew
        // (Simplified: T_clk_q + T_logic + T_setup <= T_period + T_skew)
        float arrival = p.t_clk_q + p.t_logic;
        float required = p.period + p.t_clk_skew - p.t_setup;
        slack = required - arrival;
        return slack >= 0;
    }

    bool check_hold(const TimingPath& p, float& slack) {
        // T_launch + T_logic >= T_hold + T_skew
        float arrival = p.t_clk_q + p.t_logic;
        float required = p.t_hold + p.t_clk_skew;
        slack = arrival - required;
        return slack >= 0;
    }
};

int main() {
    std::cout << "--- STA Sign-off Laboratory ---" << std::endl;

    TimingPath path = {0.1f, 0.5f, 0.05f, 0.05f, 0.02f, 1.0f}; // 1GHz clock
    STASignoff sta;
    float setup_slack, hold_slack;

    {
        lab::Benchmark b("Setup Time Check");
        sta.check_setup(path, setup_slack);
    }
    std::cout << "[METRICS] Setup Slack: " << setup_slack << " ns (" << (setup_slack >= 0 ? "MET" : "VIOLATED") << ")" << std::endl;

    {
        lab::Benchmark b("Hold Time Check");
        sta.check_hold(path, hold_slack);
    }
    std::cout << "[METRICS] Hold Slack:  " << hold_slack << " ns (" << (hold_slack >= 0 ? "MET" : "VIOLATED") << ")" << std::endl;

    lab::print_qor("Timing DB", sizeof(path));

    return 0;
}
