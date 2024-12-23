#include <iostream>
#include <board/board.h>

void test_default_placement() {
    Board board;
    board.defaultPlacement();
    std::cout << board;
}
