#include <board/board.h>

Board::Board() {}

void Board::placement(std::string s) {
    for (auto& x : figures) for (auto &y : x) y = BitBoard();
    if (s.size() != 64) throw std::invalid_argument("Board: placement with len != 64");
    for (int pos = 0; pos < 64; ++pos) {
        char low = tolower(s[pos]);
        if (low == ' ') continue;
        Color color = (low == s[pos] ? Color::BLACK : Color::WHITE);
        Figure figure;
        switch (low) {
            case 'p': figure = Figure::PAWN; break;
            case 'n': figure = Figure::KNIGHT; break;
            case 'b': figure = Figure::BISHOP; break;
            case 'r': figure = Figure::ROOK; break;
            case 'q': figure = Figure::QUEEN; break;
            case 'k': figure = Figure::KING; break;
            default: throw std::invalid_argument("Board placement with unexpected figure");
        }
        figures[(int) color][(int) figure] = figures[(int) color][(int) figure].set1(pos);
    }
    updateBitBoards();
}

void Board::defaultPlacement() {
    Board::placement("RNBQKBNRPPPPPPPP                                pppppppprnbqkbnr");
}

void Board::updateBitBoards() {
    colorFigures[(int) Color::WHITE] = figures[(int) Color::WHITE][(int) Figure::PAWN] |
                                       figures[(int) Color::WHITE][(int) Figure::KNIGHT] |
                                       figures[(int) Color::WHITE][(int) Figure::BISHOP] |
                                       figures[(int) Color::WHITE][(int) Figure::ROOK] |
                                       figures[(int) Color::WHITE][(int) Figure::QUEEN] |
                                       figures[(int) Color::WHITE][(int) Figure::KING];
    colorFigures[(int) Color::BLACK] = figures[(int) Color::BLACK][(int) Figure::PAWN] |
                                       figures[(int) Color::BLACK][(int) Figure::KNIGHT] |
                                       figures[(int) Color::BLACK][(int) Figure::BISHOP] |
                                       figures[(int) Color::BLACK][(int) Figure::ROOK] |
                                       figures[(int) Color::BLACK][(int) Figure::QUEEN] |
                                       figures[(int) Color::BLACK][(int) Figure::KING];
    invColorFigures[(int) Color::WHITE] = colorFigures[(int) Color::WHITE].inv();
    invColorFigures[(int) Color::BLACK] = colorFigures[(int) Color::BLACK].inv();
    anyFigures = colorFigures[(int) Color::WHITE] | colorFigures[(int) Color::BLACK];
    noneFigures = anyFigures.inv();
}

BitBoard Board::getFigureBitBoard(Color color, Figure figure) const {
    return figures[(int) color][(int) figure];
}

BitBoard Board::getColorBitBoard(Color color) const {
    return colorFigures[(int) color];
}

BitBoard Board::getInvColorBitBoard(Color color) const {
    return invColorFigures[(int) color];
}

BitBoard Board::getAnyBitBoard() const {
    return anyFigures;
}

BitBoard Board::getNoneBitBoard() const {
    return noneFigures;
}

std::array<std::array<BitBoard, 6>, 2> Board::getAllFigures() const {
    return figures;
}

void Board::setFigureBitBoard(Color color, Figure figure, BitBoard new_bb) {
    figures[(int) color][(int) figure] = new_bb;
}

std::ostream &operator<<(std::ostream &os, Board const& board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            int index = i * 8 + j;
            if (board.getFigureBitBoard(Color::WHITE, Figure::PAWN).getBit(index)) os << 'P';
            else if (board.getFigureBitBoard(Color::WHITE, Figure::KNIGHT).getBit(index)) os << 'N';
            else if (board.getFigureBitBoard(Color::WHITE, Figure::BISHOP).getBit(index)) os << 'B';
            else if (board.getFigureBitBoard(Color::WHITE, Figure::ROOK).getBit(index)) os << 'R';
            else if (board.getFigureBitBoard(Color::WHITE, Figure::QUEEN).getBit(index)) os << 'Q';
            else if (board.getFigureBitBoard(Color::WHITE, Figure::KING).getBit(index)) os << 'K';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::PAWN).getBit(index)) os << 'p';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::KNIGHT).getBit(index)) os << 'n';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::BISHOP).getBit(index)) os << 'b';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::ROOK).getBit(index)) os << 'r';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::QUEEN).getBit(index)) os << 'q';
            else if (board.getFigureBitBoard(Color::BLACK, Figure::KING).getBit(index)) os << 'k';
            else os << ' ';
        }
        os << std::endl;
    }
    return os;
}
