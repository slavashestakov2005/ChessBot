#include <stdexcept>
#include <settings/settings.h>

std::string Settings::steps = "wb";
PlayerType Settings::white = PlayerType::USER, Settings::black = PlayerType::BOT;

void Settings::setSteps(std::string steps) {
    for (char c : steps) {
        if (c != 'w' && c != 'b') {
            throw std::invalid_argument("Steps string contains not w, and not b");
        }
    }
    if (steps.empty()) {
        throw std::invalid_argument("Steps string is empty");
    }
    Settings::steps = steps;
}

void Settings::setWhitePlayerType(PlayerType type) {
    Settings::white = type;
}

void Settings::setBlackPlayerType(PlayerType type) {
    Settings::black = type;
}

char Settings::player(int step) {
    return Settings::steps[step % Settings::steps.size()];
}

PlayerType Settings::getWhitePlayerType() {
    return Settings::white;
}

PlayerType Settings::getBlckPlayerType() {
    return Settings::black;
}
