# Module 02: Arena Allocation (Linear Allocator)

## The Core Problem: The `malloc` Tax
In high-performance systems (like a compiler front-end or a physics engine), we often need to allocate millions of small objects (AST nodes, particles) and then destroy them all at once.

Standard `std::malloc` or `new` has several hidden costs:
1.  **Metadata Overhead:** Every `malloc` stores extra bytes (size, flags) to know how to `free` that specific chunk.
2.  **Search Time:** `malloc` must search its "free list" for a hole that fits your request.
3.  **Fragmentation:** Over time, your memory looks like Swiss cheese, making it harder to find large contiguous blocks.
4.  **Locking:** In multi-threaded apps, `malloc` often uses a global lock, causing threads to stall.

## 1. The Solution: The Arena (Bump Allocator)
An Arena is a large, pre-allocated block of memory. To "allocate" from it, we simply:
1.  Check if there is enough space.
2.  Return the current "top" pointer.
3.  "Bump" the top pointer forward by the requested size.

### Complexity:
- **Allocation:** $O(1)$ (just a pointer addition).
- **Deallocation:** $O(1)$ (just reset the pointer to the start).

## 2. Alignment: The Hidden Requirement
As we saw in Module 01, CPUs hate unaligned data. Our Arena must ensure that even if you ask for 1 byte, the *next* allocation starts on a proper boundary (usually 8 bytes).

Formula for alignment:
```cpp
uintptr_t aligned_addr = (current_addr + alignment - 1) & ~(alignment - 1);
```
This bit-magic rounds `current_addr` up to the nearest multiple of `alignment`.

## 3. The Experiment
In `main.cpp`, we simulate a "Compiler Pass":
1.  Create 1,000,000 small nodes using `malloc` and then `free` them individually.
2.  Create the same 1,000,000 nodes using our `lab::Arena`.
3.  Observe that Arena allocation is nearly instant, and deallocation (resetting) is essentially free.

## 🎛 Experimental Controls
- Try changing the `default_block_size` in the Arena constructor. If it's too small, the Arena will frequently call `malloc` for new blocks, slowing it down.
