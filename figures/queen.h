#pragma once
#include <figures/figure.h>

class Queen : public Figure<Queen> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
