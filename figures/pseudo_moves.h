#pragma once
#include <board/board.h>

namespace PseudoMoves {
    BitBoard movesPawns(Board const& board, Color color, bool only_attack=false);
    BitBoard movesKnight(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesBishop(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesRook(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesQueen(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesKing(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    
    bool inBitten(Board const& board, uint8_t cell, Color color);
}
