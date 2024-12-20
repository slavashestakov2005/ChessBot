#include <figures/knight.h>

char Knight::latter = 'n';
int Knight::cost = 30;
int Knight::cost_table[8][8] = {{-50,-40,-30,-30,-30,-30,-40,-50},
                                {-40,-20,  0,  0,  0,  0,-20,-40},
                                {-30,  0, 10, 15, 15, 10,  0,-30},
                                {-30,  5, 15, 20, 20, 15,  5,-30},
                                {-30,  0, 15, 20, 20, 15,  0,-30},
                                {-30,  5, 10, 15, 15, 10,  5,-30},
                                {-40,-20,  0,  5,  5,  0,-20,-40},
                                {-50,-40,-30,-30,-30,-30,-40,-50}};

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
