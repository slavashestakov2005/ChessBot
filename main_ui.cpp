#include <iostream>
#include <settings/settings.h>
#include <ui/ui.h>

void hello() {
    std::cout << "===== Sophisticated Queue Chess Bot! =====" << std::endl;
}

void get_steps_cycle() {
    while (true) {
        std::cout << "Input steps queue cycle (w or b without other symbols): ";
        std::string steps;
        std::cin >> steps;
        try {
            Settings::setSteps(steps);
            return;
        } catch (const std::logic_error& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
}

PlayerType get_player_type(std::string whom) {
    while (true) {
        std::cout << "Input player type (bot or user) for " << whom << ": ";
        std::string type;
        std::cin >> type;
        if (type == "bot") {
            return PlayerType::BOT;
        } else if (type == "user") {
            return PlayerType::USER;
        } else {
            std::cout << "Error: expected 'bot' or 'user'" << std::endl;
        }
    }
}

void get_settings() {
    std::cout << "Input settings for game" << std::endl;
    get_steps_cycle();
    Settings::setWhitePlayerType(get_player_type("white"));
    Settings::setBlackPlayerType(get_player_type("black"));
}

int main() {
    hello();
    get_settings();
    UI ui;
    ui.start();
    return 0;
}
