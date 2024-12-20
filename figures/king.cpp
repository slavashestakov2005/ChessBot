#include <figures/king.h>

char King::latter = 'k';

#define WHITE_KING(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY || c == Color::BLACK) to.push_back({x, y}); \
    /* if x, y bitten ? */ \
}

#define BLACK_KING(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY || c == Color::WHITE) to.push_back({x, y}); \
    /* if x, y bitten ? */ \
}

std::vector<Pos> King::moves(Board const& board, Pos pos, Color color) {
    std::vector<Pos> to;
    if (color == Color::WHITE) {
        WHITE_KING(pos.x + 1, pos.y);
        WHITE_KING(pos.x + 1, pos.y + 1);
        WHITE_KING(pos.x, pos.y + 1);
        WHITE_KING(pos.x - 1, pos.y + 1);
        WHITE_KING(pos.x - 1, pos.y);
        WHITE_KING(pos.x - 1, pos.y - 1);
        WHITE_KING(pos.x, pos.y - 1);
        WHITE_KING(pos.x + 1, pos.y - 1);
    } else if (color == Color::BLACK) {
        BLACK_KING(pos.x + 1, pos.y);
        BLACK_KING(pos.x + 1, pos.y + 1);
        BLACK_KING(pos.x, pos.y + 1);
        BLACK_KING(pos.x - 1, pos.y + 1);
        BLACK_KING(pos.x - 1, pos.y);
        BLACK_KING(pos.x - 1, pos.y - 1);
        BLACK_KING(pos.x, pos.y - 1);
        BLACK_KING(pos.x + 1, pos.y - 1);
    }
    return to;
}
