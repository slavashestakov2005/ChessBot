#include <iostream>
#include <board/board.h>
#include <figures/all.h>
#include <bot/analyzer.h>
#include <bot/stepper.h>

void test_steps_on_empty_board() {
    Board board;
    std::cout << "Pawn (1, 1):\n";
    for (Pos to : Pawn::moves(board, {1, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Rook (1, 1):\n";
    for (Pos to : Rook::moves(board, {1, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Knight (2, 1):\n";
    for (Pos to : Knight::moves(board, {2, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Bishop (3, 4):\n";
    for (Pos to : Bishop::moves(board, {3, 4}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "King (0, 2):\n";
    for (Pos to : King::moves(board, {0, 2}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Queen (2, 1):\n";
    for (Pos to : Queen::moves(board, {2, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
}

void test_default_placement() {
    Board board;
    board.defaultPlacement();
    board.print();
    std::cout << "Material Simple:   " << Analyzer::analyzeMaterial(board) << "\n";
    std::cout << "Material Position: " << Analyzer::analyzeMaterialPosition(board) << "\n";
}

void test_stepper() {
    Board board;
    board.defaultPlacement();
    board.print();
    Stepper stepper;
    Step step = stepper.run(board, 0);
    std::cout << "Best step is:  " << step.from << " -> " << step.to << "\n";
}

void test_play_game() {
    Board board;
    board.defaultPlacement();
    board.print();
    int cnt = 0;
    while (true) {
        Stepper stepper;
        Step step = stepper.run(board, cnt);
        board = applyMove(board, step);
        std::cout << "\n\n";
        board.print();
        std::cout << "From to: ";
        char s, d;
        Pos from, to;
        std::cin >> s >> d;
        if (s == 'q') break;
        from.x = s - 'a';
        from.y = d - '1';
        std::cin >> s >> d;
        to.x = s - 'a';
        to.y = d - '1';
        step = Step(from, to);
        board = applyMove(board, step);
        board.print();
        std::cout << "\n";
        cnt += 2;
    }
}