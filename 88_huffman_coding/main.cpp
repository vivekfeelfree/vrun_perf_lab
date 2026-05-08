/**
 * EXPERIMENT: Huffman Coding
 * 
 * GOAL: Implement Huffman's greedy algorithm for optimal prefix-free 
 * binary codes to compress data.
 */

#include "../include/harness.hpp"
#include <vector>
#include <queue>
#include <map>

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    bool operator>(const Node& other) const { return freq > other.freq; }
};

class HuffmanCoder {
public:
    Node* build_tree(const std::map<char, int>& freqs) {
        std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> pq;
        for (auto const& [ch, freq] : freqs) {
            pq.push(new Node{ch, freq, nullptr, nullptr});
        }

        while (pq.size() > 1) {
            Node *l = pq.top(); pq.pop();
            Node *r = pq.top(); pq.pop();
            pq.push(new Node{'\0', l->freq + r->freq, l, r});
        }
        return pq.top();
    }

    void compute_codes(Node* root, std::string code, std::map<char, std::string>& codes) {
        if (!root) return;
        if (root->ch != '\0') codes[root->ch] = code;
        compute_codes(root->left, code + "0", codes);
        compute_codes(root->right, code + "1", codes);
    }
};

int main() {
    std::string text = "huffman coding experiment for prefix codes";
    std::cout << "--- Huffman Coding Laboratory ---" << std::endl;

    std::map<char, int> freqs;
    for (char c : text) freqs[c]++;

    HuffmanCoder coder;
    std::map<char, std::string> codes;
    {
        lab::Benchmark b("Huffman Tree & Code Generation");
        Node* root = coder.build_tree(freqs);
        coder.compute_codes(root, "", codes);
    }

    std::cout << "[METRICS] Unique Characters: " << freqs.size() << std::endl;
    for (auto const& [ch, code] : codes) {
        if (ch == ' ') std::cout << "  ' ': " << code << std::endl;
        else std::cout << "  " << ch << ": " << code << std::endl;
    }

    lab::print_qor("Huffman Metadata", codes.size() * 16);

    return 0;
}
