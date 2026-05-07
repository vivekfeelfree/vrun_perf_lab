# Module 08: Radix Trees (Tries) & Prefix Matching

## The Core Problem: Hierarchical Keys
Hash maps are great for exact matches, but they fail at hierarchical queries:
1.  **Prefix Search:** "Find all keys starting with `sys.cpu.`"
2.  **Longest Prefix Match:** "Which IP range does `10.0.5.2` belong to?"
3.  **Sorted Iteration:** "List all keys in alphabetical order."

## 1. The Trie (Prefix Tree)
A Trie stores keys bit-by-bit (or byte-by-byte). Each node represents a common prefix shared by multiple keys.
- **Space Efficiency:** Common prefixes are stored only once.
- **Deterministic Performance:** Lookups depend on the *length* of the key, not the number of keys in the tree.

## 2. The Radix Tree (Compressed Trie)
A "naive" trie is very deep and wastes memory on nodes with only one child. A **Radix Tree** compresses these paths:
- If a node has only one child, it is merged with that child.
- This significantly reduces tree depth and improves cache locality.

## 3. The Experiment
In `main.cpp`, we will compare:
1.  **`std::set<string>`:** The baseline (Red-Black Tree).
2.  **`lab::RadixTree`:** Our custom prefix-compressed tree.

## 🎛 Experimental Controls
- **Key Density:** How does the tree perform when keys share long common prefixes (e.g., file paths) vs when they are completely random?
- **Lookup Depth:** Measure how lookup time scales with key length.
