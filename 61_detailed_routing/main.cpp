/**
 * EXPERIMENT: Detailed Routing (A* with Grid Costs)
 * 
 * GOAL: Implement A* search on a multi-layer grid with variable costs 
 * for vias and preferred routing directions.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <cmath>

struct Point3D { int x, y, z; };
struct Node {
    Point3D p;
    float g, h;
    bool operator>(const Node& other) const { return (g + h) > (other.g + other.h); }
};

class DetailedRouter {
    int width, height, layers;
    float via_cost = 10.0f;

public:
    DetailedRouter(int w, int h, int l) : width(w), height(h), layers(l) {}

    float heuristic(Point3D a, Point3D b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z) * via_cost;
    }

    float solve(Point3D start, Point3D end) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::vector<std::vector<std::vector<float>>> dist(width, std::vector<std::vector<float>>(height, std::vector<float>(layers, 1e18)));

        dist[start.x][start.y][start.z] = 0;
        pq.push({start, 0, heuristic(start, end)});

        int dx[] = {1, -1, 0, 0, 0, 0};
        int dy[] = {0, 0, 1, -1, 0, 0};
        int dz[] = {0, 0, 0, 0, 1, -1};

        size_t visited = 0;
        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            visited++;

            if (curr.p.x == end.x && curr.p.y == end.y && curr.p.z == end.z) {
                std::cout << "[METRICS] Nodes Explored: " << visited << std::endl;
                return curr.g;
            }

            for (int i = 0; i < 6; ++i) {
                Point3D next = {curr.p.x + dx[i], curr.p.y + dy[i], curr.p.z + dz[i]};
                if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height || next.z < 0 || next.z >= layers) continue;

                float move_cost = (dz[i] != 0) ? via_cost : 1.0f;
                // Layer preference: Even layers horizontal, Odd layers vertical
                if (dz[i] == 0) {
                    if (next.z % 2 == 0 && dx[i] == 0) move_cost += 2.0f; // Penalty for vertical on horizontal layer
                    if (next.z % 2 != 0 && dy[i] == 0) move_cost += 2.0f; // Penalty for horizontal on vertical layer
                }

                if (dist[next.x][next.y][next.z] > curr.g + move_cost) {
                    dist[next.x][next.y][next.z] = curr.g + move_cost;
                    pq.push({next, dist[next.x][next.y][next.z], heuristic(next, end)});
                }
            }
        }
        return -1.0f;
    }

    size_t memory_usage() const { return width * height * layers * sizeof(float); }
};

int main() {
    int W = 100, H = 100, L = 4;
    std::cout << "--- Detailed Routing (Multi-layer A*) Laboratory ---" << std::endl;

    DetailedRouter router(W, H, L);
    lab::print_qor("Grid Memory", router.memory_usage());

    float cost = 0;
    {
        lab::Benchmark b("Multi-layer Routing Search");
        cost = router.solve({0, 0, 0}, {90, 90, 3});
    }

    std::cout << "[METRICS] Final Route Cost: " << cost << std::endl;
    lab::print_qor("Final Result", 0, (size_t)cost);

    return 0;
}
