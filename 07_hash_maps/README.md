# Module 07: Robin Hood Hashing (Flat Maps)

## The Core Problem: Cache Locality in Hash Maps
`std::unordered_map` uses **Chaining**. Each bucket is a linked list of nodes.
- **Problem 1: Pointer Chasing.** To find a key, the CPU must jump to a random memory address for the bucket, then jump again for each node in the list.
- **Problem 2: Metadata Waste.** Each node has `next` pointers and allocation overhead.

## 1. The Solution: Open Addressing (Flat Maps)
In a Flat Map, all keys and values are stored in a single contiguous array. There are no linked lists.
- If a collision occurs at index `i`, we just look at `i+1`, `i+2`, etc. (Linear Probing).

**The Challenge of Linear Probing:** If many keys hash to the same area, we get "Clusters," which make searches very slow.

## 2. Robin Hood Hashing: "Steal from the Rich"
Robin Hood Hashing is an optimization for Linear Probing. We keep track of the **Probe Distance** (how far a key is from its original hash position).

- **The Rule:** If we are inserting a key and its probe distance is *greater* than the current key's probe distance, we swap them.
- **Result:** We "steal" from the "rich" (keys with short probe distances) to give to the "poor" (keys with long distances). This drastically reduces the *variance* in lookup times, keeping almost all lookups within a few cache lines.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`std::unordered_map`:** The baseline (Chaining).
2.  **`lab::RobinHoodMap`:** Our custom flat map.

## 🎛 Experimental Controls
- **Load Factor:** What happens when the map is 90% full? (Flat maps usually degrade here, but Robin Hood stays remarkably stable).
- **Search Type:** Compare "Hit" searches (key exists) vs "Miss" searches (key does not exist).
