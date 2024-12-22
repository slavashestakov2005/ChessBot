#include <board/figure_type.h>
#include <figures/all.h>

constexpr const BaseFigure* figures_classes[] =
    {&Empty::instance, &Pawn::instance, &Rook::instance, &Knight::instance, &Bishop::instance,
     &King::instance, &Queen::instance, &Rook::instance, &King::instance,
     &Empty::instance, &Pawn::instance, &Rook::instance, &Knight::instance, &Bishop::instance,
     &King::instance, &Queen::instance, &Rook::instance, &King::instance};

constexpr Color figures_color[] = {Color::EMPTY, Color::WHITE, Color::WHITE, Color::WHITE, Color::WHITE,
                                   Color::WHITE, Color::WHITE, Color::WHITE, Color::WHITE,
                                   Color::EMPTY, Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK,
                                   Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK};

Color getColor(FigureType type) {
    int id = static_cast<uint8_t>(type);
    return figures_color[id];
} 

char getChar(FigureType type) {
    int id = static_cast<uint8_t>(type);
    return figures_classes[id]->print(figures_color[id]);
}

int getMaterial(FigureType type) {
    int id = static_cast<uint8_t>(type);
    return figures_classes[id]->material(figures_color[id]);
}

int getMaterial(FigureType type, Pos pos) {
    int id = static_cast<uint8_t>(type);
    return figures_classes[id]->materialPlace(pos, figures_color[id]);
}

std::vector<Pos> getSteps(Board const& board, Pos pos) {
    FigureType type = board.getType(pos.x, pos.y);
    int id = static_cast<uint8_t>(type);
    return figures_classes[id]->step(board, pos, figures_color[id]);
}
