#include <bot/analyzer.h>
#include <figures/pseudo_moves.h>

int32_t Analyzer::analyze(Board const& board) {
    int32_t result = 0;
    result += analyze(board, Color::WHITE);
    result -= analyze(board, Color::BLACK);
    return result;
}

int32_t Analyzer::analyze(Board const& board, Color color) {
    int32_t result = 0;
    result += material(board, color);
    result += mobility(board, color);
    result += doublePawn(board, color);
    result += connectedPawn(board, color);
    return result;
}

int32_t Analyzer::materialCounter(Board const& board, Color color, Figure figure) {
    return board.getFigureBitBoard(color, figure).ones();
}

int32_t Analyzer::material(Board const& board, Color color) {
    int32_t result = 0;
    result += (int32_t) Material::PAWN * materialCounter(board, color, Figure::PAWN);
    result += (int32_t) Material::KNIGHT * materialCounter(board, color, Figure::KNIGHT);
    result += (int32_t) Material::BISHOP * materialCounter(board, color, Figure::BISHOP);
    result += (int32_t) Material::ROOK * materialCounter(board, color, Figure::ROOK);
    result += (int32_t) Material::QUEEN * materialCounter(board, color, Figure::QUEEN);
    result += (int32_t) Material::KING * materialCounter(board, color, Figure::KING);
    result += (int32_t) Material::ROOK_MOVED * materialCounter(board, color, Figure::ROOK_MOVED);
    result += (int32_t) Material::KING_MOVED * materialCounter(board, color, Figure::KING_MOVED);
    return result;
}

template <typename Func>
int32_t Analyzer::mobilityCounter(Board const& board, Color color, Figure figure, Func generator) {
    BitBoard allFigs = board.getFigureBitBoard(color, figure);
    int steps = 0;
    while (allFigs) {
        uint8_t cell = allFigs.getHigh1();
        allFigs = allFigs.set0(cell);
        steps += generator(board, cell, color, false).ones();
    }
    return steps;
}

int32_t Analyzer::mobility(Board const& board, Color color) {
    int32_t result = 0;
    result += (int32_t) Mobility::KNIGHT * mobilityCounter(board, color, Figure::KNIGHT, PseudoMoves::movesKnight);
    result += (int32_t) Mobility::BISHOP * mobilityCounter(board, color, Figure::BISHOP, PseudoMoves::movesBishop);
    result += (int32_t) Mobility::ROOK * mobilityCounter(board, color, Figure::ROOK, PseudoMoves::movesRook);
    result += (int32_t) Mobility::QUEEN * mobilityCounter(board, color, Figure::QUEEN, PseudoMoves::movesRook);
    result += (int32_t) Mobility::ROOK_MOVED * mobilityCounter(board, color, Figure::ROOK_MOVED, PseudoMoves::movesRook);
    return result;
}

int32_t Analyzer::doublePawn(Board const& board, Color color) {
    int8_t cnt = 0;
    BitBoard pawns = board.getFigureBitBoard(color, Figure::PAWN);
    for (int x = 0; x < 8; ++x) {
        int8_t line = (pawns & BitBoardConstants::COLS[x]).ones();
        cnt += std::max(line - 1, 0);
    }
    return (int32_t) Costs::DOUBLE_PAWN * cnt;
}

int32_t Analyzer::connectedPawn(Board const& board, Color color) {
    BitBoard pawns = board.getFigureBitBoard(color, Figure::PAWN);
    BitBoard attack = PseudoMoves::pawnLeft(board, color, true) | PseudoMoves::pawnRight(board, color, true);
    int8_t cnt = (pawns & attack).ones();
    return (int32_t) Costs::CONNECTED_PAWN * cnt;
}
