#include <board/bitboard.h>

std::ostream& operator<<(std::ostream& os, BitBoard const& bb) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            os << bb.getBit(i * 8 + j) << " ";
        }
        os << std::endl;
    }
    return os;
}
