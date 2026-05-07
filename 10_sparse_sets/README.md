# Module 10: Sparse Sets

## 🎯 Goal
Demonstrate the Sparse Set data structure, which provides $O(1)$ insertion, deletion, and lookup, while also allowing $O(N)$ dense iteration.

## 🧠 Key Concept
A Sparse Set uses two arrays:
1.  **Sparse Array:** Maps a value to its position in the dense array.
2.  **Dense Array:** Stores the actual values contiguously.

This allows us to iterate over elements in a cache-friendly way while maintaining fast random access and removal (by swapping the element to be removed with the last element in the dense array).

## 📊 Metrics to Watch
- **Iteration Speed:** Sparse sets are much faster to iterate than hash maps.
- **Memory Footprint:** The sparse array size depends on the maximum possible value, not the number of elements.
