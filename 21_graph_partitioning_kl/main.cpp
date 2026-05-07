/**
 * EXPERIMENT: Kernighan-Lin Graph Partitioning (Optimized)
 * 
 * GOAL: Measure the effectiveness of the K-L heuristic in reducing 
 * the cut-set size of a graph.
 * 
 * Complexity: O(Iterations * N^2) with incremental updates.
 */

#include "../include/harness.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

struct Graph {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int8_t> matrix; // Flat matrix for O(1) lookup
    
    Graph(int nodes) : n(nodes), adj(nodes), matrix(nodes * nodes, 0) {}
    
    void add_edge(int u, int v) {
        if (u == v || u >= n || v >= n) return;
        if (!matrix[u * n + v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            matrix[u * n + v] = matrix[v * n + u] = 1;
        }
    }

    int count_cut(const std::vector<int>& partition) {
        int cut = 0;
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                if (partition[u] != partition[v]) cut++;
            }
        }
        return cut / 2;
    }
};

class KLPartitioner {
    Graph& g;
public:
    KLPartitioner(Graph& graph) : g(graph) {}

    void run(std::vector<int>& partition) {
        bool improved = true;
        int pass = 0;
        const int MAX_PASSES = 50; 
        
        while (improved && pass < MAX_PASSES) {
            improved = false;
            pass++;
            std::vector<bool> locked(g.n, false);
            std::vector<int> D(g.n, 0);

            // Initial D values
            for (int i = 0; i < g.n; ++i) {
                int p_i = partition[i];
                for (int neighbor : g.adj[i]) {
                    if (p_i != partition[neighbor]) D[i]++;
                    else D[i]--;
                }
            }

            std::vector<std::pair<int, int>> swaps;
            std::vector<int> gains;
            swaps.reserve(g.n / 2);
            gains.reserve(g.n / 2);

            for (int step = 0; step < g.n / 2; ++step) {
                int best_u = -1, best_v = -1;
                int max_gain = std::numeric_limits<int>::min();

                // Sort candidates by D values to allow pruning
                std::vector<int> cand_u, cand_v;
                for (int i = 0; i < g.n; ++i) {
                    if (locked[i]) continue;
                    if (partition[i] == 0) cand_u.push_back(i);
                    else cand_v.push_back(i);
                }

                std::sort(cand_u.begin(), cand_u.end(), [&](int a, int b) {
                    return D[a] > D[b];
                });
                std::sort(cand_v.begin(), cand_v.end(), [&](int a, int b) {
                    return D[a] > D[b];
                });

                // Pruned search
                for (int u : cand_u) {
                    if (D[u] + D[cand_v[0]] - 0 < max_gain) break; // Cannot possibly beat max_gain

                    for (int v : cand_v) {
                        int gain = D[u] + D[v] - (g.matrix[u * g.n + v] ? 2 : 0);
                        if (gain > max_gain) {
                            max_gain = gain;
                            best_u = u;
                            best_v = v;
                        }
                        // Since we sorted cand_v, if D[u] + D[v] is already too small, we can stop for this u
                        if (D[u] + D[v] - 2 < max_gain) break; 
                    }
                }

                if (best_u == -1) break;

                locked[best_u] = locked[best_v] = true;
                swaps.push_back({best_u, best_v});
                gains.push_back(max_gain);

                // Update D values for all unlocked nodes
                for (int i = 0; i < g.n; ++i) {
                    if (locked[i]) continue;
                    
                    int n_idx = i * g.n;
                    if (g.matrix[n_idx + best_u]) {
                        D[i] += (partition[i] == 0 ? 2 : -2);
                    }
                    if (g.matrix[n_idx + best_v]) {
                        D[i] += (partition[i] == 1 ? 2 : -2);
                    }
                }
            }

            // Find best prefix of swaps
            int max_sum = 0;
            int current_sum = 0;
            int best_k = -1;
            for (int i = 0; i < (int)gains.size(); ++i) {
                current_sum += gains[i];
                if (current_sum > max_sum) {
                    max_sum = current_sum;
                    best_k = i;
                }
            }

            if (best_k != -1) {
                for (int i = 0; i <= best_k; ++i) {
                    int u = swaps[i].first;
                    int v = swaps[i].second;
                    std::swap(partition[u], partition[v]);
                }
                improved = true;
            }
        }
    }
};

int main() {
    int N = 400; 
    std::cout << "--- Kernighan-Lin Partitioning Laboratory (" << N << " nodes) ---" << std::endl;

    Graph g(N);
    std::mt19937 gen(42);
    for (int i = 0; i < N * 10; ++i) {
        g.add_edge(gen() % N, gen() % N);
    }

    std::vector<int> partition(N);
    for (int i = 0; i < N / 2; ++i) partition[i] = 0;
    for (int i = N / 2; i < N; ++i) partition[i] = 1;

    int initial_cut = g.count_cut(partition);
    size_t total_adj_size = 0;
    for(const auto& v : g.adj) total_adj_size += v.size() * sizeof(int);
    size_t est_mem = sizeof(Graph) + (g.adj.size() * sizeof(std::vector<int>)) + total_adj_size + g.matrix.size();

    lab::print_qor("Initial Random Cut", est_mem, initial_cut);

    {
        lab::Benchmark b("Kernighan-Lin Optimization");
        KLPartitioner kl(g);
        kl.run(partition);
    }

    int final_cut = g.count_cut(partition);
    lab::print_qor("Final Optimized Cut", est_mem, final_cut);
    if (initial_cut > 0) {
        std::cout << "[METRICS] Improvement: " << (float)(initial_cut - final_cut) / initial_cut * 100 << "%" << std::endl;
    }

    return 0;
}
