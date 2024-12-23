#include <board/hash.h>

Hash::Hash() : value(0) {}

Hash::Hash(Position const& pos) {
    value = 0;
    if (pos.currentPlayer() == Color::BLACK) value ^= HashConstants::BLACK_STEP;

    Board board = pos.getBoard();
    for (int cell = 0; cell < 64; ++cell) {
        Color color;
        if (board.getColorBitBoard(Color::WHITE).getBit(cell)) color = Color::WHITE;
        else if (board.getColorBitBoard(Color::BLACK).getBit(cell)) color = Color::BLACK;
        else continue;
        if (board.getFigureBitBoard(color, Figure::PAWN).getBit(cell)) inverse(cell, color, Figure::PAWN);
        else if (board.getFigureBitBoard(color, Figure::KNIGHT).getBit(cell)) inverse(cell, color, Figure::PAWN);
        else if (board.getFigureBitBoard(color, Figure::BISHOP).getBit(cell)) inverse(cell, color, Figure::PAWN);
        else if (board.getFigureBitBoard(color, Figure::ROOK).getBit(cell)) inverse(cell, color, Figure::PAWN);
        else if (board.getFigureBitBoard(color, Figure::QUEEN).getBit(cell)) inverse(cell, color, Figure::PAWN);
        else if (board.getFigureBitBoard(color, Figure::KING).getBit(cell)) inverse(cell, color, Figure::PAWN);
    }
}

uint64_t Hash::getValue() const {
    return value;
}

void Hash::inverse(int pos, Color color, Figure figure) {
    value ^= HashConstants::CONSTANTS[pos][(int) color][(int) figure];
}

bool operator==(Hash const& l, Hash const& r) {
    return l.getValue() == r.getValue();
}
