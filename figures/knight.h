#pragma once
#include <array>
#include <board/bitboard.h>

namespace Moves {
    consteval std::array<BitBoard, 64> evalKnight();
}

#include <figures/knight.impl>

namespace Moves {
    constexpr std::array<BitBoard, 64> KNIGHT = evalKnight();
}
