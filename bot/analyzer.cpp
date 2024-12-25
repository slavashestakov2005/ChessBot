#include <bot/analuzer.h>

enum class MOBILITY {
    KNIGHT = 12,
    BISHOP = 8,
    ROOK = 5,
    QUEEN = 5,
};

int32_t Analyzer::analyze(Board const& board) {
    int32_t result = 0;
    result += material(board);
    result += mobility(board);
    return result;
}

int32_t Analyzer::material(Board const& board) {
    int32_t result = 0;
    result += (int32_t) Material::PAWN * (board.getFigureBitBoard(Color::WHITE, Figure::PAWN).ones() -
                                         board.getFigureBitBoard(Color::BLACK, Figure::PAWN).ones());
    result += (int32_t) Material::KNIGHT * (board.getFigureBitBoard(Color::WHITE, Figure::KNIGHT).ones() -
                                            board.getFigureBitBoard(Color::BLACK, Figure::KNIGHT).ones());
    result += (int32_t) Material::BISHOP * (board.getFigureBitBoard(Color::WHITE, Figure::BISHOP).ones() -
                                            board.getFigureBitBoard(Color::BLACK, Figure::BISHOP).ones());
    result += (int32_t) Material::ROOK * (board.getFigureBitBoard(Color::WHITE, Figure::ROOK).ones() -
                                          board.getFigureBitBoard(Color::BLACK, Figure::ROOK).ones());
    result += (int32_t) Material::QUEEN * (board.getFigureBitBoard(Color::WHITE, Figure::QUEEN).ones() -
                                           board.getFigureBitBoard(Color::BLACK, Figure::QUEEN).ones());
    return result;
}

int32_t Analyzer::mobility(Board const& board) {
    return 0;
}
