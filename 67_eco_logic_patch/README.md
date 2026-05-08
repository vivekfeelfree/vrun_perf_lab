# Module 67: ECO Logic Patch

## 🎯 Goal
Apply a logic change to a fixed layout by locating and utilizing nearby "spare cells" to minimize routing disruption.

## 🧠 Key Concept
Engineering Change Orders (ECOs) are modifications made late in the design cycle. To avoid a full re-run of placement and routing, designers often include "spare cells" (redundant gates) throughout the layout. A logic patch is implemented by mapping the new logic onto these existing spare cells and performing incremental routing.

## 📊 Metrics to Watch
- **Patch Distance:** Proximity of spare cells to the target modification point.
- **Utilization Rate:** Percentage of available spare cells used.
