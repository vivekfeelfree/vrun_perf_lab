# Module 93: Job Scheduling (EDF)

## 🎯 Goal
Implement the Earliest Deadline First (EDF) scheduling heuristic to maximize task completion.

## 🧠 Key Concept
Job scheduling on a single processor to minimize missed deadlines is a fundamental problem in real-time systems and resource management. The EDF heuristic is an optimal dynamic priority algorithm that prioritizes tasks based on their absolute deadlines, ensuring that if a feasible schedule exists, EDF will find it.

## 📊 Metrics to Watch
- **Completion Count:** Number of tasks finished before their deadlines.
- **Sorting Overhead:** Impact of deadline sorting on scheduler performance.
