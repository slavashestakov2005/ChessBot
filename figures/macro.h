#define WHITE_STEP(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY) to.push_back({x, y}); \
    else { \
        if (c == Color::BLACK) to.push_back({x, y}); \
        break; \
    } \
}

#define BLACK_STEP(x, y) { \
    Color c = board.getColor(x, y); \
    if (c == Color::EMPTY) to.push_back({x, y}); \
    else { \
        if (c == Color::WHITE) to.push_back({x, y}); \
        break; \
    } \
}
