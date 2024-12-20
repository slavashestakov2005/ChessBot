#include <figures/bishop.h>
#include <figures/macro.h>

char Bishop::latter = 'b';

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
