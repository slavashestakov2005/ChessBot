#include <iostream>
#include <board/board.h>
#include <bot/legal_moves.h>
#include <bot/bot.h>

void test_default_placement() {
    Board board;
    board.defaultPlacement();
    std::cout << board;
}

void print_cell(uint8_t cell) {
    int x = cell % 8, y = cell / 8;
    std::cout << char('a' + x) << char('1' + y);
}

void print_move(Move const& move) {
    std::cout << "From: "; print_cell(move.cell_from); std::cout << "  To: "; print_cell(move.cell_to); std::cout << "\n";
    std::cout << "Col:   " << (int) move.color_from << "       " << (int) move.color_to << "\n";
    std::cout << "Fig:   " << (int) move.figure_from << "       " << (int) move.figure_to << "\n";
    std::cout << "Spec:    " << (int) move.special << "\n";
}

void print_moves(std::string msg, Moves const& moves) {
    std::cout << msg << "\n";
    for (int i = 0; i < moves.size(); ++i) {
        Move move = moves[i];
        print_move(move);
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

uint8_t readCell() {
    char lat, dig;
    std::cin >> lat >> dig;
    if (lat == 'q') exit(0);
    uint8_t y = dig - '1', x = lat - 'a';
    return y * 8 + x;
}

Move readMove(Board const& board, Color color) {
    uint8_t from_cell = readCell(), to_cell = readCell();
    Figure from_figure = Figure::NONE, to_figure = Figure::NONE;
    Color from_color = Color::NONE, to_color = Color::NONE;
    Color invc = inv(color);
    for (Figure fig : FIGURES) {
        if (board.getFigureBitBoard(color, fig).getBit(from_cell)) {
            from_figure = fig;
            from_color = color;
        }
        if (board.getFigureBitBoard(invc, fig).getBit(from_cell)) {
            from_figure = fig;
            from_color = invc;
        }
        if (board.getFigureBitBoard(color, fig).getBit(to_cell)) {
            to_figure = fig;
            to_color = color;
        }
        if (board.getFigureBitBoard(invc, fig).getBit(to_cell)) {
            to_figure = fig;
            to_color = invc;
        }
    }
    if (from_color == Color::NONE) exit(1);
    return Move(from_cell, to_cell, from_color, from_figure, to_color, to_figure);
}

void test_play_game() {
    Position pos;
    std::cout << pos;
    while (true) {
        Move white_move = Bot::getBestMove(pos);
        std::cout << "Bot move:\n";
        print_move(white_move);
        pos.move(white_move);
        std::cout << "\n\n" << pos << "From to: ";
        Move black_move = readMove(pos.getBoard(), Color::BLACK);
        std::cout << "Your move:\n";
        print_move(black_move);
        pos.move(black_move);
        std::cout << pos << "\n";
    }
}

void test_bot_bot() {
    Position pos;
    std::cout << pos;
    char c;
    while (std::cin >> c) {
        Move white_move = Bot::getBestMove(pos);
        std::cout << "White move:\n";
        // print_move(white_move);
        pos.move(white_move);
        std::cout << pos;
        Move black_move = Bot::getBestMove(pos);
        std::cout << "Black move:\n";
        // print_move(black_move);
        pos.move(black_move);
        std::cout << pos;
    }
}
