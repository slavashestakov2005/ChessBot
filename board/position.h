#pragma once
#include <board/board.h>
#include <board/hash.h>
#include <board/move.h>

class Position {
public:
    static uint8_t EN_PASSANT_NONE;

    Position();
    Position(Board board);
    void move(Move move);
    Board getBoard() const;
    uint8_t getEnPassant() const;
    Color currentPlayer() const;
    Hash getHash() const;
    uint8_t getWhiteGoal() const;
    uint8_t getBlackGoal() const;
    bool isWhiteWon() const;
    bool isBlackWon() const;
    int getStep() const;
private:
    void incStep();
    void removeFigure(uint8_t cell, Figure figure, Color color);
    void addFigure(uint8_t cell, Figure figure, Color color);
    void setEnPassant(uint8_t cell);

    Board board;
    uint8_t en_passant;
    int step;
    Hash hash;
};

std::ostream &operator<<(std::ostream &os, Position const& position);
