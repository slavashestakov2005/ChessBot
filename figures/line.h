#pragma once
#include <array>
#include <board/bitboard.h>

namespace MovesConstants {
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
    consteval BitBoard evalOneSegment(uint8_t from, uint8_t to);
    consteval std::array<std::array<BitBoard, 64>, 64> evalSegments();
}

#include <figures/line.impl>

namespace MovesConstants {
    constexpr std::array<std::array<BitBoard, 8>, 64> LINES = evalLines();
    constexpr std::array<std::array<BitBoard, 64>, 64> SEGMENTS = evalSegments();
}
