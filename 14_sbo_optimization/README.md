# Module 13: Small Buffer Optimization (SBO)

## The Core Problem: Short-Lived Small Allocations
Many objects in a system are small:
- Short strings (e.g., variable names in a compiler: `i`, `tmp`).
- Small lambdas (e.g., used in `std::find_if`).

If we call `malloc` for every 2-byte string, we pay a massive price in metadata, fragmentation, and speed (as seen in Module 02).

## 1. The SBO Solution
SBO uses a `union` to store data:
- **Small Case:** The data is stored in a fixed-size `char[]` buffer inside the object.
- **Large Case:** The data is stored on the heap, and the object holds a pointer.

```cpp
union {
    char internal_buffer[16];
    char* heap_ptr;
};
```

## 2. Advantages
1.  **Zero Heap Access:** For small items, `malloc` is never called.
2.  **Locality:** The data is in the same cache line as the object itself.
3.  **Deterministic:** No risk of heap fragmentation for small items.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`NaiveString`**: Always allocates on the heap.
2.  **`SBOString`**: Uses a 16-byte internal buffer.

## 🎛 Experimental Controls
- **Threshold:** Test at exactly 15 bytes, 16 bytes, and 17 bytes to see the "performance cliff" when SBO switches to the heap.
- **Batch Processing:** Create 1 million small strings and measure the total time.
