/**
 * EXPERIMENT: A* Pathfinding
 * 
 * GOAL: Demonstrate A* search efficiency on a grid using a heuristic 
 * to guide the search towards the target.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <cmath>
#include <map>

struct Node {
    int x, y;
    float g, h;
    bool operator>(const Node& other) const { return (g + h) > (other.g + other.h); }
};

class AStar {
    int width, height;
    
public:
    AStar(int w, int h) : width(w), height(h) {}

    float heuristic(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    float solve(int sx, int sy, int tx, int ty) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::vector<std::vector<float>> dist(width, std::vector<float>(height, 1e18));

        dist[sx][sy] = 0;
        pq.push({sx, sy, 0, heuristic(sx, sy, tx, ty)});

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        size_t visited = 0;
        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            visited++;

            if (curr.x == tx && curr.y == ty) {
                std::cout << "[METRICS] Visited Nodes: " << visited << std::endl;
                return curr.g;
            }

            if (curr.g > dist[curr.x][curr.y]) continue;

            for (int i = 0; i < 4; ++i) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (dist[nx][ny] > curr.g + 1.0f) {
                        dist[nx][ny] = curr.g + 1.0f;
                        pq.push({nx, ny, dist[nx][ny], heuristic(nx, ny, tx, ty)});
                    }
                }
            }
        }
        return -1.0f;
    }
};

int main() {
    int W = 500, H = 500;
    std::cout << "--- A* Search Laboratory (" << W << "x" << H << " grid) ---" << std::endl;

    AStar astar(W, H);
    
    float path_len = 0;
    {
        lab::Benchmark b("A* Pathfinding (Source to Sink)");
        path_len = astar.solve(0, 0, W-1, H-1);
    }

    std::cout << "[METRICS] Path Length: " << path_len << std::endl;

    return 0;
}
