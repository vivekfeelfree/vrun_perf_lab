# Module 10: Value Semantics vs. Pointer Semantics (DOD)

## The Core Problem: The "Indirection Tax"
In C++, you have a choice:
1.  **Pointer Semantics:** `std::vector<Object*>`
2.  **Value Semantics:** `std::vector<Object>`

### The OOP Trap (Pointer Semantics)
Traditional OOP encourages storing pointers to objects (especially for polymorphism).
- **Fragmentation:** Every `new Object` call puts the object in a random spot on the heap.
- **Pointer Chasing:** To process a vector of pointers, the CPU must:
    1. Fetch the pointer (Cache Miss?).
    2. Fetch the object the pointer points to (Definite Cache Miss).
- **VTable Overhead:** If you use `virtual` functions, there is another jump to the function table.

### The DOD Solution (Value Semantics)
Data-Oriented Design (DOD) treats data as a "stream." By storing objects by value in a contiguous array:
- **Prefetcher Friendly:** The CPU sees you are reading memory linearly and starts "pre-fetching" the next objects before you even ask for them.
- **Zero Indirection:** The data is *right there*. No pointers to follow.

## 1. AoS vs. SoA
- **AoS (Array of Structures):** `std::vector<Point>` where `Point { x, y, z }`. (Good for locality of a single object).
- **SoA (Structure of Arrays):** `struct Points { vector x, y, z; }`. (Best for SIMD and processing only specific fields).

## 2. The Experiment
In `main.cpp`, we will compare three ways to manage 1,000,000 "Entity" objects:
1.  **`std::vector<Entity*>`**: Pointers to scattered heap objects.
2.  **`std::vector<Entity>`**: Contiguous objects by value.
3.  **SoA (Structure of Arrays)**: Separating hot data from cold data.

## 🎛 Experimental Controls
- **Object Size:** How does the gap change if `Entity` is 16 bytes vs 1024 bytes?
- **Randomization:** What happens to the pointer version if we shuffle the pointers? (Spoiler: It gets much worse).
