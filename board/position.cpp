#include <board/position.h>

char player(int step) {
    return step % 2 == 0 ? 'w' : 'b';
}

Position::Position() : board(), step(0) {
    board.defaultPlacement();
    hash = Hash(*this);
}

Position::Position(Board board) : board(board), step(0) {
    hash = Hash(*this);
}

void Position::move(Move move) {
    removeFigure(move.cell_from, move.figure_from, move.color_from);
    addFigure(move.cell_to, move.figure_from, move.color_from);
    if (move.figure_to != Figure::NONE) {
        removeFigure(move.cell_to, move.figure_to, move.color_to);
    }
    switch (move.special) {
        case SpecialMove::NONE: break;
        case SpecialMove::PAWN_LONG:
            // en pass
            break;
        case SpecialMove::PAWN_KNIGHT:
            removeFigure(move.cell_to, move.figure_from, move.color_from);
            addFigure(move.cell_to, Figure::KNIGHT, move.color_from);
            break;
        case SpecialMove::PAWN_BISHOP:
            removeFigure(move.cell_to, move.figure_from, move.color_from);
            addFigure(move.cell_to, Figure::BISHOP, move.color_from);
            break;
        case SpecialMove::PAWN_ROOK:
            removeFigure(move.cell_to, move.figure_from, move.color_from);
            addFigure(move.cell_to, Figure::ROOK, move.color_from);
            break;
        case SpecialMove::PAWN_QUEEN:
            removeFigure(move.cell_to, move.figure_from, move.color_from);
            addFigure(move.cell_to, Figure::QUEEN, move.color_from);
            break;
    }
    board.updateBitBoards();
    incStep();
}

Board Position::getBoard() const {
    return board;
}

Color Position::currentPlayer() const {
    return player(step) == 'w' ? Color::WHITE : Color::BLACK;
}

Hash Position::getHash() const {
    return hash;
}

void Position::incStep() {
    ++step;
    hash.inversePlayer();
}

void Position::removeFigure(uint8_t cell, Figure figure, Color color) {
    if (board.getFigureBitBoard(color, figure).getBit(cell)) {
        board.setFigureBitBoard(color, figure, board.getFigureBitBoard(color, figure).set0(cell));
        hash.inverse(cell, color, figure);
    }
}
void Position::addFigure(uint8_t cell, Figure figure, Color color) {
    if (!board.getFigureBitBoard(color, figure).getBit(cell)) {
        board.setFigureBitBoard(color, figure, board.getFigureBitBoard(color, figure).set1(cell));
        hash.inverse(cell, color, figure);
    }
}

std::ostream &operator<<(std::ostream &os, Position const& position) {
    return os << position.getBoard();
}
