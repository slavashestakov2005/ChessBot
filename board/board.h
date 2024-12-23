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
    BitBoard getColorBitBoard(Color color) const;
    BitBoard getFigureBitBoard(Color color, Figure figure) const;
    void setFigureBitBoard(Color color, Figure figure, BitBoard new_bb);
private:
    std::array<std::array<BitBoard, 6>, 2> figures;
    std::array<BitBoard, 2> colorFigures;
    std::array<BitBoard, 2> invColorFigures;
    BitBoard anyFigures;
    BitBoard noFigures;
};

std::ostream &operator<<(std::ostream &os, Board const& board);
