#pragma once
#include <array>
#include <board/move.h>

class Moves {
public:
    static const uint8_t MAX = 220;
    Moves();
    Move operator[](uint8_t pos) const;
    Move& operator[](uint8_t pos);
    void push(Move move);
    uint8_t size() const;
private:
    std::array<Move, MAX> moves;
    uint8_t len;
    using iterator = std::array<Move, MAX>::iterator;
public:
    iterator begin();
    iterator end();
};
