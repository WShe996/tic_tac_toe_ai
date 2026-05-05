#pragma once

#include <array>
#include <vector>

class GameBoard {
public:
    GameBoard() = default;

    bool is_game_over() const;
    int  score() const;
    bool try_move(int row, int col);
    void print() const;
    std::vector<int> to_vector() const;

private:
    static constexpr int kSize = 3;
    std::array<std::array<int, kSize>, kSize> board_{};
    bool x_turn_ = true;
};
