#pragma once
#include <board/board.h>
#include <board/pos.h>
#include <vector>

class BaseFigure {
public:
    virtual constexpr char print(Color color) const = 0;
    virtual constexpr int material(Color color) const = 0;
    virtual constexpr int materialPlace(Pos pos, Color color) const = 0;
    virtual std::vector<Pos> step(Board const& board, Pos pos, Color color) const = 0;
};

template <typename Name>
class Figure : public BaseFigure {
public:
    constexpr static Name instance = {};

    constexpr char print(Color color) const override {
        if (color == Color::WHITE) return Name::latter;
        else return Name::latter - 'a' + 'A';
    }

    constexpr int material(Color color) const override {
        if (color == Color::WHITE) return Name::cost;
        if (color == Color::BLACK) return -Name::cost;
        return 0;
    }

    constexpr int materialPlace(Pos pos, Color color) const override {
        if (color == Color::WHITE) return Name::cost_table[7 - pos.y][pos.x];
        if (color == Color::BLACK) return -Name::cost_table[pos.y][7 - pos.x];
        return 0;
    }

    std::vector<Pos> step(Board const& board, Pos pos, Color color) const override {
        return Name::moves(board, pos, color);
    };
};
