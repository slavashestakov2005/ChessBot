#include <iostream>
#include <settings/settings.h>
#include <ui/ui.h>

void hello() {
    std::cout << "===== Sophisticated Queue Chess Bot! =====" << std::endl << std::endl;
}

void get_steps_cycle() {
    std::cout << std::endl;
    while (true) {
        std::cout << "Input steps queue cycle:" << std::endl;
        std::cout << "1) w or b without other symbols" << std::endl;
        std::cout << "2) p=<float> () for randomized queue with Prob(w)=p, Prob(b)=1-p)" << std::endl;
        std::cout << "3) w or b with parens, '<pre-period>(<period>): ";
        std::string steps;
        std::cin >> steps;
        try {
            if (steps.size() >= 2 && steps[0] == 'p' && steps[1] == '=') {
                std::string prob;
                for (int i = 2; i < steps.size(); ++i) {
                    prob += (steps[i] == ',' ? '.' : steps[i]);
                }
                Settings::setProb(stod(prob));
            } else if (steps.find('(') != std::string::npos && steps[steps.size() - 1] == ')') {
                std::string preperiod, period;
                bool paren_was = false;
                for (char c : steps) {
                    if (!paren_was && c == '(') {
                        paren_was = true;
                    } else if (!paren_was) {
                        preperiod += c;
                    } else {
                        period += c;
                    }
                }
                period.pop_back();
                Settings::setPreAndPeriod(preperiod, period);
            } else {
                Settings::setSteps(steps);
            }
            return;
        } catch (const std::logic_error& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
}

PlayerType get_player_type(std::string whom) {
    std::cout << std::endl;
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

std::string get_placement_line(int line) {
    while (true) {
        std::cout << "Input placement for line " << line << ": ";
        std::string inp;
        std::cin >> inp;
        if (inp.size() != 8) {
            std::cout << "Error: expected line with len 8" << std::endl;
            continue;
        }
        bool ok = true;
        for (int pos = 0; pos < inp.size(); ++pos) {
            char c = tolower(inp[pos]);
            if (c != 'p' && c != 'n' && c != 'b' && c != 'r' && c != 'q' && c != 'k' && c != '-') {
                std::cout << "Error: unexpected symbol '" << inp[pos] << "' at pos " << pos + 1 << std::endl;
                ok = false;
            }
            if ((line == 1 || line == 8) && c == 'p') {
                std::cout << "Error: line can't contain pawns" << std::endl;
                ok = false;
            }
            if (c == '-') {
                inp[pos] = ' ';
            }
        }
        if (ok) {
            return inp;
        }
    }
}

int get_goal(std::string we, std::string opponent, int min_value, int max_value) {
    if (min_value == max_value) {
        std::cout << we << " won, when count of " << opponent << " kings <=: " << min_value << std::endl;
        return min_value;
    }
    std::cout << std::endl;
    while (true) {
        std::cout << we << " won, when count of " << opponent << " kings <=: ";
        int goal;
        std::cin >> goal;
        if (goal < min_value || goal > max_value) {
            std::cout << "Error: expected value from [" << min_value << "; " << max_value << "]" << std::endl;
            continue;
        }
        return goal;
    }
}

void get_placement() {
    std::cout << std::endl;
    while (true) {
        std::cout << "Use default placement (yes or no)? ";
        std::string ans;
        std::cin >> ans;
        if (ans == "yes") {
            return;
        } else if (ans == "no") {
            break;
        } else {
            std::cout << "Error: expected 'yes' or 'no'" << std::endl;
        }
    }
    std::cout << "For each line input 8 symbols: capital for white, lowercase for black, - for space" << std::endl;
    std::cout << "Figure symbols: p (pawn), n (knight), b (bishop), r (rook), q (queen), k (king)" << std::endl;
    std::cout << "Lines 1 and 8 can't contain pawns" << std::endl;
    int white_kings, black_kings;
    while (true) {
        std::string all;
        for (int line = 1; line <= 8; ++line) {
            all += get_placement_line(line);
        }
        white_kings = std::count(all.begin(), all.end(), 'K');
        black_kings = std::count(all.begin(), all.end(), 'k');
        if (white_kings < 1) {
            std::cout << "Error: white king not found" << std::endl; 
        }
        if (black_kings < 1) {
            std::cout << "Error: black king not found" << std::endl;
        }
        if (white_kings >= 1 && black_kings >= 1) {
            Settings::setPlacement(all);
            break;
        }
    }
    Settings::setWhiteGoal(get_goal("White", "black", 0, black_kings - 1));
    Settings::setBlackGoal(get_goal("Black", "white", 0, white_kings - 1));
}

void get_settings() {
    std::cout << "Input settings for game" << std::endl;
    get_steps_cycle();
    Settings::setWhitePlayerType(get_player_type("white"));
    Settings::setBlackPlayerType(get_player_type("black"));
    get_placement();
}

int main() {
    hello();
    get_settings();
    UI ui;
    ui.start();
    return 0;
}
