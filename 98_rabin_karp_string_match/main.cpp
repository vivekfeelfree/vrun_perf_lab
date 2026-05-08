/**
 * EXPERIMENT: Rabin-Karp String Matching
 * 
 * GOAL: Use rolling hashes to efficiently find all occurrences 
 * of a pattern string in a large text.
 */

#include "../include/harness.hpp"
#include <vector>
#include <string>

class RabinKarp {
    long long base = 256;
    long long mod = 1e9 + 7;

public:
    int search(const std::string& pattern, const std::string& text) {
        int n = text.size();
        int m = pattern.size();
        if (m > n) return 0;

        long long h_p = 0, h_t = 0, h_max = 1;
        for (int i = 0; i < m - 1; ++i) h_max = (h_max * base) % mod;

        for (int i = 0; i < m; ++i) {
            h_p = (base * h_p + pattern[i]) % mod;
            h_t = (base * h_t + text[i]) % mod;
        }

        int matches = 0;
        for (int i = 0; i <= n - m; ++i) {
            if (h_p == h_t) {
                if (text.substr(i, m) == pattern) matches++;
            }
            if (i < n - m) {
                h_t = (base * (h_t - text[i] * h_max) + text[i + m]) % mod;
                if (h_t < 0) h_t += mod;
            }
        }
        return matches;
    }
};

int main() {
    std::string text = "the quick brown fox jumps over the lazy dog and the other dog";
    std::string pattern = "the";
    std::cout << "--- Rabin-Karp String Matching Laboratory ---" << std::endl;

    RabinKarp rk;
    int matches = 0;
    {
        lab::Benchmark b("Rolling Hash Search");
        matches = rk.search(pattern, text);
    }

    std::cout << "[METRICS] Pattern '" << pattern << "' found " << matches << " times." << std::endl;
    lab::print_qor("Search Memory", text.size() + pattern.size());

    return 0;
}
