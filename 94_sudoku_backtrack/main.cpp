/**
 * EXPERIMENT: Sudoku Solver (Backtracking)
 * 
 * GOAL: Solve a 9x9 Sudoku puzzle using recursive backtracking 
 * with constraint propagation.
 */

#include "../include/harness.hpp"
#include <vector>

class SudokuSolver {
public:
    bool is_safe(int board[9][9], int row, int col, int num) {
        for (int x = 0; x < 9; ++x) if (board[row][x] == num) return false;
        for (int x = 0; x < 9; ++x) if (board[x][col] == num) return false;
        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i + startRow][j + startCol] == num) return false;
        return true;
    }

    bool solve(int board[9][9]) {
        int row, col;
        bool empty = false;
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++col) {
                if (board[row][col] == 0) {
                    empty = true;
                    break;
                }
            }
            if (empty) break;
        }

        if (!empty) return true;

        for (int num = 1; num <= 9; ++num) {
            if (is_safe(board, row, col, num)) {
                board[row][col] = num;
                if (solve(board)) return true;
                board[row][col] = 0;
            }
        }
        return false;
    }
};

int main() {
    std::cout << "--- Sudoku Backtracking Laboratory ---" << std::endl;

    int board[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    SudokuSolver solver;
    bool success = false;
    {
        lab::Benchmark b("Sudoku Backtracking Search");
        success = solver.solve(board);
    }

    std::cout << "[METRICS] Solved Successfully: " << (success ? "YES" : "NO") << std::endl;
    lab::print_qor("Search State", sizeof(board));

    return 0;
}
