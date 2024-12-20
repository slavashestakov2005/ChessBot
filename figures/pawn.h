#pragma once
#include <figures/figure.h>

class Pawn : public Figure<Pawn> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
