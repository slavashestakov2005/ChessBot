#include <bot/legal_moves.h>
#include <figures/pseudo_moves.h>

template <typename Func>
void LegalMoves::generateForFigureType(Board const& board, Color color, Figure figure, Func generator, bool only_attack, Moves &moves) {
    BitBoard allFigs = board.getFigureBitBoard(color, figure);
    while (allFigs) {
        uint8_t from_cell = allFigs.getHigh1();
        allFigs = allFigs.set0(from_cell);
        BitBoard mask = generator(board, from_cell, color, only_attack);
        LegalMoves::generateRegular(board, mask, from_cell, figure, color, moves);
    }
}

Moves LegalMoves::generate(Position const& position, Color color, bool only_attack) {
    Moves moves;
    Board board = position.getBoard();
    generatePawnsAll(board, color, only_attack, moves);
    generateForFigureType(board, color, Figure::KNIGHT, PseudoMoves::movesKnight, only_attack, moves);
    generateForFigureType(board, color, Figure::BISHOP, PseudoMoves::movesBishop, only_attack, moves);
    generateForFigureType(board, color, Figure::ROOK, PseudoMoves::movesRook, only_attack, moves);
    generateForFigureType(board, color, Figure::QUEEN, PseudoMoves::movesQueen, only_attack, moves);
    generateForFigureType(board, color, Figure::KING, PseudoMoves::movesKing, only_attack, moves);
    return moves;
}

void LegalMoves::generatePawnsAll(Board const& board, Color color, bool only_attack, Moves &moves) {
    BitBoard pl = PseudoMoves::pawnLeft(board, color, false);
    BitBoard pr = PseudoMoves::pawnRight(board, color, false);
    if (color == Color::WHITE) {
        generatePawnsPart(board, pl, color, -7, true, SpecialMove::NONE, moves);
        generatePawnsPart(board, pr, color, -9, true, SpecialMove::NONE, moves);
    } else {
        generatePawnsPart(board, pl, color, 7, true, SpecialMove::NONE, moves);
        generatePawnsPart(board, pr, color, 9, true, SpecialMove::NONE, moves);
    }
    if (!only_attack) {
        BitBoard step_short = PseudoMoves::pawnDefault(board, color);
        BitBoard step_long = PseudoMoves::pawnLong(board, color);
        if (color == Color::WHITE) {
            generatePawnsPart(board, step_short, color, -8, false, SpecialMove::NONE, moves);
            generatePawnsPart(board, step_long, color, -16, false, SpecialMove::PAWN_LONG, moves);
        } else {
            generatePawnsPart(board, step_short, color, 8, false, SpecialMove::NONE, moves);
            generatePawnsPart(board, step_long, color, 16, false, SpecialMove::PAWN_LONG, moves);
        }
    }
}

void LegalMoves::generatePawnsPart(Board const& board, BitBoard mask, Color from_color, int8_t step_delta, bool attack, SpecialMove flag, Moves &moves) {
    Color invc = inv(from_color);
    while (mask) {
        uint8_t to_cell = mask.getHigh1();
        mask = mask.set0(to_cell);
        Figure to_figure = Figure::NONE;
        Color to_color = Color::NONE;
        if (attack) {
            for (Figure fig : FIGURES) {
                if (board.getFigureBitBoard(invc, fig).getBit(to_cell)) {
                    to_figure = fig;
                    to_color = invc;
                    break;
                }
            }
        }
        Move move(to_cell + step_delta, to_cell, from_color, Figure::PAWN, to_color, to_figure, flag);
        if (to_cell < 8 || to_cell > 55) {
            move.special = SpecialMove::PAWN_KNIGHT;
            moves.push(move);
            move.special = SpecialMove::PAWN_BISHOP;
            moves.push(move);
            move.special = SpecialMove::PAWN_ROOK;
            moves.push(move);
            move.special = SpecialMove::PAWN_QUEEN;
            moves.push(move);
            move.special = SpecialMove::PAWN_KING;
            moves.push(move);
        } else {
            moves.push(move);
        }
    }
}

void LegalMoves::generateRegular(Board const& board, BitBoard mask, uint8_t from_cell, Figure from_figure, Color from_color, Moves &moves) {
    Color invc = inv(from_color);
    while (mask) {
        uint8_t to_cell = mask.getHigh1();
        mask = mask.set0(to_cell);
        Figure to_figure = Figure::NONE;
        Color to_color = Color::NONE;
        for (Figure fig : FIGURES) {
            if (board.getFigureBitBoard(invc, fig).getBit(to_cell)) {
                to_figure = fig;
                to_color = invc;
                break;
            }
        }
        moves.push(Move(from_cell, to_cell, from_color, from_figure, to_color, to_figure));
    }
}
