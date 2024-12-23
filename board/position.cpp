#include <board/position.h>

char player(int step) {
    return step % 2 == 0 ? 'w' : 'b';
}

Position::Position() : board(), step(0) {
    board.defaultPlacement();
}

Position::Position(Board board) : board(board), step(0) {}

Board Position::getBoard() const {
    return board;
}

Color Position::currentPlayer() const {
    return player(step) == 'w' ? Color::WHITE : Color::BLACK;
}
