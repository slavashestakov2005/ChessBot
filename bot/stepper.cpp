#include <bot/stepper.h>
#include <bot/analyzer.h>
#include <random>
#include <iostream>

const int INF = 1e9;

Board applyMove(Board board, Step move) {
    FigureType old = board.getType(move.from.x, move.from.y);
    board.setType(move.from, FigureType::EMPTY);
    switch (old) {
        case FigureType::WHITE_KING: board.setType(move.to, FigureType::WHITE_KING_MOVED); break;
        case FigureType::BLACK_KING: board.setType(move.to, FigureType::BLACK_KING_MOVED); break;
        case FigureType::WHITE_ROOK: board.setType(move.to, FigureType::WHITE_ROOK_MOVED); break;
        case FigureType::BLACK_ROOK: board.setType(move.to, FigureType::BLACK_ROOK_MOVED); break;
        default: board.setType(move.to, old);
    }
    return board;
}

Step::Step() : from{-INF, -INF}, to{-INF, -INF} {
}

Step::Step(Pos from, Pos to) : from(from), to(to) {
}

StepInfo::StepInfo() : StepInfo(0) {
}

StepInfo::StepInfo(int cost) : cost(cost) {
}

StepInfo::StepInfo(Step best, int cost) : best(best), cost(cost) {
}

Step Stepper::run(Board const& board, int step) const {
    StepInfo info;
    if (step % 2 == 0) info = stepFirst(board, step, step + 6, -INF, INF);
    else info = stepSecond(board, step, step + 6, -INF, INF);
    return info.best;
}

char Stepper::player(int step) const {
    return (step % 2 == 0 ? '1' : '2');
}

StepInfo Stepper::stepFirst(Board const& board, int step, int max_step, int alpha, int beta) const {
    if (step == max_step) {
        int cost = 11 * Analyzer::analyzeMaterial(board) + 2 * Analyzer::analyzeMaterialPosition(board);
        return StepInfo(cost);
    }
    char next = player(step + 1);
    Step best;
    for (Step move : genMoves(board, Color::WHITE)) {
        StepInfo score;
        Board new_board = applyMove(board, move);
        if (next == '1') score = stepFirst(new_board, step + 1, max_step, alpha, beta);
        else score = stepSecond(new_board, step + 1, max_step, alpha, beta);
        if (score.cost >= beta) return StepInfo(beta);
        if (score.cost > alpha) alpha = score.cost, best = move;
    }
    return StepInfo(best, alpha);
}

StepInfo Stepper::stepSecond(Board const& board, int step, int max_step, int alpha, int beta) const {
    if (step == max_step) {
        int cost = 11 * Analyzer::analyzeMaterial(board) + 2 * Analyzer::analyzeMaterialPosition(board);
        return StepInfo(cost);
    }
    char next = player(step + 1);
    Step best;
    for (Step move : genMoves(board, Color::WHITE)) {
        StepInfo score;
        Board new_board = applyMove(board, move);
        if (next == '1') score = stepFirst(new_board, step + 1, max_step, alpha, beta);
        else score = stepSecond(new_board, step + 1, max_step, alpha, beta);
        if (score.cost <= alpha) return StepInfo(alpha);
        if (score.cost < beta) beta = score.cost, best = move;
   }
   return StepInfo(best, beta);
}

std::vector<Step> Stepper::genMoves(Board const& board, Color wb) const {
    std::vector<Step> moves;
    for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) {
        Pos from = {i, j};
        if (board.getColor(i, j) == wb) {
            for (Pos to : getSteps(board, from)) {
                moves.push_back(Step(from, to));
            }
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(moves.begin(), moves.end(), g);
    return moves;
}
