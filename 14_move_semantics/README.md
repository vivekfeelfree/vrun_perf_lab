# Module 14: Move Semantics & RVO (Copy Elision)

## The Core Problem: The "Expensive Return"
Consider this function:
```cpp
vector<int> get_data() {
    vector<int> v = {1, 2, 3};
    return v;
}
```
In old C++, this would:
1.  Create `v` on the stack.
2.  Allocate heap memory for `v`.
3.  Allocate *new* heap memory for the caller's version of the vector.
4.  Copy all data.
5.  Deallocate the old heap memory.

## 1. Move Semantics (`std::move`)
Instead of copying the heap memory, we "steal" it.
- **Copy:** `NewPtr = malloc(size); memcpy(NewPtr, OldPtr, size);`
- **Move:** `NewPtr = OldPtr; OldPtr = nullptr;`

## 2. RVO (Return Value Optimization)
Modern compilers are even smarter. With RVO, the compiler constructs the object *directly in the caller's memory space*, eliminating even the move.

## 3. The Experiment
In `main.cpp`, we will implement a `HeavyObject` that tracks its own copies and moves.
We will compare:
1.  **Old Style:** Passing by value and copying.
2.  **Move Style:** Using `std::move`.
3.  **RVO:** Seeing how the compiler automatically optimizes returns.

## 🎛 Experimental Controls
- **`noexcept`**: Observe how marking your move constructor `noexcept` allows `std::vector` to use it during reallocations.
- **Force Copy:** Explicitly disable RVO (if possible) to see the raw cost of copying 1 million items.
