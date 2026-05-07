# Module 12: Custom Iterators & Idiomatic C++

## The Core Problem: The API Gap
We built an `IntrusiveList` that is fast and memory-efficient. But it's painful to use:
```cpp
for(auto* link = list.begin(); link != list.end(); link = link->next) {
    auto* obj = IntrusiveList::container_of<Process, &Process::link>(link);
    // ...
}
```
In C++, we want:
```cpp
for(auto& process : list) {
    // ...
}
```

## 1. The Iterator Pattern
A C++ iterator is a "Smart Pointer" that knows how to:
1.  **Advance:** `operator++`
2.  **Access:** `operator*` and `operator->`
3.  **Compare:** `operator!=`

## 2. Integrating the `container_of` Magic
The "Secret Sauce" of an intrusive iterator is that its `operator*` performs the `container_of` calculation automatically.

```cpp
T& operator*() {
    return *IntrusiveList::container_of<T, Member>(current_link);
}
```

## 3. The Experiment
In `main.cpp`, we will:
1.  Extend our `IntrusiveList` with a proper `Iterator` class.
2.  Demonstrate using the list with **Standard Algorithms** like `std::count_if` and `std::for_each`.
3.  Measure if there is any performance penalty for this abstraction (Spoiler: Zero cost, thanks to C++ inlining).

## 🎛 Experimental Controls
- **Abstraction Penalty:** Compare the raw loop speed (Module 03) against the idiomatic iterator loop.
- **Algorithm Composition:** See how easily we can pipe our intrusive list into modern C++ features.
