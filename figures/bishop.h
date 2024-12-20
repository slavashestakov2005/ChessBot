#pragma once
#include <figures/figure.h>

class Bishop : public Figure<Bishop> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
