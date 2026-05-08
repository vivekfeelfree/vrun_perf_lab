# Module 41: BDD Variable Reordering (Sifting)

## 🎯 Goal
Demonstrate how variable order affects BDD size and implement a simple swap-based reordering heuristic.

## 🧠 Key Concept
The size of a Binary Decision Diagram (BDD) is extremely sensitive to the order of its variables. For some functions (like an adder), a good order yields linear size, while a bad order yields exponential size. Sifting is a heuristic that moves each variable to find its local optimal position.

## 📊 Metrics to Watch
- **Node Count:** Total number of BDD nodes for different orders.
- **Reordering Time:** Time spent swapping variables.
