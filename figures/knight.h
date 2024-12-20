#pragma once
#include <figures/figure.h>

class Knight : public Figure<Knight> {
public:
    static char latter;
    static int cost;
    static int cost_table[8][8];

    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
