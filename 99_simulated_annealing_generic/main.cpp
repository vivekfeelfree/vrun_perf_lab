/**
 * EXPERIMENT: Generic Simulated Annealing Framework
 * 
 * GOAL: Implement a reusable metaheuristic framework for solving 
 * complex combinatorial optimization problems.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <random>

class GenericAnnealer {
public:
    struct State {
        float energy;
        std::vector<int> config;
    };

    template<typename NeighborFunc, typename EnergyFunc>
    State solve(State initial, NeighborFunc get_neighbor, EnergyFunc get_energy, int iterations) {
        State current = initial;
        current.energy = get_energy(current.config);
        State best = current;

        float temp = 1000.0f;
        float cooling = 0.999f;
        std::mt19937 gen(42);
        std::uniform_real_distribution<float> dis(0, 1);

        for (int i = 0; i < iterations; ++i) {
            std::vector<int> next_config = get_neighbor(current.config);
            float next_energy = get_energy(next_config);

            if (next_energy < current.energy || dis(gen) < std::exp((current.energy - next_energy) / temp)) {
                current.config = next_config;
                current.energy = next_energy;
                if (current.energy < best.energy) best = current;
            }
            temp *= cooling;
        }
        return best;
    }
};

int main() {
    std::cout << "--- Generic Simulated Annealing Laboratory ---" << std::endl;

    GenericAnnealer annealer;
    // Example: Minimize sum of squares (trivial but demonstrates framework)
    auto energy_fn = [](const std::vector<int>& c) {
        float sum = 0;
        for (int x : c) sum += (float)x * x;
        return sum;
    };

    auto neighbor_fn = [](const std::vector<int>& c) {
        std::vector<int> next = c;
        int idx = rand() % next.size();
        next[idx] += (rand() % 3 - 1); // Mutate by -1, 0, or 1
        return next;
    };

    GenericAnnealer::State initial = {0, {10, -5, 20, 3, 11}};
    GenericAnnealer::State result;

    {
        lab::Benchmark b("Generic SA Optimization");
        result = annealer.solve(initial, neighbor_fn, energy_fn, 10000);
    }

    std::cout << "[METRICS] Optimized Energy: " << result.energy << std::endl;
    lab::print_qor("Framework Stats", initial.config.size() * sizeof(int));

    return 0;
}
