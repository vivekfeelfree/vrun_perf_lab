# Module 17: Concurrent Data Structures (Lock-Free Stack)

## The Core Problem: The Lock Bottleneck
When multiple threads access a shared `std::stack`, we usually protect it with a `std::mutex`:
```cpp
lock_guard lock(m);
stack.push(x);
```
**Problem:** If 100 threads are trying to push, they all queue up for the same lock. Only one thread can work at a time. The system is "Serialized," not "Parallel."

## 1. Lock-Free Programming
Lock-free structures use **Atomic Operations** instead of Mutexes. The most important one is **CAS (Compare-and-Swap)**.

### How a Lock-Free Push Works:
1.  Read the current `top` pointer.
2.  Create a new node that points to this `top`.
3.  **CAS:** "Update `top` to my new node, but ONLY if `top` is still what I read in step 1."
4.  If it changed (another thread won the race), go back to step 1.

## 2. Mechanical Sympathy: Memory Ordering
Atomicity isn't enough. We must also ensure that the CPU and the compiler don't reorder our instructions in a way that makes the node's data visible *before* the pointer is updated.
- `memory_order_acquire`
- `memory_order_release`

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`MutexStack`**: A standard stack protected by a mutex.
2.  **`LockFreeStack`**: A stack using `std::atomic` and CAS.

## 🎛 Experimental Controls
- **Contention:** Measure performance with 2, 4, and 8 threads.
- **Work-per-thread:** Does the lock-free version stay faster as we add more threads?
