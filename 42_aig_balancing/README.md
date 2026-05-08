# Module 42: AIG Balancing

## 🎯 Goal
Reduce the logic depth of an AIG using associative re-balancing.

## 🧠 Key Concept
The depth of an And-Inverter Graph (AIG) determines the number of levels of logic, which directly impacts the circuit's delay. Associative balancing uses the property $(A \& B) \& C = A \& (B \& C)$ to restructure chains into trees, reducing depth from $O(N)$ to $O(\log N)$.

## 📊 Metrics to Watch
- **Logic Depth:** The maximum number of nodes on any path from PI to PO.
- **Node Count:** Balancing should ideally not increase the total number of nodes.
