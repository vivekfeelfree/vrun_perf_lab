# Module 98: Rabin-Karp String Matching

## 🎯 Goal
Use rolling hashes to efficiently find all occurrences of a pattern string in a large text.

## 🧠 Key Concept
The Rabin-Karp algorithm uses hashing to find any one of a set of pattern strings in a text. By using a rolling hash, it can update the hash of a sliding window in $O(1)$ time, leading to an average search time of $O(N+M)$. This is particularly useful for multiple pattern matching and plagiarism detection.

## 📊 Metrics to Watch
- **Match Count:** Total occurrences of the pattern found.
- **Hash Collisions:** Efficiency of the chosen base and modulus.
