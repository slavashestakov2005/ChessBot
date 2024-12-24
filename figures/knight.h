#pragma once
#include <board/bitboard.h>
#include <array>

namespace Moves {
    consteval std::array<BitBoard, 64> evalKnight();
}

#include <figures/knight.impl>

namespace Moves {
    constexpr std::array<BitBoard, 64> KNIGHT = evalKnight();
}
