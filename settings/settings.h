#pragma once
#include <string>

enum class PlayerType {
    USER,
    BOT,
};

class Settings {
    static std::string steps;
    static PlayerType white, black;
    static std::string placement;
    static int white_goal, black_goal;
public:
    static void setPreAndPeriod(std::string preperiod, std::string period);
    static void setProb(double prob);
    static void setSteps(std::string steps);
    static void setWhitePlayerType(PlayerType type);
    static void setBlackPlayerType(PlayerType type);
    static void setPlacement(std::string placement);
    static void setWhiteGoal(int goal);
    static void setBlackGoal(int goal);

    static char player(int step);
    static std::string getGameCycle();
    static PlayerType getWhitePlayerType();
    static PlayerType getBlackPlayerType();
    static std::string getPlacement();
    static int getWhiteGoal();
    static int getBlackGoal();
};
