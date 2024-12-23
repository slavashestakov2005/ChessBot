#include <board/move.h>

Move::Move() = default;

Move::Move(uint8_t cell_from, uint8_t cell_to, Color color_from, Figure figure_from, Color color_to, Figure figure_to, SpecialMove flag)
    : cell_from(cell_from), cell_to(cell_to), color_from(color_from), figure_from(figure_from), color_to(color_to), figure_to(figure_to), special(flag) {}
