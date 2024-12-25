#include <bot/visited_states.h>

uint8_t VisitedStates::NONE = 255;
std::unordered_map<uint64_t, std::pair<int32_t, int8_t>> VisitedStates::data = {};

void VisitedStates::addState(Hash hash, int32_t depth, uint8_t bestMove) {
    auto it = data.find(hash.getValue());
    if (it == data.end()) {
        data[hash.getValue()] = {depth, bestMove};
    } else if (it->second.first < depth) {
        data.erase(it);
        data[hash.getValue()] = {depth, bestMove};
    }
}

uint8_t VisitedStates::getBestMove(Hash hash) {
    auto it = data.find(hash.getValue());
    if (it == data.end()) {
        return NONE;
    }
    return it->second.second;
}
