#pragma once
#include <board/board.h>
#include <board/hash.h>
#include <board/move.h>

class Position {
public:
    Position();
    Position(Board board);
    void move(Move move);
    Board getBoard() const;
    Color currentPlayer() const;
    Hash getHash() const;
private:
    void incStep();
    void removeFigure(uint8_t cell, Figure figure, Color color);
    void addFigure(uint8_t cell, Figure figure, Color color);
    Board board;
    int step;
    Hash hash;
};

std::ostream &operator<<(std::ostream &os, Position const& position);
