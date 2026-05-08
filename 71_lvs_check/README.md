# Module 71: Layout vs. Schematic (LVS)

## 🎯 Goal
Compare two circuit graphs (Golden Schematic vs. Extracted Layout) using vertex signatures to identify topological mismatches.

## 🧠 Key Concept
LVS is a critical sign-off step that ensures the physical layout correctly implements the original schematic design. Modern LVS tools use graph isomorphism algorithms and vertex "signatures" (based on device type, pin count, and neighbor connectivity) to efficiently find mismatches in nets or device properties.

## 📊 Metrics to Watch
- **Matching Accuracy:** Success in identifying deliberate mismatches.
- **Traversal Speed:** Time to compute and compare netlist signatures.
