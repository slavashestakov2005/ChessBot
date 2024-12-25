#include <bot/moves_sorted.h>
#include <bot/analuzer.h>
#include <algorithm>

Moves MovesSorter::sort(Board const& board, Moves moves) {
    std::sort(moves.begin(), moves.end(), [&board](Move const& l, Move const& r){
        return move_cost(board, l) > move_cost(board, r);
    });
    return moves;
}

int32_t MovesSorter::move_cost(Board const& board, Move const& move) {
    int32_t result = 0;
    // skip
    if (move.figure_to != Figure::NONE) {
        switch (move.figure_to) {
            case Figure::PAWN: result += 1000 * (int32_t) Analyzer::Material::PAWN; break;
            case Figure::KNIGHT: result += 1000 * (int32_t) Analyzer::Material::KNIGHT; break;
            case Figure::BISHOP: result += 1000 * (int32_t) Analyzer::Material::BISHOP; break;
            case Figure::ROOK: result += 1000 * (int32_t) Analyzer::Material::ROOK; break;
            case Figure::QUEEN: result += 1000 * (int32_t) Analyzer::Material::QUEEN; break;
            // case Figure::KING: result += 1000 * (int32_t) Analyzer::Material::KING; break;
        }
        switch (move.figure_from) {
            case Figure::PAWN: result -= (int32_t) Analyzer::Material::PAWN; break;
            case Figure::KNIGHT: result -= (int32_t) Analyzer::Material::KNIGHT; break;
            case Figure::BISHOP: result -= (int32_t) Analyzer::Material::BISHOP; break;
            case Figure::ROOK: result -= (int32_t) Analyzer::Material::ROOK; break;
            case Figure::QUEEN: result -= (int32_t) Analyzer::Material::QUEEN; break;
            // case Figure::KING: result -= Analyzer::Material::KING; break;
        }
    }
    return result;
}
