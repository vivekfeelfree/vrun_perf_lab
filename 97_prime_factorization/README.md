# Module 97: Prime Factorization (Trial Division)

## 🎯 Goal
Use trial division to find the prime factors of a large integer.

## 🧠 Key Concept
Prime factorization is the decomposition of a composite number into a product of prime numbers. While factorization of extremely large numbers is the basis of RSA cryptography and is considered computationally difficult, trial division is a reliable and straightforward method for smaller (up to 64-bit) integers, running in $O(\sqrt{N})$.

## 📊 Metrics to Watch
- **Factor Count:** Number of prime factors identified.
- **Trial Latency:** Time taken to exhaust the search space up to $\sqrt{N}$.
