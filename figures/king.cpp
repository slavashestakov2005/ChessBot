#include <figures/king.h>

char King::latter = 'k';
int King::cost = 900;
int King::cost_table[8][8] = {{-30,-40,-40,-50,-50,-40,-40,-30},
                              {-30,-40,-40,-50,-50,-40,-40,-30},
                              {-30,-40,-40,-50,-50,-40,-40,-30},
                              {-30,-40,-40,-50,-50,-40,-40,-30},
                              {-20,-30,-30,-40,-40,-30,-30,-20},
                              {-10,-20,-20,-20,-20,-20,-20,-10},
                              { 20, 20,  0,  0,  0,  0, 20, 20},
                              { 20, 30, 10,  0,  0, 10, 30, 20}};

/* table for end game
-50,-40,-30,-20,-20,-30,-40,-50,
-30,-20,-10,  0,  0,-10,-20,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-30,  0,  0,  0,  0,-30,-30,
-50,-30,-30,-30,-30,-30,-30,-50
*/

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
