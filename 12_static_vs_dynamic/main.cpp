/**
 * EXPERIMENT: Static vs. Dynamic Dispatch
 * 
 * GOAL: Measure the overhead of virtual functions and indirect
 * jumps compared to compile-time template dispatch.
 */

#include "../include/harness.hpp"
#include <vector>

// --- Dynamic Approach (VTable) ---

class BaseTask {
public:
    virtual ~BaseTask() = default;
    virtual int execute(int input) = 0;
};

class AddTask : public BaseTask {
public:
    int execute(int input) override { return input + 1; }
};

class MulTask : public BaseTask {
public:
    int execute(int input) override { return input * 2; }
};

// --- Static Approach (Templates) ---

struct StaticAddTask {
    inline int execute(int input) { return input + 1; }
};

struct StaticMulTask {
    inline int execute(int input) { return input * 2; }
};

template <typename T>
void run_static_bench(const char* name, T& task, int iterations) {
    int val = 0;
    lab::Benchmark b(name);
    for(int i = 0; i < iterations; ++i) {
        val = task.execute(val);
    }
    lab::escape(&val);
}

const int ITERATIONS = 100'000'000;

int main() {
    std::cout << "--- Static vs. Dynamic Dispatch (" << ITERATIONS << " calls) ---" << std::endl;

    // 1. Dynamic Dispatch (Virtual Calls)
    {
        AddTask add;
        MulTask mul;
        BaseTask* tasks[2] = {&add, &mul};
        
        lab::print_qor("Dynamic Dispatch", sizeof(AddTask) + sizeof(MulTask) + sizeof(tasks));
        int val = 0;
        lab::Benchmark b("Dynamic Dispatch (Virtual)");
        for(int i = 0; i < ITERATIONS; ++i) {
            // The compiler CANNOT inline this because it's a virtual call
            // via a pointer.
            val = tasks[i % 2]->execute(val);
        }
        lab::escape(&val);
    }

    // 2. Static Dispatch (Inlined Templates)
    {
        StaticAddTask add;
        StaticMulTask mul;
        
        int val = 0;
        lab::Benchmark b("Static Dispatch (Inlined)");
        for(int i = 0; i < ITERATIONS; ++i) {
            // The compiler CAN inline these perfectly.
            if (i % 2 == 0) val = add.execute(val);
            else val = mul.execute(val);
        }
        lab::escape(&val);
    }

    return 0;
}
