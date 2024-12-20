#pragma once
#include <figures/figure.h>

class Rook : public Figure<Rook> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
