# Module 06: Binary Heaps & Cache-Friendly Priority Queues

## The Core Problem: Efficient Priority Management
In systems software, we often need to "Find the Min" or "Find the Max" while items are being added and removed constantly.
- `std::sort` after every add: $O(N \log N)$ (Too slow).
- `std::vector` + Search: $O(N)$ (Too slow for large N).
- **Binary Heap:** $O(\log N)$ for both insert and extract.

## 1. The Array-Based Heap
Binary heaps are usually stored in a flat array to avoid pointer overhead:
- Parent: `i`
- Left Child: `2i + 1`
- Right Child: `2i + 2`

**The Cache Problem:** As the heap grows, children are located many cache lines away from their parents. This causes "pointer-chase-like" cache misses even though we are using an array.

## 2. Advanced: D-ary Heaps (4-ary)
By increasing the branching factor to 4 children per node:
1.  **The tree is shallower:** $\log_4 N$ instead of $\log_2 N$.
2.  **Better Spatial Locality:** All 4 children of a node might fit in a single 64-byte cache line (if the objects are small).
3.  **Trade-off:** We do more comparisons per level, but fewer memory fetches. Since memory is 100x slower than a comparison, this is usually a win.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`std::priority_queue`:** The standard library implementation.
2.  **`lab::BinaryHeap`:** Our hand-rolled array-based version.
3.  **`lab::DaryHeap<4>`:** A cache-optimized heap.

## 🎛 Experimental Controls
- **Element Size:** Does a heap of `int` behave differently than a heap of 128-byte `struct`s? (Spoiler: Larger structs make D-ary heaps even more important).
- **Heap Size:** Measure how performance drops once the heap exceeds the L3 cache size.
