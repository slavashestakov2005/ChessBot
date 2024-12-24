#pragma once
#include <board/board.h>

namespace PseudoMoves {
    BitBoard pawnDefault(Board const& board, Color color);
    BitBoard pawnLong(Board const& board, Color color);
    BitBoard pawnLeft(Board const& board, Color color, bool attack_empty);
    BitBoard pawnRight(Board const& board, Color color, bool attack_empty);

    BitBoard movesPawns(Board const& board, Color color, bool only_attack=false);
    BitBoard movesKnight(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesBishop(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesRook(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesQueen(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    BitBoard movesKing(Board const& board, uint8_t cell, Color color, bool only_attack=false);
    
    bool isBitten(Board const& board, uint8_t cell, Color color);
}
