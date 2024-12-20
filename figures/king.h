#pragma once
#include <figures/figure.h>

class King : public Figure<King> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
