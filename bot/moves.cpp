#include <bot/moves.h>
#include <stdexcept>

Moves::Moves() : len(0) {}

Move Moves::operator[](uint8_t pos) const {
    return moves[pos];    
}

Move& Moves::operator[](uint8_t pos) {
    return moves[pos];
}

void Moves::push(Move move) {
    if (len == MAX) throw std::invalid_argument("Position with > Moves::MAX variants");
    moves[len] = move;
    ++len;
}

uint8_t Moves::size() const {
    return len;
}
