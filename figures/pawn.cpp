#include <figures/pawn.h>

char Pawn::latter = 'p';
int Pawn::cost = 10;
int Pawn::cost_table[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0},
                              {50, 50, 50, 50, 50, 50, 50, 50},
                              {10, 10, 20, 30, 30, 20, 10, 10},
                              {5,  5, 10, 25, 25, 10,  5,  5},
                              {0,  0,  0, 20, 20,  0,  0,  0},
                              {5, -5,-10,  0,  0,-10, -5,  5},
                              {5, 10, 10,-20,-20, 10, 10,  5},
                              {0,  0,  0,  0,  0,  0,  0,  0}};

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
