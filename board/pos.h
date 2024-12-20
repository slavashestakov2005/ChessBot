#pragma once
#include <cstdint>

enum class Color : uint8_t {
    WHITE,
    BLACK,
    EMPTY,
    OUT,
};

class Pos {
public:
    int x, y;
};
