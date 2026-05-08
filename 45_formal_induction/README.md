# Module 45: Formal Verification (k-Induction)

## 🎯 Goal
Prove that a hardware property holds for all time steps using base case and inductive step verification.

## 🧠 Key Concept
k-Induction is a technique for formal verification:
1.  **Base Case:** Prove the property holds for the first $k$ steps.
2.  **Inductive Step:** Prove that if the property holds for $k$ steps, it must hold for the $(k+1)$-th step.
If both are proven, the property is invariant for all time.

## 📊 Metrics to Watch
- **Proof Success:** Whether the property was formally proven.
- **Solver Effort:** Number of states explored during induction.
