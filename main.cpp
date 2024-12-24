#include <iostream>
#include <tests/tests.h>

int main() {
    std::cout << "Chess Bot\n";
    test_default_placement();
    test_steps_from_default_placement();
    return 0;
}
