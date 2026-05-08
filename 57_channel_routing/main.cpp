/**
 * EXPERIMENT: Channel Routing (Left-Edge Algorithm)
 * 
 * GOAL: Assign horizontal segments (nets) to the minimum number 
 * of tracks within a routing channel.
 */

#include "../include/harness.hpp"
#include <vector>
#include <algorithm>

struct Segment {
    int id, l, r;
    int track;
    bool operator<(const Segment& other) const { return l < other.l; }
};

class ChannelRouter {
    std::vector<Segment> nets;

public:
    void add_net(int id, int l, int r) {
        nets.push_back({id, l, r, -1});
    }

    int route() {
        std::sort(nets.begin(), nets.end());
        int tracks = 0;
        std::vector<bool> routed(nets.size(), false);
        int remaining = nets.size();

        while (remaining > 0) {
            tracks++;
            int last_r = -1;
            for (size_t i = 0; i < nets.size(); ++i) {
                if (!routed[i] && nets[i].l > last_r) {
                    nets[i].track = tracks;
                    routed[i] = true;
                    last_r = nets[i].r;
                    remaining--;
                }
            }
        }
        return tracks;
    }

    size_t memory_usage() const { return nets.size() * sizeof(Segment); }
};

int main() {
    int NETS = 2000;
    std::cout << "--- Channel Routing (Left-Edge) Laboratory ---" << std::endl;

    ChannelRouter router;
    for (int i = 0; i < NETS; ++i) {
        int l = rand() % 1000;
        int r = l + rand() % 500 + 1;
        router.add_net(i, l, r);
    }

    lab::print_qor("Channel Design", router.memory_usage());

    int tracks = 0;
    {
        lab::Benchmark b("Left-Edge Routing Heuristic");
        tracks = router.route();
    }

    std::cout << "[METRICS] Total Tracks Required: " << tracks << std::endl;
    lab::print_qor("Final Tracks", 0, (size_t)tracks);

    return 0;
}
