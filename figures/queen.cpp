#include <figures/queen.h>
#include <figures/macro.h>

char Queen::latter = 'q';
int Queen::cost = 90;
int Queen::cost_table[8][8] = {{-20,-10,-10, -5, -5,-10,-10,-20},
                               {-10,  0,  0,  0,  0,  0,  0,-10},
                               {-10,  0,  5,  5,  5,  5,  0,-10},
                               { -5,  0,  5,  5,  5,  5,  0, -5},
                               {  0,  0,  5,  5,  5,  5,  0, -5},
                               {-10,  5,  5,  5,  5,  5,  0,-10},
                               {-10,  0,  5,  0,  0,  0,  0,-10},
                               {-20,-10,-10, -5, -5,-10,-10,-20}};

std::vector<Pos> Queen::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        for (int x = pos.x - 1; ; --x) WHITE_STEP(x, pos.y);
        for (int x = pos.x + 1; ; ++x) WHITE_STEP(x, pos.y);
        for (int y = pos.y - 1; ; --y) WHITE_STEP(pos.x, y);
        for (int y = pos.y + 1; ; ++y) WHITE_STEP(pos.x, y);

        for (int x = pos.x + 1, y = pos.y + 1; ; ++x, ++y) WHITE_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y + 1; ; --x, ++y) WHITE_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y - 1; ; --x, --y) WHITE_STEP(x, y);
        for (int x = pos.x + 1, y = pos.y - 1; ; ++x, --y) WHITE_STEP(x, y);
    } else if (color == Color::BLACK) {
        for (int x = pos.x - 1; ; --x) BLACK_STEP(x, pos.y);
        for (int x = pos.x + 1; ; ++x) BLACK_STEP(x, pos.y);
        for (int y = pos.y - 1; ; --y) BLACK_STEP(pos.x, y);
        for (int y = pos.y + 1; ; ++y) BLACK_STEP(pos.x, y);

        for (int x = pos.x + 1, y = pos.y + 1; ; ++x, ++y) BLACK_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y + 1; ; --x, ++y) BLACK_STEP(x, y);
        for (int x = pos.x - 1, y = pos.y - 1; ; --x, --y) BLACK_STEP(x, y);
        for (int x = pos.x + 1, y = pos.y - 1; ; ++x, --y) BLACK_STEP(x, y);   
    }
    return to;
}
