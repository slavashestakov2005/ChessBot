#include <iostream>
#include <board/board.h>
#include <bot/legal_moves.h>

void test_default_placement() {
    Board board;
    board.defaultPlacement();
    std::cout << board;
}

void print_cell(uint8_t cell) {
    int x = cell % 8, y = cell / 8;
    std::cout << char('a' + x) << char('1' + y);
}

void print_moves(std::string msg, Moves const& moves) {
    std::cout << msg << "\n";
    for (int i = 0; i < moves.size(); ++i) {
        Move move = moves[i];
        std::cout << "From: "; print_cell(move.cell_from); std::cout << "  To: "; print_cell(move.cell_to); std::cout << "\n";
        std::cout << "Col:   " << (int) move.color_from << "       " << (int) move.color_to << "\n";
        std::cout << "Fig:   " << (int) move.figure_from << "       " << (int) move.figure_to << "\n";
        std::cout << "Spec:    " << (int) move.special << "\n";
    }
}

void test_steps_from_default_placement() {
    Board board;
    board.defaultPlacement();
    print_moves("Moves White, only_attack=false:", LegalMoves::generate(board, Color::WHITE, false));
    print_moves("Moves White, only_attack=true: ", LegalMoves::generate(board, Color::WHITE, true));
    print_moves("Moves Black, only_attack=false:", LegalMoves::generate(board, Color::BLACK, false));
    print_moves("Moves Black, only_attack=true: ", LegalMoves::generate(board, Color::BLACK, true));
}
