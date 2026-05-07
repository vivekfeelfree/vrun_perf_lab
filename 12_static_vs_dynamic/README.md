# Module 11: Static Dispatch vs. Dynamic Dispatch

## The Core Problem: The Cost of `virtual`
C++ offers two ways to achieve polymorphism:
1.  **Dynamic Dispatch:** Using `virtual` functions and inheritance.
2.  **Static Dispatch:** Using templates and "duck typing" or `std::variant`.

### The `virtual` Penalty
When you call a `virtual` function:
1.  **Load the VTable Pointer:** The CPU must read the pointer from the object's memory.
2.  **Load the Function Pointer:** The CPU must read the address of the function from the VTable.
3.  **Indirect Jump:** The CPU must jump to an address it doesn't know until runtime.
4.  **No Inlining:** Because the compiler doesn't know which function will be called, it *cannot* inline the code. This is the biggest penalty.

### The Template Advantage
With templates, the compiler knows exactly which function is being called at compile-time. It can:
- Inline the entire function.
- Perform constant folding.
- Optimize register usage across the call boundary.

## 1. The Experiment
In `main.cpp`, we will implement a "Processor" that handles different "Task" types:
1.  **`DynamicTask`**: Uses a base class with a `virtual execute()` method.
2.  **`StaticTask`**: Uses a template-based "CRTP" (Curiously Recurring Template Pattern) or simple function overloading.

## 🎛 Experimental Controls
- **Work Per Task:** If a task does a lot of work, the `virtual` overhead is small. If a task does very little (e.g., adding two numbers), the `virtual` overhead will dominate.
- **Inlining:** We will explicitly check how inlining changes the performance of the static version.
