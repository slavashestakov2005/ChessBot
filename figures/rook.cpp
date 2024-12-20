#include <figures/rook.h>
#include <figures/macro.h>

char Rook::latter = 'r';
int Rook::cost = 50;
int Rook::cost_table[8][8] = {{  0,  0,  0,  0,  0,  0,  0,  0},
                              {  5, 10, 10, 10, 10, 10, 10,  5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              {  0,  0,  0,  5,  5,  0,  0,  0}};

std::vector<Pos> Rook::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        for (int x = pos.x - 1; ; --x) WHITE_STEP(x, pos.y);
        for (int x = pos.x + 1; ; ++x) WHITE_STEP(x, pos.y);
        for (int y = pos.y - 1; ; --y) WHITE_STEP(pos.x, y);
        for (int y = pos.y + 1; ; ++y) WHITE_STEP(pos.x, y);
    } else if (color == Color::BLACK) {
        for (int x = pos.x - 1; ; --x) BLACK_STEP(x, pos.y);
        for (int x = pos.x + 1; ; ++x) BLACK_STEP(x, pos.y);
        for (int y = pos.y - 1; ; --y) BLACK_STEP(pos.x, y);
        for (int y = pos.y + 1; ; ++y) BLACK_STEP(pos.x, y);    
    }
    return to;
}
