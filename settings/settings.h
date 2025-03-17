#pragma once
#include <string>

enum class PlayerType {
    USER,
    BOT,
};

class Settings {
    static std::string steps;
    static PlayerType white, black;
public:
    static void setSteps(std::string steps);
    static void setWhitePlayerType(PlayerType type);
    static void setBlackPlayerType(PlayerType type);

    static char player(int step);
    static PlayerType getWhitePlayerType();
    static PlayerType getBlckPlayerType();
};
