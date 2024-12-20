#pragma once
#include <board/board.h>

class Analyzer {
public:
    static int analyzeMaterial(Board const& board);
    static int analyzeMaterialPosition(Board const& board);
};
