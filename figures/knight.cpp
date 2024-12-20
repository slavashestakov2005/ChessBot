#include <figures/knight.h>

char Knight::latter = 'n';

#define WHITE_KNIGHT(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY || c == Color::BLACK) to.push_back({x, y}); \
}

#define BLACK_KNIGHT(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY || c == Color::WHITE) to.push_back({x, y}); \
}

std::vector<Pos> Knight::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        WHITE_KNIGHT(pos.x + 2, pos.y + 1);
        WHITE_KNIGHT(pos.x + 1, pos.y + 2);
        WHITE_KNIGHT(pos.x - 1, pos.y + 2);
        WHITE_KNIGHT(pos.x - 2, pos.y + 1);
        WHITE_KNIGHT(pos.x - 2, pos.y - 1);
        WHITE_KNIGHT(pos.x - 1, pos.y - 2);
        WHITE_KNIGHT(pos.x + 1, pos.y - 2);
        WHITE_KNIGHT(pos.x + 2, pos.y - 1);
    } else if (color == Color::BLACK) {
        BLACK_KNIGHT(pos.x + 2, pos.y + 1);
        BLACK_KNIGHT(pos.x + 1, pos.y + 2);
        BLACK_KNIGHT(pos.x - 1, pos.y + 2);
        BLACK_KNIGHT(pos.x - 2, pos.y + 1);
        BLACK_KNIGHT(pos.x - 2, pos.y - 1);
        BLACK_KNIGHT(pos.x - 1, pos.y - 2);
        BLACK_KNIGHT(pos.x + 1, pos.y - 2);
        BLACK_KNIGHT(pos.x + 2, pos.y - 1);
    }
    return to;
}
