#include <board/board.h>
#include <figures/all.h>
#include <iostream>
#include <string>

Board::Board() {
    for (auto &x : board) for (auto &y : x) y = FigureType::EMPTY;
}

void Board::defaultPlacement() {
    board[0][0] = board[0][7] = FigureType::WHITE_ROOK;
    board[0][1] = board[0][6] = FigureType::WHITE_KNIGHT;
    board[0][2] = board[0][5] = FigureType::WHITE_BISHOP;
    board[0][3] = FigureType::WHITE_QUEEN;
    board[0][4] = FigureType::WHITE_KING;
    for (int j = 0; j < 8; ++j) board[1][j] = FigureType::WHITE_PAWN;
    board[7][0] = board[7][7] = FigureType::BLACK_ROOK;
    board[7][1] = board[7][6] = FigureType::BLACK_KNIGHT;
    board[7][2] = board[7][5] = FigureType::BLACK_BISHOP;
    board[7][3] = FigureType::BLACK_QUEEN;
    board[7][4] = FigureType::BLACK_KING;
    for (int j = 0; j < 8; ++j) board[6][j] = FigureType::BLACK_PAWN;
}

Color Board::getColor(int x, int y) const {
    if (x < 0 || y < 0 || x > 7 || y > 7) return Color::OUT;
    if (board[y][x] == FigureType::EMPTY) return Color::EMPTY;
    return board[y][x] < FigureType::COLOR_SEP ? Color::WHITE : Color::BLACK;
}

FigureType Board::getType(int x, int y) const {
    return board[y][x];
}

void Board::setType(Pos pos, FigureType type) {
    board[pos.y][pos.x] = type;
}

void Board::print() const {
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << getChar(board[i][j]);
        }
        std::cout << "\n";
    }
}
