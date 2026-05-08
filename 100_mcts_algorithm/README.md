# Module 100: Monte Carlo Tree Search (MCTS)

## 🎯 Goal
Implement the MCTS algorithm for decision-making in deterministic games.

## 🧠 Key Concept
MCTS is a state-of-the-art algorithm for navigating massive search trees, famous for its success in AlphaGo. It uses four stages—Selection (using UCB1 for the exploration-exploitation tradeoff), Expansion, Simulation (rollout), and Backpropagation—to iteratively build a search tree toward the most promising game states.

## 📊 Metrics to Watch
- **Simulation Count:** Number of rollouts processed.
- **Node Growth:** Memory consumption as the search tree expands.
