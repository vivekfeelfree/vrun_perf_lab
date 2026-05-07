# Module 21: And-Inverter Graphs (AIGs) & 2-Level Strashing

## The Core Problem: Scalability of Logic Representation
BDDs are excellent for equivalence checking but often "explode" in size for complex logic.
**AIGs** are non-canonical but highly scalable. They represent any boolean function using only two primitives:
1.  Two-input **AND** gates.
2.  **Inverters** (represented as a single bit on the edge).

## 1. Structural Hashing (Strashing)
To keep the AIG small, we use **Structural Hashing**:
- **1-Level:** Before creating `AND(a, b)`, check if it already exists.
- **2-Level:** Apply local algebraic rules like:
    - `AND(a, a) = a`
    - `AND(a, NOT(a)) = 0`
    - `AND(a, 0) = 0`
    - `AND(a, 1) = a`

## 2. Implementation: The Literal representation
Instead of storing pointers to "Inverter" nodes, we use the "Least Significant Bit" (LSB) of the pointer to represent the inversion.
- `Pointer | 0`: Direct signal.
- `Pointer | 1`: Inverted signal.
This is a classic "Systems" trick to save memory and improve cache locality.

## 3. The Experiment
In `main.cpp`, we will:
1.  Implement an AIG Manager using the **LSB-Inverter** trick.
2.  Build a logic circuit and apply 2-level strashing.
3.  Compare the number of nodes in a "naive" graph vs. a "strashed" graph.

## 🎛 Experimental Controls
- **Circuit Complexity:** Compare a simple adder vs. a random logic cloud.
- **Strashing Impact:** Measure the % reduction in node count as we enable different levels of optimization.
