#include <board/hash.h>
#include <board/position.h>

Hash::Hash() : value(0) {}

Hash::Hash(Position const& pos) {
    value = 0;
    if (pos.currentPlayer() == Color::BLACK) inversePlayer();

    Board board = pos.getBoard();
    for (int cell = 0; cell < 64; ++cell) {
        Color color = Color::NONE;
        if (board.getColorBitBoard(Color::WHITE).getBit(cell)) color = Color::WHITE;
        else if (board.getColorBitBoard(Color::BLACK).getBit(cell)) color = Color::BLACK;
        else continue;
        for (Figure fig : FIGURES) {
            if (board.getFigureBitBoard(color, fig).getBit(cell)) inverse(cell, color, fig);
        }
    }
}

uint64_t Hash::getValue() const {
    return value;
}

void Hash::inversePlayer() {
    value ^= HashConstants::BLACK_STEP;
}

void Hash::inverse(uint8_t cell, Color color, Figure figure) {
    value ^= HashConstants::CONSTANTS[cell][(int) color][(int) figure];
}

bool operator==(Hash const& l, Hash const& r) {
    return l.getValue() == r.getValue();
}
