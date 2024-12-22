#include <board/pos.h>

std::ostream& operator<<(std::ostream& os, Pos const& pos) {
    return os << char('a' + pos.x) << char('1' + pos.y);
}
