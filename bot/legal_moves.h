#pragma once
#include <board/position.h>
#include <bot/moves.h>

class LegalMoves {
public:
    static Moves generate(Position const& position, Color color, bool only_attack=false);
private:
    static void generatePawnsAll(Board const& board, Color color, bool only_attack, Moves &moves);
    static void generatePawnsPart(Board const& board, BitBoard mask, Color from_color, int8_t step_delta, bool attack, SpecialMove flag, Moves &moves);
    static void generateRegular(Board const& board, BitBoard mask, uint8_t from_cell, Figure from_figure, Color from_color, Moves &moves);
    template <typename Func>
    static void generateForFigureType(Board const& board, Color color, Figure figure, Func generator, bool only_attack, Moves &moves);
};
