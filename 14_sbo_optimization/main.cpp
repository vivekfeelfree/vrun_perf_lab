/**
 * EXPERIMENT: Small Buffer Optimization (SBO)
 * 
 * GOAL: Demonstrate how avoiding heap allocations for small data
 * significantly improves performance and memory locality.
 */

#include "../include/harness.hpp"
#include <vector>
#include <cstring>

/**
 * A string class that ALWAYS allocates on the heap.
 */
class NaiveString {
    char* data;
    size_t len;
public:
    NaiveString(const char* s) {
        len = std::strlen(s);
        data = new char[len + 1];
        std::memcpy(data, s, len + 1);
    }
    ~NaiveString() { delete[] data; }
    char operator[](size_t i) const { return data[i]; }
};

/**
 * A string class with Small Buffer Optimization (16 bytes).
 */
class SBOString {
    size_t len;
    union {
        char* heap_ptr;
        char local_buffer[16];
    };
    bool is_small;

public:
    SBOString(const char* s) {
        len = std::strlen(s);
        if (len < 16) {
            is_small = true;
            std::memcpy(local_buffer, s, len + 1);
        } else {
            is_small = false;
            heap_ptr = new char[len + 1];
            std::memcpy(heap_ptr, s, len + 1);
        }
    }

    ~SBOString() {
        if (!is_small) delete[] heap_ptr;
    }

    char operator[](size_t i) const {
        return is_small ? local_buffer[i] : heap_ptr[i];
    }
};

const int COUNT = 1'000'000;

int main() {
    std::cout << "--- SBO (Small Buffer Optimization) Laboratory ---" << std::endl;

    const char* small_text = "Hello SBO!"; // 10 chars
    const char* large_text = "This is a much longer string that will exceed the 16 byte limit!";

    // 1. Benchmarking Small Strings (Where SBO should shine)
    {
        lab::print_qor("Naive (Small)", sizeof(NaiveString) + 11);
        lab::Benchmark b("NaiveString (Small)");
        for(int i = 0; i < COUNT; ++i) {
            NaiveString s(small_text);
            lab::escape(&s);
        }
    }

    {
        lab::print_qor("SBO (Small)", sizeof(SBOString));
        lab::Benchmark b("SBOString (Small)");
        for(int i = 0; i < COUNT; ++i) {
            SBOString s(small_text);
            lab::escape(&s);
        }
    }

    // 2. Benchmarking Large Strings (Where SBO should match Naive)
    std::cout << "\nBenchmarking Large Strings (Exceeding Buffer):" << std::endl;
    {
        lab::print_qor("Naive (Large)", sizeof(NaiveString) + std::strlen(large_text) + 1);
        lab::Benchmark b("NaiveString (Large)");
        for(int i = 0; i < COUNT; ++i) {
            NaiveString s(large_text);
            lab::escape(&s);
        }
    }

    {
        lab::print_qor("SBO (Large)", sizeof(SBOString) + std::strlen(large_text) + 1);
        lab::Benchmark b("SBOString (Large)");
        for(int i = 0; i < COUNT; ++i) {
            SBOString s(large_text);
            lab::escape(&s);
        }
    }

    return 0;
}
