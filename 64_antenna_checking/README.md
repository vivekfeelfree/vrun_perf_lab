# Module 64: Antenna Effect Checking

## 🎯 Goal
Calculate metal-to-gate area ratios for nets to identify potential antenna violations.

## 🧠 Key Concept
During plasma etching, long metal wires can collect electric charge. If this charge has no discharge path (like a diffusion diode) and is connected to a thin gate oxide, the resulting high voltage can damage the oxide. This is the **Antenna Effect**. Rules typically limit the ratio of wire area to gate area.

## 📊 Metrics to Watch
- **Violation Count:** Number of nets exceeding the antenna ratio.
- **Traversal Throughput:** Speed of checking large netlists.
