#pragma once
#include <board/bitboard.h>
#include <board/figures.h>
#include <string>

class Board {
public:
    Board();
    void placement(std::string s);
    void defaultPlacement();
    void updateBitBoards();
    BitBoard getFigureBitBoard(Color color, Figure figure) const;
    BitBoard getColorBitBoard(Color color) const;
    BitBoard getInvColorBitBoard(Color color) const;
    BitBoard getAnyBitBoard() const;
    BitBoard getNoneBitBoard() const;
    std::array<std::array<BitBoard, 6>, 2> getAllFigures() const;
    void setFigureBitBoard(Color color, Figure figure, BitBoard new_bb);
private:
    std::array<std::array<BitBoard, 6>, 2> figures;
    std::array<BitBoard, 2> colorFigures;
    std::array<BitBoard, 2> invColorFigures;
    BitBoard anyFigures;
    BitBoard noneFigures;
};

std::ostream &operator<<(std::ostream &os, Board const& board);
