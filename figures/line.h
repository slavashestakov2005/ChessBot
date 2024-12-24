#pragma once
#include <board/bitboard.h>
#include <array>

namespace Moves {
    enum class LineDirection {
        EAST,
        NORTH_EAST,
        NORTH,
        NORTH_WEST,
        WEST,
        SOUTH_WEST,
        SOUTH,
        SOUTH_EAST,
    };

    consteval BitBoard evalOneLine(uint8_t cell, LineDirection dir);
    consteval std::array<std::array<BitBoard, 8>, 64> evalLines();
}

#include <figures/line.impl>

namespace Moves {
    constexpr std::array<std::array<BitBoard, 8>, 64> LINES = evalLines();
}
