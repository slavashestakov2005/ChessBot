#include <bot/analyzer.h>

int Analyzer::analyzeMaterial(Board const& board) {
    int sum = 0;
    for (int y = 0; y < 8; ++y) for (int x = 0; x < 8; ++x) {
        sum += getMaterial(board.getType(x, y));
    }
    return sum;
}

int Analyzer::analyzeMaterialPosition(Board const& board) {
    int sum = 0;
    for (int y = 0; y < 8; ++y) for (int x = 0; x < 8; ++x) {
        sum += getMaterial(board.getType(x, y), {x, y});
    }
    return sum;
}
