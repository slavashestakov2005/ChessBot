#pragma once
#include <board/board.h>
#include <board/pos.h>
#include <vector>

template <typename Name>
class Figure {
public:
    static char print(Color color) {
        if (color == Color::WHITE) return Name::latter;
        else return Name::latter - 'a' + 'A';
    }

    static std::vector<Pos> step(Board const& board, Pos pos, Color color) {
        return Name::moves(board, pos, color);
    };
};
