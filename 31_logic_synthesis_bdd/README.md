# Module 20: Binary Decision Diagrams (BDDs) - EDA Logic Synthesis

## The Core Problem: Boolean Equivalence
In Logic Synthesis, we often transform a circuit to optimize it (e.g., reduce the number of gates). How do we know the new circuit still does the exact same thing as the old one?
Comparing truth tables is $O(2^n)$, which is impossible for a chip with 1,000 inputs.

## 1. The BDD (Binary Decision Diagram)
A BDD is a rooted, directed acyclic graph. Each node represents a decision on a boolean variable (0 or 1).
- **Canonicality:** If we use a fixed variable ordering, every boolean function has a *unique* BDD. To check if two circuits are equal, we just check if they point to the same BDD root node!

## 2. Implementation Nuances: The Unique Table
To keep the BDD canonical, we must never create the same node twice.
- Before creating a node `Node(var, low, high)`, we check a **Unique Table** (a specialized Hash Map). If it already exists, we return the existing pointer.
- This is a form of **Structural Hashing**.

## 3. The Computed Table (Memoization)
Boolean operations like `AND(BDD_A, BDD_B)` are recursive. We use a **Computed Table** (Cache) to store results. If we've already computed `AND(A, B) = C`, we return `C` instantly next time.

## 4. The Experiment
In `main.cpp`, we will:
1.  Implement a minimal BDD manager with a Unique Table.
2.  Represent a simple boolean function: `(a AND b) OR c`.
3.  Demonstrate that different boolean expressions for the same function result in the exact same BDD node pointer.

## 🎛 Experimental Controls
- **Unique Table Hits:** Measure how many redundant nodes we avoid creating.
- **Computed Table Cache Rate:** See how memoization speeds up complex boolean operations.
