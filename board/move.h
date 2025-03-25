#pragma once
#include <cstdint>
#include <board/figures.h>

enum class SpecialMove {
    NONE,
    EN_PASSANT,
    CASTLE,
    PAWN_LONG,

    PAWN_KNIGHT,
    PAWN_BISHOP,
    PAWN_ROOK,
    PAWN_QUEEN,
    PAWN_KING,
};

struct Move {
public:
    Move();
    Move(uint8_t cell_from, uint8_t cell_to, Color color_from, Figure figure_from, Color color_to, Figure figure_to, SpecialMove flag = SpecialMove::NONE);
    uint8_t cell_from, cell_to;
    Color color_from, color_to;
    Figure figure_from, figure_to;
    SpecialMove special;
};
