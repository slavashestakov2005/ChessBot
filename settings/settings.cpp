#include <stdexcept>
#include <settings/settings.h>

std::string Settings::steps = "wb";
PlayerType Settings::white = PlayerType::USER, Settings::black = PlayerType::BOT;
std::string Settings::placement = "";
int Settings::white_goal = 0, Settings::black_goal = 0;

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

void Settings::setPlacement(std::string placement) {
    Settings::placement = placement;
}

void Settings::setWhiteGoal(int goal) {
    Settings::white_goal = goal;
}

void Settings::setBlackGoal(int goal) {
    Settings::black_goal = goal;
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

std::string Settings::getPlacement() {
    return Settings::placement;
}

int Settings::getWhiteGoal() {
    return Settings::white_goal;
}

int Settings::getBlackGoal() {
    return Settings::black_goal;
}
