#include <iostream>
#include <board/board.h>
#include <figures/all.h>

void test_steps_on_empty_board() {
    Board board;
    std::cout << "Pawn (1, 1):\n";
    for (Pos to : Pawn::step(board, {1, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Rook (1, 1):\n";
    for (Pos to : Rook::step(board, {1, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Knight (2, 1):\n";
    for (Pos to : Knight::step(board, {2, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Bishop (3, 4):\n";
    for (Pos to : Bishop::step(board, {3, 4}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "King (0, 2):\n";
    for (Pos to : King::step(board, {0, 2}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
    std::cout << "Queen (2, 1):\n";
    for (Pos to : Queen::step(board, {2, 1}, Color::WHITE)) std::cout << to.x << " " << to.y << "\n";
}
