#pragma once
#include <board/figure_type.h>
#include <board/pos.h>

class Board {
public:
    Board();
    void defaultPlacement();
    Color getColor(int x, int y) const;
    FigureType getType(int x, int y) const;
    void print() const;
private:
    FigureType board[8][8];
};
