#pragma once
#include <board/board.h>

class Position {
public:
    Position();
    Position(Board board);
    Board getBoard() const;
    Color currentPlayer() const;
private:
    Board board;
    int step;
};
