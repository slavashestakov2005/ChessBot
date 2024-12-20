#include <figures/empty.h>

char Empty::latter = ' ';
int Empty::cost = 0;
int Empty::cost_table[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0,  0}};


std::vector<Pos> Empty::moves(Board const& board, Pos pos, Color color) {
    return {};
}
