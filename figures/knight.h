#pragma once
#include <figures/figure.h>

class Knight : public Figure<Knight> {
public:
    static char latter;
    static std::vector<Pos> moves(Board const& board, Pos pos, Color color);
};
