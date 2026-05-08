# Module 40: State Machine Minimization

## 🎯 Goal
Use Moore's algorithm to identify equivalent states in a Finite State Machine (FSM) and reduce the total state count.

## 🧠 Key Concept
Two states in an FSM are equivalent if they produce the same output and transition to equivalent states for every possible input. Moore's algorithm iteratively refines partitions of states until no further splits are possible.

## 📊 Metrics to Watch
- **State Count:** Reduction from initial to minimized FSM.
- **Iteration Count:** Number of refinement steps required.
