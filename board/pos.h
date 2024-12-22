#pragma once
#include <cstdint>
#include <ostream>

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

std::ostream& operator<<(std::ostream& os, Pos const& pos);
