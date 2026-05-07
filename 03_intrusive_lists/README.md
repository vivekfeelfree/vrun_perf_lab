# Module 03: Intrusive Lists & The `container_of` Magic

## The Core Concept: Intrusive vs. Non-Intrusive
In standard C++ (`std::list<T>`), the list "owns" the data. When you push an item, the list allocates a wrapper node:
```cpp
// Non-Intrusive (std::list)
struct InternalNode {
    InternalNode *next, *prev;
    T data; // Your data is copied here
};
```
**Problem:** This forces an extra allocation and a copy. Also, an object cannot easily live in two lists at once.

In **Intrusive Lists** (used in Linux Kernel, LLVM, etc.), the object "owns" the list links:
```cpp
// Intrusive
struct MyObject {
    int id;
    lab::ListLink link; // The "Hook" is inside the struct
};
```

## 1. The `container_of` Trick
The biggest challenge with intrusive lists is: If I have a pointer to the `ListLink`, how do I get a pointer to the `MyObject` that contains it?

We use pointer arithmetic. If we know the offset of `link` within `MyObject`, we can subtract that offset from the link's address to find the start of the object.

```cpp
// The Magic Formula
ObjectPtr = (char*)LinkPtr - OffsetOf(MyObject, link);
```

## 2. Advantages for System Software
1.  **Zero Allocation:** Adding an object to a list requires zero memory allocation (the memory is already inside the object).
2.  **No Copies:** The object is never moved or copied.
3.  **Multi-Homing:** An object can have multiple `ListLink` members, allowing it to be part of many lists simultaneously (e.g., a "Ready Queue" and an "All Processes" list) without extra overhead.
4.  **Cache Locality:** The link and the data are in the same cache line.

## 3. The Experiment
In `main.cpp`, we:
1.  Compare the allocation speed of `std::list` vs. `IntrusiveList`.
2.  Demonstrate "Multi-Homing": A single `Process` struct inhabiting two different lists.
3.  Show how to remove an item from a list in $O(1)$ without even knowing which list it's in (since the links are in the object itself).

## 🎛 Experimental Controls
- Try adding a third list to the `Process` struct (e.g., `priority_link`).
- Measure the time it takes to iterate 1 million elements in `std::list` vs `IntrusiveList`.
