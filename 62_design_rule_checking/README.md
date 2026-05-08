# Module 62: Design Rule Checking (DRC)

## 🎯 Goal
Implement efficient geometric checks to identify spacing violations between metal rectangles in a layout.

## 🧠 Key Concept
DRC ensures that a physical layout can be manufactured reliably. The most common rule is the **Minimum Spacing** rule, which requires a minimum distance between any two distinct polygons on the same metal layer to prevent short circuits.

## 📊 Metrics to Watch
- **Violation Count:** Number of identified spacing errors.
- **DB Scalability:** How checking time scales with the number of layout objects.
