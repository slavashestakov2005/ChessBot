#include <algorithm>
#include <bot/analyzer.h>
#include <bot/moves_sorted.h>
#include <figures/pseudo_moves.h>

Moves MovesSorter::sort(Board const& board, Moves moves) {
    std::sort(moves.begin(), moves.end(), [&board](Move const& l, Move const& r){
        return move_cost(board, l) > move_cost(board, r);
    });
    return moves;
}

int32_t MovesSorter::move_cost(Board const& board, Move const& move) {
    int32_t result = 0;
    if (move.special == SpecialMove::CASTLE) return 0;

    if (move.figure_from != Figure::PAWN) {
        BitBoard opponent_pawns = PseudoMoves::pawnLeft(board, inv(move.color_from), true) |
                                  PseudoMoves::pawnRight(board, inv(move.color_from), true);
        if (opponent_pawns.getBit(move.cell_to)) {
            switch (move.figure_from) {
                case Figure::KNIGHT: result -= (int32_t) Analyzer::Material::KNIGHT; break;
                case Figure::BISHOP: result -= (int32_t) Analyzer::Material::BISHOP; break;
                case Figure::ROOK: result -= (int32_t) Analyzer::Material::ROOK; break;
                case Figure::QUEEN: result -= (int32_t) Analyzer::Material::QUEEN; break;
                case Figure::KING: result -= (int32_t) Analyzer::Material::KING; break;
                case Figure::ROOK_MOVED: result -= (int32_t) Analyzer::Material::ROOK_MOVED; break;
                case Figure::KING_MOVED: result -= (int32_t) Analyzer::Material::KING_MOVED; break;
            }
        }
    }

    if (move.figure_to != Figure::NONE) {
        switch (move.figure_to) {
            case Figure::PAWN: result += 1000 * (int32_t) Analyzer::Material::PAWN; break;
            case Figure::KNIGHT: result += 1000 * (int32_t) Analyzer::Material::KNIGHT; break;
            case Figure::BISHOP: result += 1000 * (int32_t) Analyzer::Material::BISHOP; break;
            case Figure::ROOK: result += 1000 * (int32_t) Analyzer::Material::ROOK; break;
            case Figure::QUEEN: result += 1000 * (int32_t) Analyzer::Material::QUEEN; break;
            case Figure::KING: result += 1000 * (int32_t) Analyzer::Material::KING; break;
            case Figure::ROOK_MOVED: result += 1000 * (int32_t) Analyzer::Material::ROOK_MOVED; break;
            case Figure::KING_MOVED: result += 1000 * (int32_t) Analyzer::Material::KING_MOVED; break;
        }
        switch (move.figure_from) {
            case Figure::PAWN: result -= (int32_t) Analyzer::Material::PAWN; break;
            case Figure::KNIGHT: result -= (int32_t) Analyzer::Material::KNIGHT; break;
            case Figure::BISHOP: result -= (int32_t) Analyzer::Material::BISHOP; break;
            case Figure::ROOK: result -= (int32_t) Analyzer::Material::ROOK; break;
            case Figure::QUEEN: result -= (int32_t) Analyzer::Material::QUEEN; break;
            case Figure::KING: result -= (int32_t) Analyzer::Material::KING; break;
            case Figure::ROOK_MOVED: result -= (int32_t) Analyzer::Material::ROOK_MOVED; break;
            case Figure::KING_MOVED: result -= (int32_t) Analyzer::Material::KING_MOVED; break;
        }
    }
    return result;
}
