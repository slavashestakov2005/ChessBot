#pragma once
#include <board/hash.h>
#include <unordered_map>

class VisitedStates {
public:
    static uint8_t NONE;
    static void addState(Hash hash, int32_t depth, uint8_t bestMove);
    static uint8_t getBestMove(Hash hash);
private:
    static std::unordered_map<uint64_t, std::pair<int32_t, int8_t>> data;
};
