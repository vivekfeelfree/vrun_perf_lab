/**
 * EXPERIMENT: Cache-Oblivious Matrix Transpose
 * 
 * GOAL: Compare the naive nested loop transpose against a 
 * recursive divide-and-conquer strategy that optimizes 
 * for the cache hierarchy automatically.
 */

#include "../include/harness.hpp"
#include <vector>

const int N = 2048; // A 2048x2048 matrix is ~16MB (Exceeds L1/L2)

void transpose_naive(const float* A, float* B) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            B[j * N + i] = A[i * N + j];
        }
    }
}

// Threshold where recursion stops and we use a simple loop
const int THRESHOLD = 32;

void transpose_recursive(const float* A, float* B, 
                         int row_start, int col_start, 
                         int r_size, int c_size) {
    if (r_size <= THRESHOLD && c_size <= THRESHOLD) {
        for (int i = row_start; i < row_start + r_size; ++i) {
            for (int j = col_start; j < col_start + c_size; ++j) {
                B[j * N + i] = A[i * N + j];
            }
        }
        return;
    }

    if (r_size >= c_size) {
        // Split rows
        int half = r_size / 2;
        transpose_recursive(A, B, row_start, col_start, half, c_size);
        transpose_recursive(A, B, row_start + half, col_start, r_size - half, c_size);
    } else {
        // Split columns
        int half = c_size / 2;
        transpose_recursive(A, B, row_start, col_start, r_size, half);
        transpose_recursive(A, B, row_start, col_start + half, r_size, c_size - half);
    }
}

int main() {
    std::cout << "--- Cache-Oblivious Laboratory (" << N << "x" << N << " matrix) ---" << std::endl;

    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 0.0f);

    {
        lab::Benchmark b("Naive Transpose (Nested Loops)");
        transpose_naive(A.data(), B.data());
        lab::escape(B.data());
    }

    {
        lab::Benchmark b("Recursive Transpose (Cache-Oblivious)");
        transpose_recursive(A.data(), B.data(), 0, 0, N, N);
        lab::escape(B.data());
    }

    return 0;
}
