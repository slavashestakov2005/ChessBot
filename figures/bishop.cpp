#include <figures/bishop.h>
#include <figures/macro.h>

char Bishop::latter = 'b';
int Bishop::cost = 30;
int Bishop::cost_table[8][8] = {{-20,-10,-10,-10,-10,-10,-10,-20},
                                {-10,  0,  0,  0,  0,  0,  0,-10},
                                {-10,  0,  5, 10, 10,  5,  0,-10},
                                {-10,  5,  5, 10, 10,  5,  5,-10},
                                {-10,  0, 10, 10, 10, 10,  0,-10},
                                {-10, 10, 10, 10, 10, 10, 10,-10},
                                {-10,  5,  0,  0,  0,  0,  5,-10},
                                {-20,-10,-10,-10,-10,-10,-10,-20}};

std::vector<Pos> Bishop::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        for (int x = pos.x + 1, y = pos.y + 1; ; ++x, ++y) WHITE_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y + 1; ; --x, ++y) WHITE_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y - 1; ; --x, --y) WHITE_STEP(x, y);
        for (int x = pos.x + 1, y = pos.y - 1; ; ++x, --y) WHITE_STEP(x, y);
    } else if (color == Color::BLACK) {
        for (int x = pos.x + 1, y = pos.y + 1; ; ++x, ++y) BLACK_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y + 1; ; --x, ++y) BLACK_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y - 1; ; --x, --y) BLACK_STEP(x, y);
        for (int x = pos.x + 1, y = pos.y - 1; ; ++x, --y) BLACK_STEP(x, y);   
    }
    return to;
}
