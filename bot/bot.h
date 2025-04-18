#pragma once
#include <board/position.h>
#include <bot/moves.h>

class Bot {
public:
    static Move getBestMove(const Position& position);
private:
    static std::tuple<int32_t, bool, Move> alphaBeta(const Position& position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent);
    static std::tuple<int32_t, bool, Move> alphaBetaMin(const Position &position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent);
    static std::tuple<int32_t, bool, Move> alphaBetaMax(const Position &position, int32_t alpha, int32_t beta, int32_t depthLeft, int32_t depthCurrent);

    static int32_t alphaBetaOnlyCaptures(const Position& position, int32_t alpha, int32_t beta);
    static int32_t alphaBetaMinOnlyCaptures(const Position& position, int32_t alpha, int32_t beta);
    static int32_t alphaBetaMaxOnlyCaptures(const Position& position, int32_t alpha, int32_t beta);
};
