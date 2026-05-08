/**
 * EXPERIMENT: Prime Factorization (Trial Division)
 * 
 * GOAL: Use trial division to find the prime factors of a 
 * large integer.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>

class PrimeSolver {
public:
    std::vector<long long> factorize(long long n) {
        std::vector<long long> factors;
        while (n % 2 == 0) {
            factors.push_back(2);
            n /= 2;
        }
        for (long long i = 3; i <= std::sqrt(n); i += 2) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        if (n > 2) factors.push_back(n);
        return factors;
    }
};

int main() {
    long long N = 123456789012345LL;
    std::cout << "--- Prime Factorization Laboratory ---" << std::endl;

    PrimeSolver solver;
    std::vector<long long> factors;
    {
        lab::Benchmark b("Trial Division Factorization");
        factors = solver.factorize(N);
    }

    std::cout << "[METRICS] Factors for " << N << ":" << std::endl;
    for (long long f : factors) std::cout << "  " << f << std::endl;

    lab::print_qor("Factor Count", 0, factors.size());

    return 0;
}
