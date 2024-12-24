#pragma once
#include <array>
#include <cstdint>
#include <ostream>

class BitBoard {
public:
    constexpr BitBoard();
    constexpr BitBoard(uint64_t board);
    constexpr uint64_t getAll() const;
    constexpr uint8_t ones() const;
    constexpr BitBoard inv() const;
    constexpr BitBoard set0(uint8_t place) const;
    constexpr BitBoard set1(uint8_t place) const;
    constexpr bool getBit(uint8_t place) const;
    constexpr uint8_t getHigh1() const;
    constexpr uint8_t getLow1() const;
    constexpr operator bool() const;
private:
    uint64_t board;
};

constexpr BitBoard operator|(BitBoard const& l, BitBoard const& r);
constexpr BitBoard operator&(BitBoard const& l, BitBoard const& r);
constexpr BitBoard operator^(BitBoard const& l, BitBoard const& r);
constexpr BitBoard operator<<(BitBoard const& bb, int shift);
constexpr BitBoard operator>>(BitBoard const& bb, int shift);
std::ostream& operator<<(std::ostream& os, BitBoard const& bb);

namespace BitBoardConstants {
    consteval std::array<BitBoard, 8> evalRows();
    consteval std::array<BitBoard, 8> evalInvRows();
    consteval std::array<BitBoard, 8> evalCols();
    consteval std::array<BitBoard, 8> evalInvCols();
}

#include <board/bitboard.impl>

namespace BitBoardConstants {
    constexpr std::array<BitBoard, 8> ROWS = evalRows();
    constexpr std::array<BitBoard, 8> INV_ROWS = evalInvRows();
    constexpr std::array<BitBoard, 8> COLS = evalCols();
    constexpr std::array<BitBoard, 8> INV_COLS = evalInvCols();
};
