# Module 53: Partitioning-based Placement

## 🎯 Goal
Use recursive min-cut partitioning to perform global placement of a netlist.

## 🧠 Key Concept
Min-cut placement works by recursively dividing the chip area and the netlist into two halves, minimizing the number of nets that cross the cut. This top-down approach ensures that highly connected modules are placed close together.

## 📊 Metrics to Watch
- **Placement Latency:** Time taken to recursively subdivide 10,000 nodes.
- **Node Distribution:** How evenly the nodes are spread across the chip.
