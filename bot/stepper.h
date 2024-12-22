#pragma once
#include <board/board.h>

struct Step {
    Step();
    Step(Pos from, Pos to);
    Pos from, to;
};

struct StepInfo {
    StepInfo();
    StepInfo(int cost);
    StepInfo(Step best, int cost);
    Step best;
    int cost;
};

class Stepper {
public:
    Step run(Board const& board, int step) const;
private:
    char player(int step) const;
    StepInfo stepFirst(Board const& board, int step, int max_step, int alpha, int beta) const;
    StepInfo stepSecond(Board const& board, int step, int max_step, int alpha, int beta) const;
    std::vector<Step> genMoves(Board const& board, Color wb) const;
};
