#pragma once
#include <board/pos.h>
#include <cstdint>

enum class FigureType : uint8_t {
    EMPTY = 0,
    WHITE_PAWN = 10,
    COLOR_SEP = 20,
    BLACK_PAWN = 30,
};

class Board {
public:
    Board();
    Color getColor(int x, int y) const;
private:
    FigureType board[8][8];
};
