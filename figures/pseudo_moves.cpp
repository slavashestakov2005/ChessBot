#include <figures/pseudo_moves.h>
#include <figures/king.h>
#include <figures/knight.h>
#include <figures/line.h>

BitBoard moveLine(Board const& board, uint8_t cell, Color color, bool attack_only, Moves::LineDirection dir, bool first_block) {
    BitBoard blockers = Moves::LINES[cell][(int) dir] & board.getAnyBitBoard();
    if (blockers.getAll() == 0) {
        if (attack_only) return 0;
        return Moves::LINES[cell][(int) dir];
    }
    uint8_t block_pos;
    if (first_block) block_pos = blockers.getHigh1();
    else block_pos = blockers.getLow1();
    BitBoard moves;
    if (!attack_only) moves = Moves::LINES[cell][(int) dir] ^ Moves::LINES[block_pos][(int) dir];
    if (board.getColorBitBoard(color).getBit(block_pos)) moves = moves.set0(block_pos);
    else moves = moves.set1(block_pos);
    return moves;
}

BitBoard PseudoMoves::pawnDefault(Board const& board, Color color) {
    BitBoard pawns = board.getFigureBitBoard(color, Figure::PAWN);
    if (color == Color::WHITE) return (pawns << 8) & board.getNoneBitBoard();
    else return (pawns >> 8) & board.getNoneBitBoard();
}

BitBoard PseudoMoves::pawnLong(Board const& board, Color color) {
    BitBoard pawns = pawnDefault(board, color);
    if (color == Color::WHITE) return ((pawns & BitBoardConstants::ROWS[2]) << 8) & board.getNoneBitBoard();
    else return ((pawns & BitBoardConstants::ROWS[5]) >> 8) & board.getNoneBitBoard();
}

BitBoard PseudoMoves::pawnLeft(Board const& board, Color color, bool attack_empty) {
    BitBoard pawns = board.getFigureBitBoard(color, Figure::PAWN);
    if (color == Color::WHITE) {
        BitBoard mask = (pawns << 7) & BitBoardConstants::INV_COLS[7];
        if (!attack_empty) mask = mask & board.getColorBitBoard(Color::BLACK);
        return mask;
    } else {
        BitBoard mask = (pawns >> 9) & BitBoardConstants::INV_COLS[7];
        if (!attack_empty) mask = mask & board.getColorBitBoard(Color::WHITE);
        return mask;
    }
}

BitBoard PseudoMoves::pawnRight(Board const& board, Color color, bool attack_empty) {
    BitBoard pawns = board.getFigureBitBoard(color, Figure::PAWN);
    if (color == Color::WHITE) {
        BitBoard mask = (pawns << 9) & BitBoardConstants::INV_COLS[0];
        if (!attack_empty) mask = mask & board.getColorBitBoard(Color::BLACK);
        return mask;
    } else {
        BitBoard mask = (pawns >> 7) & BitBoardConstants::INV_COLS[0];
        if (!attack_empty) mask = mask & board.getColorBitBoard(Color::WHITE);
        return mask;
    }
}

BitBoard PseudoMoves::movesPawns(Board const& board, Color color, bool only_attack) {
    BitBoard pl = pawnLeft(board, color, false);
    BitBoard pr = pawnRight(board, color, false);
    if (only_attack) return pl | pr;
    BitBoard p1 = pawnDefault(board, color);
    BitBoard p2 = pawnLong(board, color);
    return pl | pr | p1 | p2;
}

BitBoard PseudoMoves::movesKnight(Board const& board, uint8_t cell, Color color, bool only_attack) {
    if (only_attack) return Moves::KNIGHT[cell] & board.getColorBitBoard(inv(color));
    return Moves::KNIGHT[cell] & board.getInvColorBitBoard(color);
}

BitBoard PseudoMoves::movesBishop(Board const& board, uint8_t cell, Color color, bool only_attack) {
    BitBoard ne = moveLine(board, cell, color, only_attack, Moves::LineDirection::NORTH_EAST, false);
    BitBoard nw = moveLine(board, cell, color, only_attack, Moves::LineDirection::NORTH_WEST, false);
    BitBoard sw = moveLine(board, cell, color, only_attack, Moves::LineDirection::SOUTH_WEST, true);
    BitBoard se = moveLine(board, cell, color, only_attack, Moves::LineDirection::SOUTH_EAST, true);
    return ne | nw | sw | se;
}

BitBoard PseudoMoves::movesRook(Board const& board, uint8_t cell, Color color, bool only_attack) {
    BitBoard e = moveLine(board, cell, color, only_attack, Moves::LineDirection::EAST, false);
    BitBoard n = moveLine(board, cell, color, only_attack, Moves::LineDirection::NORTH, false);
    BitBoard w = moveLine(board, cell, color, only_attack, Moves::LineDirection::WEST, true);
    BitBoard s = moveLine(board, cell, color, only_attack, Moves::LineDirection::SOUTH, true);
    return e | n | w | s;
}

BitBoard PseudoMoves::movesQueen(Board const& board, uint8_t cell, Color color, bool only_attack) {
    BitBoard bishop = movesBishop(board, cell, color, only_attack);
    BitBoard rook = movesRook(board, cell, color, only_attack);
    return bishop | rook;
}

BitBoard PseudoMoves::movesKing(Board const& board, uint8_t cell, Color color, bool only_attack) {
    if (only_attack) return Moves::KING[cell] & board.getColorBitBoard(inv(color));
    return Moves::KING[cell] & board.getInvColorBitBoard(color);
}

bool PseudoMoves::isBitten(Board const& board, uint8_t cell, Color color) {
    Color invc = inv(color);
    BitBoard pawns = pawnLeft(board, invc, true) | pawnRight(board, invc, true);
    if (pawns.getBit(cell)) return true;
    if (movesKnight(board, cell, color, true) & board.getFigureBitBoard(invc, Figure::KNIGHT)) return true;
    if (movesBishop(board, cell, color, true) & board.getFigureBitBoard(invc, Figure::BISHOP)) return true;
    if (movesRook(board, cell, color, true) & board.getFigureBitBoard(invc, Figure::ROOK)) return true;
    if (movesQueen(board, cell, color, true) & board.getFigureBitBoard(invc, Figure::QUEEN)) return true;
    if (movesKing(board, cell, color, true) & board.getFigureBitBoard(invc, Figure::KING)) return true;
    return false;
}
