#pragma once
#include <board/position.h>

class Hash {
public:
    Hash();
    Hash(Position const& pos);
    uint64_t getValue() const;
private:
    void inverse(int pos, Color color, Figure figure);
    uint64_t value;
};

bool operator==(Hash const& l, Hash const& r);

namespace HashConstants {
    consteval uint64_t nextRandomNumber(uint64_t previous);
    consteval std::array<std::array<std::array<uint64_t, 6>, 2>, 64> calcConstants();
}

#include <board/hash.impl>

namespace HashConstants {
    constexpr std::array<std::array<std::array<uint64_t, 6>, 2>, 64> CONSTANTS = calcConstants();
    constexpr uint64_t BLACK_STEP = nextRandomNumber(CONSTANTS[63][1][5]);
}
