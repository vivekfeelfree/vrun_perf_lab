# Module 72: Parasitic RC Reduction

## 🎯 Goal
Simplify a detailed RC tree into a 3-element Pi-model that preserves the first two moments of the circuit response.

## 🧠 Key Concept
Interconnect extraction often produces massive RC networks that are too slow to simulate directly in timing analysis. Parasitic reduction techniques (like Pi-model matching or TICER) simplify these networks into compact representations that accurately model the delay and slew at the sinks while using far fewer elements.

## 📊 Metrics to Watch
- **Reduction Ratio:** Number of elements before vs. after reduction.
- **Accuracy:** How well the simplified model tracks the original delay.
