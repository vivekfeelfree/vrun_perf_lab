# Module 15: Type Erasure & The Callback Tax

## The Core Problem: Storing Callbacks
In an event-driven system (like an EDA simulator), we need to store thousands of "Listeners."
Some are raw functions, some are lambdas with huge captured states.

How do we store them in a single `vector`?
- **Function Pointers:** Only work for stateless functions.
- **Inheritance:** `struct Listener { virtual void run() = 0; }`. (Forces a heap allocation for every listener).
- **`std::function`:** Uses **Type Erasure**.

## 1. What is Type Erasure?
Type Erasure is a technique to "hide" the specific type of a lambda or object behind a uniform interface *without* requiring the user to use inheritance.

It usually involves:
1.  A templated constructor.
2.  An internal virtual call (Dynamic Dispatch).
3.  **SBO (Small Buffer Optimization)** to avoid heap allocation for small lambdas.

## 2. The Performance Cost
`std::function` is powerful but has three hidden costs:
1.  **Virtual Call:** As seen in Module 11.
2.  **Indirect Jump:** The CPU can't easily predict the target.
3.  **SBO Check:** Every call checks if the function is stored locally or on the heap.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **Raw Function Pointers.**
2.  **`std::function`**.
3.  **A custom "Fixed-Size Function"** (A common systems optimization).

## 🎛 Experimental Controls
- **Captured State:** How does performance change when a lambda captures 0 bytes vs 100 bytes?
- **Inlining:** See if the compiler can ever optimize a `std::function` call (Spoiler: Rarely).
