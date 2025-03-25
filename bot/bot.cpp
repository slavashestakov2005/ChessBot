#include <bot/analyzer.h>
#include <bot/bot.h>
#include <bot/legal_moves.h>
#include <bot/moves_sorted.h>
#include <bot/visited_states.h>
#include <figures/pseudo_moves.h>

const int32_t INF = 1e9;
const int DEPTH = 6;

Move Bot::getBestMove(const Position& position) {
    auto [eval, gameWasFinished, move] = alphaBeta(position, -INF - 2 * DEPTH, INF + 2 * DEPTH, DEPTH, 0);
    return move;
}

std::tuple<int32_t, bool, Move> Bot::alphaBeta(const Position& position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent) {
    if (position.currentPlayer() == Color::WHITE) {
        return alphaBetaMax(position, alpha, beta, depthLeft, depthCurrent);
    }
    return alphaBetaMin(position, alpha, beta, depthLeft, depthCurrent);
}

std::tuple<int32_t, bool, Move> Bot::alphaBetaMin(const Position &position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent) {
    if (position.isWhiteWon()) return {INF + depthLeft, true, Move()};
    if (position.isBlackWon()) return {-INF - depthLeft, true, Move()};
    if (depthLeft == 0) {
        return {alphaBetaMinOnlyCaptures(position, alpha, beta), false, Move()};
    }
    Moves moves = LegalMoves::generate(position, Color::BLACK);
    if (moves.size() == 0) return {0, true, Move()};
    moves = MovesSorter::sort(position.getBoard(), moves);
    Move bestMove;
    uint8_t bestMoveIndex;
    bool gameWasFinishedOnBestMove;
    uint8_t tableResult = VisitedStates::getBestMove(position.getHash());
    if (tableResult < moves.size()) {
        std::swap(moves[0], moves[tableResult]);
    }
    for (uint8_t i = 0; i < moves.size(); ++i) {
        Move move = moves[i];
        Position copy = position;
        copy.move(move);
        auto [evaluation, gameWasFinished, next_move] = alphaBeta(copy, alpha, beta, depthLeft - 1, depthCurrent + 1);
        if (evaluation <= alpha) {
            VisitedStates::addState(position.getHash(), depthCurrent, bestMoveIndex);
            return {alpha, gameWasFinishedOnBestMove, bestMove};
        }
        if (evaluation < beta) {
            bestMove = move;
            bestMoveIndex = i;
            gameWasFinishedOnBestMove = gameWasFinished;
            beta = evaluation;
        }
    }
    VisitedStates::addState(position.getHash(), depthCurrent, bestMoveIndex);
    return {beta, gameWasFinishedOnBestMove, bestMove};
}

std::tuple<int32_t, bool, Move> Bot::alphaBetaMax(const Position &position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent) {
    if (position.isWhiteWon()) return {INF + depthLeft, true, Move()};
    if (position.isBlackWon()) return {-INF - depthLeft, true, Move()};
    if (depthLeft == 0) {
        return {alphaBetaMaxOnlyCaptures(position, alpha, beta), false, Move()};
    }
    Moves moves = LegalMoves::generate(position, Color::WHITE);
    if (moves.size() == 0) return {0, true, Move()};
    moves = MovesSorter::sort(position.getBoard(), moves);
    Move bestMove;
    uint8_t bestMoveIndex;
    bool gameWasFinishedOnBestMove;
    uint8_t tableResult = VisitedStates::getBestMove(position.getHash());
    if (tableResult < moves.size()) {
        std::swap(moves[0], moves[tableResult]);
    }
    for (uint8_t i = 0; i < moves.size(); ++i) {
        Move move = moves[i];
        Position copy = position;
        copy.move(move);
        auto [evaluation, gameWasFinished, next_move] = alphaBeta(copy, alpha, beta, depthLeft - 1, depthCurrent + 1);
        if (evaluation >= beta) {
            VisitedStates::addState(position.getHash(), depthCurrent, bestMoveIndex);
            return {beta, gameWasFinishedOnBestMove, bestMove};
        }
        if (evaluation > alpha) {
            bestMove = move;
            bestMoveIndex = i;
            gameWasFinishedOnBestMove = gameWasFinished;
            alpha = evaluation;
        }
    }
    VisitedStates::addState(position.getHash(), depthCurrent, bestMoveIndex);
    return {alpha, gameWasFinishedOnBestMove, bestMove};
}

int32_t Bot::alphaBetaOnlyCaptures(const Position& position, int32_t alpha, int32_t beta) {
    if (position.currentPlayer() == Color::WHITE) {
        return alphaBetaMaxOnlyCaptures(position, alpha, beta);
    }
    return alphaBetaMinOnlyCaptures(position, alpha, beta);
}

int32_t Bot::alphaBetaMinOnlyCaptures(const Position& position, int32_t alpha, int32_t beta) {
    int32_t evaluation = Analyzer::analyze(position.getBoard());
    if (evaluation <= alpha) {
        return alpha;
    }
    if (evaluation < beta) {
        beta = evaluation;
    }
    Moves moves = LegalMoves::generate(position, Color::BLACK, true);
    moves = MovesSorter::sort(position.getBoard(), moves);
    for (Move move : moves) {
        Position copy = position;
        copy.move(move);
        evaluation = alphaBetaOnlyCaptures(copy, alpha, beta);
        if (evaluation <= alpha) {
            return alpha;
        }
        if (evaluation < beta) {
            beta = evaluation;
        }
    }
    return beta;
}

int32_t Bot::alphaBetaMaxOnlyCaptures(const Position& position, int32_t alpha, int32_t beta) {
    int32_t evaluation = Analyzer::analyze(position.getBoard());
    if (evaluation >= beta) {
        return beta;
    }
    if (evaluation > alpha) {
        alpha = evaluation;
    }
    Moves moves = LegalMoves::generate(position, Color::WHITE, true);
    moves = MovesSorter::sort(position.getBoard(), moves);
    for (Move move : moves) {
        Position copy = position;
        copy.move(move);
        evaluation = alphaBetaOnlyCaptures(copy, alpha, beta);
        if (evaluation >= beta) {
            return beta;
        }
        if (evaluation > alpha) {
            alpha = evaluation;
        }
    }
    return alpha;
}
