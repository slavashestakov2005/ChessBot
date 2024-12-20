#include <figures/pawn.h>

char Pawn::latter = 'p';

std::vector<Pos> Pawn::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        if (board.getColor(pos.x - 1, pos.y + 1) == Color::EMPTY) to.push_back({pos.x - 1, pos.y + 1});
        if (board.getColor(pos.x + 1, pos.y + 1) == Color::EMPTY) to.push_back({pos.x + 1, pos.y + 1});
        if (board.getColor(pos.x, pos.y + 1) == Color::EMPTY) {
            to.push_back({pos.x, pos.y + 1});
            if (pos.y == 1 && board.getColor(pos.x, pos.y + 2) == Color::EMPTY) to.push_back({pos.x, pos.y + 2});
        }
    } else if (color == Color::BLACK) {
        if (board.getColor(pos.x - 1, pos.y - 1) == Color::EMPTY) to.push_back({pos.x - 1, pos.y - 1});
        if (board.getColor(pos.x + 1, pos.y - 1) == Color::EMPTY) to.push_back({pos.x + 1, pos.y - 1});
        if (board.getColor(pos.x, pos.y - 1) == Color::EMPTY) {
            to.push_back({pos.x, pos.y - 1});
            if (pos.y == 6 && board.getColor(pos.x, pos.y - 2) == Color::EMPTY) to.push_back({pos.x, pos.y - 2});
        }
    }
    return to;
}
