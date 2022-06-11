#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

long calc_moves(long row_i, long col_i, std::vector<std::vector<long>>& board) {
    if (row_i == 0 && col_i == 0) {
        return 1;
    }
    if (row_i < 0 || row_i >= board.size() || col_i < 0 ||
        col_i >= board[0].size()) {
        return 0;
    }
    if (board[row_i][col_i] == -1) {
        board[row_i][col_i] = calc_moves(row_i - 1, col_i - 2, board) +
            calc_moves(row_i + 1, col_i - 2, board) +
            calc_moves(row_i - 2, col_i - 1, board) +
            calc_moves(row_i - 2, col_i + 1, board);
    }
    return board[row_i][col_i];
}

long calc_knight_moves(long n_rows, long m_cols) {
    std::vector<std::vector<long>> board(n_rows, std::vector<long>(m_cols, -1));
    board[0][0] = 1;

    return calc_moves(n_rows - 1, m_cols - 1, board);
}

int main() {
    std::ifstream in("knight2.in");
    std::ofstream out("knight2.out");

    long N, M;
    in >> N >> M;
    out << calc_knight_moves(N, M);

    return 0;
}
