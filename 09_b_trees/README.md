# Module 09: B-Trees (Memory-Resident Cache Locality)

## The Core Problem: Binary Search Tree Cache Misses
A Binary Search Tree (like `std::set`) has a branching factor of 2.
- To store 1,000,000 items, the tree is ~20 levels deep.
- Every step down the tree is a potential cache miss because nodes are scattered in memory.
- Total cache misses: ~20 per lookup.

## 1. The B-Tree Solution
A B-Tree has many keys per node (e.g., 16 keys).
- To store 1,000,000 items with a branching factor of 16, the tree is only ~5 levels deep ($\log_{16} 1,000,000$).
- Total cache misses: ~5 per lookup.

## 2. Mechanical Sympathy: Node Size
By making a B-Tree node exactly 64 bytes (the size of a cache line) or 128 bytes, we ensure that when the CPU fetches a node, it gets *all* the keys for that level in a single memory transaction.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`std::set<int>`:** The binary search tree baseline.
2.  **`lab::BTree`:** A cache-aligned multi-way search tree.

## 🎛 Experimental Controls
- **Order (Keys per Node):** Experiment with 4, 8, 16, and 32 keys per node. See where the sweet spot is for your CPU's L1/L2 cache.
- **Data Size:** Watch as the B-Tree's lead grows when the total data size exceeds the L3 cache.
