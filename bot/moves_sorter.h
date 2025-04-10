#pragma once
#include <board/board.h>
#include <bot/moves.h>

class MovesSorter {
public:
    static Moves sort(Board const& board, Moves moves);
private:
    static int32_t move_cost(Board const& board, Move const& move);
};
