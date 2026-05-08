/**
 * EXPERIMENT: Global Routing (Maze Routing - Soukup's)
 * 
 * GOAL: Implement a simple maze routing algorithm to find a path 
 * between two pins on a grid while avoiding obstacles.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <algorithm>

struct Point { int x, y; };

class MazeRouter {
    int width, height;
    std::vector<std::vector<int>> grid; // 0: free, 1: obstacle, 2: visited

public:
    MazeRouter(int w, int h) : width(w), height(h), grid(w, std::vector<int>(h, 0)) {}

    void add_obstacle(int x, int y) { grid[x][y] = 1; }

    int find_path(Point start, Point end) {
        std::queue<std::pair<Point, int>> q;
        q.push({start, 0});
        grid[start.x][start.y] = 2;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (curr.first.x == end.x && curr.first.y == end.y) return curr.second;

            for (int i = 0; i < 4; ++i) {
                int nx = curr.first.x + dx[i];
                int ny = curr.first.y + dy[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[nx][ny] == 0) {
                    grid[nx][ny] = 2;
                    q.push({{nx, ny}, curr.second + 1});
                }
            }
        }
        return -1;
    }

    size_t memory_usage() const { return width * height * sizeof(int); }
};

int main() {
    int W = 200, H = 200;
    std::cout << "--- Global Maze Routing Laboratory ---" << std::endl;

    MazeRouter router(W, H);
    // Add a wall in the middle
    for (int i = 0; i < 150; ++i) router.add_obstacle(100, i);

    lab::print_qor("Routing Grid", router.memory_usage());

    int dist = 0;
    {
        lab::Benchmark b("Maze Routing (Lee/BFS)");
        dist = router.find_path({10, 10}, {190, 190});
    }

    std::cout << "[METRICS] Path Distance: " << dist << std::endl;
    lab::print_qor("Final Path", 0, dist);

    return 0;
}
