#include <board/figures.h>

Color inv(Color color) {
    if (color == Color::WHITE) return Color::BLACK;
    return Color::WHITE;
}
