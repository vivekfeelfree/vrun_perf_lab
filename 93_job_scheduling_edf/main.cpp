/**
 * EXPERIMENT: Job Scheduling (Earliest Deadline First)
 * 
 * GOAL: Implement the EDF scheduling heuristic to maximize the 
 * number of tasks completed before their deadlines.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Task {
    int id;
    int duration;
    int deadline;
    bool operator<(const Task& other) const { return deadline < other.deadline; }
};

class EDFScheduler {
public:
    int solve(std::vector<Task>& tasks) {
        std::sort(tasks.begin(), tasks.end());
        int current_time = 0;
        int completed = 0;

        for (const auto& t : tasks) {
            if (current_time + t.duration <= t.deadline) {
                current_time += t.duration;
                completed++;
            }
        }
        return completed;
    }
};

int main() {
    int N = 1000;
    std::cout << "--- Job Scheduling (EDF) Laboratory (" << N << " tasks) ---" << std::endl;

    std::vector<Task> tasks;
    for (int i = 0; i < N; ++i) {
        tasks.push_back({i, rand() % 20 + 1, rand() % 500 + 50});
    }

    EDFScheduler scheduler;
    int done = 0;
    {
        lab::Benchmark b("EDF Scheduling Heuristic");
        done = scheduler.solve(tasks);
    }

    std::cout << "[METRICS] Tasks Completed On Time: " << done << std::endl;
    lab::print_qor("Schedule Stats", tasks.size() * sizeof(Task), done);

    return 0;
}
