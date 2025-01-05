#pragma once
#include <board/board.h>

class Analyzer {
public:
    static int32_t analyze(Board const& board);
private:
    static int32_t analyze(Board const& board, Color color);

    static int32_t materialCounter(Board const& board, Color color, Figure figure);
    static int32_t material(Board const& board, Color color);

    template <typename Func>
    static int32_t mobilityCounter(Board const& board, Color color, Figure figure, Func generator);
    static int32_t mobility(Board const& board, Color color);

    static int32_t doublePawn(Board const& board, Color color);
    static int32_t connectedPawn(Board const& board, Color color);
public:
    enum class Material {
        PAWN = 100,
        KNIGHT = 300,
        BISHOP = 325,
        ROOK = 550,
        QUEEN = 950,
        KING = 1600,
        ROOK_MOVED = 550,
        KING_MOVED = 1600,
    };
    enum class Mobility {
        KNIGHT = 9,
        BISHOP = 4,
        ROOK = 3,
        QUEEN = 3,
        ROOK_MOVED = 3,
    };
    enum class Costs {
        DOUBLE_PAWN = -25,
        CONNECTED_PAWN = 12,
    };
};
