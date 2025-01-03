#pragma once
#include <board/board.h>

class Analyzer {
public:
    static int32_t analyze(Board const& board);
private:
    static int32_t material(Board const& board);
    static int32_t mobility(Board const& board);
public:
    enum class Material {
        PAWN = 100,
        KNIGHT = 300,
        BISHOP = 325,
        ROOK = 550,
        QUEEN = 950,
        ROOK_MOVED = 550,
    };
};
