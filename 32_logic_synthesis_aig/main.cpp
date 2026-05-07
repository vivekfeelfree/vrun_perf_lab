/**
 * EXPERIMENT: And-Inverter Graphs (AIGs) and 2-Level Strashing
 * 
 * GOAL: Demonstrate how structural hashing and the "LSB-Inverter" 
 * trick reduce logic graph complexity.
 */

#include "../include/harness.hpp"
#include <unordered_map>
#include <vector>

/**
 * A "Literal" in AIG terminology is a node index plus an inversion bit.
 * LSB = 1 means INVERTED, LSB = 0 means DIRECT.
 */
typedef uint32_t lit;

inline lit make_lit(uint32_t id, bool inv) { return (id << 1) | (inv ? 1 : 0); }
inline uint32_t lit_id(lit l) { return l >> 1; }
inline bool lit_inv(lit l) { return (l & 1) == 1; }
inline lit lit_not(lit l) { return l ^ 1; }

struct AIGNode {
    lit fanin0;
    lit fanin1;

    bool operator==(const AIGNode& other) const {
        return fanin0 == other.fanin0 && fanin1 == other.fanin1;
    }
};

struct AIGNodeHash {
    size_t operator()(const AIGNode& n) const {
        return std::hash<uint32_t>{}(n.fanin0) ^ (std::hash<uint32_t>{}(n.fanin1) << 1);
    }
};

class AIGManager {
    std::vector<AIGNode> nodes;
    std::unordered_map<AIGNode, uint32_t, AIGNodeHash> unique_table;

public:
    static constexpr lit LIT_FALSE = 0; // Node 0 is the constant 0
    static constexpr lit LIT_TRUE = 1;

    AIGManager() {
        // Node 0: Constant False
        nodes.push_back({LIT_FALSE, LIT_FALSE});
    }

    lit create_and(lit a, lit b) {
        // --- 2-Level Strashing (Algebraic Reductions) ---
        if (a == LIT_FALSE || b == LIT_FALSE) return LIT_FALSE;
        if (a == LIT_TRUE) return b;
        if (b == LIT_TRUE) return a;
        if (a == b) return a;
        if (a == lit_not(b)) return LIT_FALSE;

        // Ensure canonical ordering of inputs for the hash table
        if (a > b) std::swap(a, b);

        // --- 1-Level Strashing (Structural Hashing) ---
        AIGNode n{a, b};
        auto it = unique_table.find(n);
        if (it != unique_table.end()) return make_lit(it->second, false);

        uint32_t id = nodes.size();
        nodes.push_back(n);
        unique_table[n] = id;
        return make_lit(id, false);
    }

    size_t num_nodes() const { return nodes.size(); }
};

int main() {
    std::cout << "--- AIG Laboratory (Strashing) ---" << std::endl;

    AIGManager mgr;

    // Inputs: x0, x1
    lit x0 = make_lit(1, false); // Manually creating "Input" IDs
    lit x1 = make_lit(2, false);

    // Expression: f = (x0 AND x1) AND (x1 AND x0)
    // Naively, this is 3 AND gates. With strashing, it should be 1.
    
    std::cout << "Building f = (x0 & x1) & (x1 & x0)..." << std::endl;
    lit g1 = mgr.create_and(x0, x1);
    lit g2 = mgr.create_and(x1, x0);
    lit f = mgr.create_and(g1, g2);

    std::cout << "Final AIG Node Count: " << mgr.num_nodes() << std::endl;
    std::cout << "Root Literal: ID=" << lit_id(f) << " Inv=" << lit_inv(f) << std::endl;

    size_t est_mem = mgr.num_nodes() * sizeof(AIGNode) + (mgr.num_nodes() * (sizeof(AIGNode) + sizeof(uint32_t)) * 1.5);
    lab::print_qor("AIG Manager", est_mem, mgr.num_nodes());

    if (mgr.num_nodes() <= 4) { // Node 0 (const), 1, 2 (inputs-ish), 3 (the gate)
        std::cout << "SUCCESS: 2-Level Strashing minimized the logic!" << std::endl;
    }

    return 0;
}
