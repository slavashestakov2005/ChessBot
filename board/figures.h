#pragma once
#include <array>

enum class Figure {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    ROOK_MOVED,
    KING_MOVED,
    NONE,
};

enum class Color {
    WHITE,
    BLACK,
    NONE,
};

Color inv(Color color);

constexpr std::array<Figure, 8> FIGURES = {Figure::PAWN, Figure::KNIGHT, Figure::BISHOP, Figure::ROOK,
                                           Figure::QUEEN, Figure::KING, Figure::ROOK_MOVED, Figure::KING_MOVED};
constexpr std::array<Color, 3> COLORS = {Color::WHITE, Color::BLACK, Color::NONE};
