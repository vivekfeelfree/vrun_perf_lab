/**
 * EXPERIMENT: K-Means Clustering
 * 
 * GOAL: Implement the K-Means algorithm to partition a set of 
 * points into K clusters.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

struct Point { float x, y; int cluster; };

class KMeans {
    int k;
    std::vector<Point> points;
    std::vector<Point> centroids;

public:
    KMeans(int k, int n) : k(k), centroids(k) {
        for (int i = 0; i < n; ++i) points.push_back({(float)(rand() % 1000), (float)(rand() % 1000), -1});
        for (int i = 0; i < k; ++i) centroids[i] = points[i];
    }

    void solve(int iterations) {
        for (int iter = 0; iter < iterations; ++iter) {
            // Assignment step
            for (auto& p : points) {
                float min_dist = 1e18;
                for (int i = 0; i < k; ++i) {
                    float d = std::pow(p.x - centroids[i].x, 2) + std::pow(p.y - centroids[i].y, 2);
                    if (d < min_dist) {
                        min_dist = d;
                        p.cluster = i;
                    }
                }
            }

            // Update step
            std::vector<float> sum_x(k, 0), sum_y(k, 0);
            std::vector<int> count(k, 0);
            for (const auto& p : points) {
                sum_x[p.cluster] += p.x;
                sum_y[p.cluster] += p.y;
                count[p.cluster]++;
            }
            for (int i = 0; i < k; ++i) {
                if (count[i] > 0) {
                    centroids[i].x = sum_x[i] / count[i];
                    centroids[i].y = sum_y[i] / count[i];
                }
            }
        }
    }

    size_t memory_usage() const { return points.size() * sizeof(Point) + centroids.size() * sizeof(Point); }
};

int main() {
    int N = 1000, K = 5;
    std::cout << "--- K-Means Clustering Laboratory (" << N << " points) ---" << std::endl;

    KMeans km(K, N);
    lab::print_qor("Point Cloud", km.memory_usage());

    {
        lab::Benchmark b("K-Means Optimization (20 iterations)");
        km.solve(20);
    }

    lab::print_qor("Final Centroids", 0, K);

    return 0;
}
