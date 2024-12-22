#pragma once
#include <board/pos.h>
#include <cstdint>
#include <vector>

enum class FigureType : uint8_t {
    EMPTY,
    
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_ROOK_MOVED,
    WHITE_KING_MOVED,

    COLOR_SEP,
    
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_ROOK_MOVED,
    BLACK_KING_MOVED,
};

Color getColor(FigureType type);

char getChar(FigureType type);

int getMaterial(FigureType type);

int getMaterial(FigureType type, Pos pos);

class Board;

std::vector<Pos> getSteps(Board const& board, Pos pos);
