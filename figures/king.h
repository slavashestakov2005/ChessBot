#pragma once
#include <board/bitboard.h>
#include <array>

namespace Moves {
    consteval std::array<BitBoard, 64> evalKing();
}

#include <figures/king.impl>

namespace Moves {
    constexpr std::array<BitBoard, 64> KING = evalKing();
}
