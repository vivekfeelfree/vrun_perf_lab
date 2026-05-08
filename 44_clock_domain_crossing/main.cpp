/**
 * EXPERIMENT: Clock Domain Crossing (CDC) Verification
 * 
 * GOAL: Identify potential metastability risks in signals crossing 
 * asynchronous clock domains without proper synchronization.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>

struct Signal {
    std::string name;
    int domain; // 0 or 1
    bool is_synchronized;
};

class CDCChecker {
    std::vector<Signal> signals;

public:
    void add_signal(std::string name, int domain, bool sync) {
        signals.push_back({name, domain, sync});
    }

    int check_violations() {
        int violations = 0;
        // In a real tool, we'd check paths between registers in different domains.
        // Here, we simulate identifying unsynchronized crossings.
        for (const auto& s : signals) {
            if (s.domain != 0 && !s.is_synchronized) {
                violations++;
            }
        }
        return violations;
    }

    size_t memory_usage() const {
        return signals.size() * sizeof(Signal) + sizeof(*this);
    }
};

int main() {
    std::cout << "--- CDC Verification Laboratory ---" << std::endl;

    CDCChecker checker;
    checker.add_signal("data_bus[0]", 1, false); // Violation
    checker.add_signal("data_bus[1]", 1, false); // Violation
    checker.add_signal("ack_sync", 1, true);     // Safe
    checker.add_signal("local_reg", 0, false);   // Safe (same domain)

    lab::print_qor("CDC Metadata", checker.memory_usage());

    int violations = 0;
    {
        lab::Benchmark b("CDC Rule Checking");
        violations = checker.check_violations();
    }

    std::cout << "[METRICS] CDC Violations Found: " << violations << std::endl;
    lab::print_qor("CDC Results", 0, violations);

    return 0;
}
