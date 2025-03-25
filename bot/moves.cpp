#include <stdexcept>
#include <bot/moves.h>

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

Moves::iterator Moves::begin() {
    return moves.begin();
}

Moves::iterator Moves::end() {
    return moves.begin() + len;
}
