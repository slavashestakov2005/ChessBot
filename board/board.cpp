#include <board/board.h>

Board::Board() {
    for (auto &x : board) for (auto &y : x) y = FigureType::EMPTY;
}

Color Board::getColor(int x, int y) const {
    if (x < 0 || y < 0 || x > 7 || y > 7) return Color::OUT;
    if (board[x][y] == FigureType::EMPTY) return Color::EMPTY;
    return board[x][y] < FigureType::COLOR_SEP ? Color::WHITE : Color::BLACK;
}
