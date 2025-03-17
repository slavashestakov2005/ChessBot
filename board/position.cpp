#include <board/position.h>
#include <settings/settings.h>

uint8_t Position::EN_PASSANT_NONE = 255;

Position::Position() : board(), en_passant(EN_PASSANT_NONE), step(0) {
    board.defaultPlacement();
    hash = Hash(*this);
}

Position::Position(Board board) : board(board), en_passant(EN_PASSANT_NONE), step(0) {
    hash = Hash(*this);
}

void Position::move(Move move) {
    if (move.special == SpecialMove::CASTLE) {
        Color color = move.color_from;
        uint8_t king = move.cell_from, rook = move.cell_to;
        removeFigure(king, Figure::KING, color);
        removeFigure(rook, Figure::ROOK, color);
        uint8_t delta_king = rook > king ? 2 : -2;
        uint8_t delta_rook = rook > king ? 1 : -1;
        addFigure(king + delta_king, Figure::KING_MOVED, color);
        addFigure(king + delta_rook, Figure::ROOK_MOVED, color);
    } else {
        removeFigure(move.cell_from, move.figure_from, move.color_from);
        {
            Figure new_fig = move.figure_from;
            if (new_fig == Figure::KING) new_fig = Figure::KING_MOVED;
            if (new_fig == Figure::ROOK) new_fig = Figure::ROOK_MOVED;
            addFigure(move.cell_to, new_fig, move.color_from);
        }
        if (move.figure_to != Figure::NONE) {
            removeFigure(move.cell_to, move.figure_to, move.color_to);
        }
        switch (move.special) {
            case SpecialMove::NONE: break;
            case SpecialMove::EN_PASSANT:
                if (move.color_from == Color::WHITE) {
                    removeFigure(move.cell_to - 8, Figure::PAWN, Color::BLACK);
                } else {
                    removeFigure(move.cell_to + 8, Figure::PAWN, Color::WHITE);
                }
                break;
            case SpecialMove::PAWN_LONG:
                setEnPassant((move.cell_from + move.cell_to) / 2);
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
                addFigure(move.cell_to, Figure::ROOK_MOVED, move.color_from);
                break;
            case SpecialMove::PAWN_QUEEN:
                removeFigure(move.cell_to, move.figure_from, move.color_from);
                addFigure(move.cell_to, Figure::QUEEN, move.color_from);
                break;
            case SpecialMove::PAWN_KING:
                removeFigure(move.cell_to, move.figure_from, move.color_from);
                addFigure(move.cell_to, Figure::KING_MOVED, move.color_from);
                break;
        }
    }
    board.updateBitBoards();

    if (move.special != SpecialMove::PAWN_LONG) {
        setEnPassant(EN_PASSANT_NONE);
    }

    incStep();
}

Board Position::getBoard() const {
    return board;
}

uint8_t Position::getEnPassant() const {
    return en_passant;
}

Color Position::currentPlayer() const {
    char pl = Settings::player(step);
    if (pl == 'w') return Color::WHITE;
    if (pl == 'b') return Color::BLACK;
    throw std::invalid_argument("function player(step) return not w and not b");
}

Hash Position::getHash() const {
    return hash;
}

bool Position::isWhiteWon() const {
    BitBoard black_kings = board.getFigureBitBoard(Color::BLACK, Figure::KING) |
                           board.getFigureBitBoard(Color::BLACK, Figure::KING_MOVED);
    return black_kings.ones() <= Settings::getWhiteGoal();
}

bool Position::isBlackWon() const {
    BitBoard white_kings = board.getFigureBitBoard(Color::WHITE, Figure::KING) |
                           board.getFigureBitBoard(Color::WHITE, Figure::KING_MOVED);
    return white_kings.ones() <= Settings::getBlackGoal();
}

void Position::incStep() {
    Color old_player = currentPlayer();
    ++step;
    Color new_player = currentPlayer();
    if (old_player == new_player) setEnPassant(EN_PASSANT_NONE);
    if (old_player != new_player) hash.inversePlayer();
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

void Position::setEnPassant(uint8_t cell) {
    en_passant = cell;
}

std::ostream &operator<<(std::ostream &os, Position const& position) {
    return os << position.getBoard();
}
