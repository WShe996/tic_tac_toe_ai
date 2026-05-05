#include "game_board.h"
#include <iostream>
#include <stdexcept>

bool GameBoard::is_game_over() const {
    int last = x_turn_ ? -1 : 1;
    if (board_[0][0]+board_[1][1]+board_[2][2] == last*3) return true;
    if (board_[2][0]+board_[1][1]+board_[0][2] == last*3) return true;
    for (int i = 0; i < kSize; ++i) {
        if (board_[i][0]+board_[i][1]+board_[i][2] == last*3) return true;
        if (board_[0][i]+board_[1][i]+board_[2][i] == last*3) return true;
    }
    for (int i = 0; i < kSize; ++i)
        for (int j = 0; j < kSize; ++j)
            if (board_[i][j] == 0) return false;
    return true;
}

int GameBoard::score() const {
    if (!is_game_over()) throw std::invalid_argument("Game is not over");
    for (int i = 0; i < kSize; ++i) {
        int r = board_[i][0]+board_[i][1]+board_[i][2];
        int c = board_[0][i]+board_[1][i]+board_[2][i];
        if (r*r == 9) return r/3;
        if (c*c == 9) return c/3;
    }
    int d1 = board_[0][0]+board_[1][1]+board_[2][2];
    int d2 = board_[0][2]+board_[1][1]+board_[2][0];
    if (d1*d1 == 9) return d1/3;
    if (d2*d2 == 9) return d2/3;
    return 0;
}

bool GameBoard::try_move(int row, int col) {
    if (row < 0 || row >= kSize || col < 0 || col >= kSize) return false;
    if (board_[row][col] != 0) return false;
    board_[row][col] = x_turn_ ? 1 : -1;
    x_turn_ = !x_turn_;
    return true;
}

void GameBoard::print() const {
    for (int i = 0; i < kSize; ++i) {
        for (int j = 0; j < kSize; ++j) {
            char c = ' ';
            if (board_[i][j] == 1) c = 'X';
            if (board_[i][j] == -1) c = 'O';
            std::cout << c;
        }
        std::cout << "\n";
    }
}

std::vector<int> GameBoard::to_vector() const {
    std::vector<int> flat;
    flat.reserve(kSize * kSize);
    for (int i = 0; i < kSize; ++i)
        for (int j = 0; j < kSize; ++j)
            flat.push_back(board_[i][j]);
    return flat;
}
