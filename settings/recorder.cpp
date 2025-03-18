#include <chrono>
#include <filesystem>
#include <settings/recorder.h>
#include <settings/settings.h>
#include <iostream>

const char TAKING = 'x', QUIET = '-';

Recorder::Recorder() {
    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    if (!std::filesystem::exists("games") || !std::filesystem::is_directory("games")) {
        std::filesystem::create_directories("games");
    }

    filename = "games/" + std::to_string(seconds) + ".txt";
    file.open(filename);
    prev = Color::NONE;
    step = 0;
    default_placement = false;
}

std::ostream& operator<<(std::ostream &os, PlayerType player) {
    if (player == PlayerType::BOT) {
        os << "bot";
    } else {
        os << "user";
    }
    return os;
}

void Recorder::settings() {
    default_placement = Settings::getPlacement().empty();
    file << "Game cycle: " << Settings::getGameCycle() << std::endl;
    file << "White player: " << Settings::getWhitePlayerType() << "; ";
    file << "Black player: " << Settings::getBlackPlayerType() << std::endl;
    file << "Placement: " << (default_placement ? "default" : Settings::getPlacement()) << std::endl;
    file << "White goal: <= " << Settings::getWhiteGoal() << " black kings; ";
    file << "Black goal: <= " << Settings::getBlackGoal() << " white kings" << std::endl;
}

void Recorder::append(Move move) {
    if (move.color_from == Color::WHITE) {
        if (prev == Color::WHITE) {
            file << " ..." << std::endl;
            ++step;
            file << step << ". ";
        } else if (prev == Color::BLACK) {
            file << std::endl;
            ++step;
            file << step << ". ";
        } else if (prev == Color::NONE) {
            ++step;
            file << step << ". ";
        }
        write(move);
    } else {
        if (prev == Color::WHITE) {
            file << " ";
        } else if (prev == Color::BLACK) {
            file << std::endl;
            ++step;
            file << step << ". ... ";
        } else if (prev == Color::NONE) {
            ++step;
            file << step << ". ... ";
        }
        write(move);
    }
    prev = move.color_from;
}

void Recorder::write(Move move) {
    if (move.special == SpecialMove::EN_PASSANT) {
        write(move.figure_from);
        write(move.cell_from);
        file << TAKING;
        write(move.cell_to);
    } else if (move.special == SpecialMove::CASTLE) {
        if (default_placement) {
            if (move.cell_to % 8 == 0) {
                file << "0-0-0";
            } else {
                file << "0-0";
            }
        } else {
            file << "00_";
            write(move.cell_from);
            file << "_";
            write(move.cell_to);
        }
    } else if (move.special == SpecialMove::PAWN_LONG) {
        write(move.figure_from);
        write(move.cell_from);
        file << QUIET;
        write(move.cell_to);
    } else if (move.special == SpecialMove::NONE) {
        write(move.figure_from);
        write(move.cell_from);
        if (move.color_to == Color::NONE) {
            file << QUIET;
        } else {
            file << TAKING;
        }
        write(move.cell_to);
    } else {
        write(move.figure_from);
        write(move.cell_from);
        if (move.color_to == Color::NONE) {
            file << QUIET;
        } else {
            file << TAKING;
        }
        write(move.cell_to);
        switch (move.special) {
            case SpecialMove::PAWN_KNIGHT:
                file << 'N';
                break;
            case SpecialMove::PAWN_BISHOP:
                file << 'B';
                break;
            case SpecialMove::PAWN_ROOK:
                file << 'R';
                break;
            case SpecialMove::PAWN_QUEEN:
                file << 'Q';
                break;
            case SpecialMove::PAWN_KING:
                file << 'K';
                break;
        }
    }
}

void Recorder::write(uint8_t cell) {
    file << char('a' + cell % 8) << char('1' + cell / 8);
}

void Recorder::write(Figure figure) {
    switch (figure) {
        case Figure::KNIGHT:
            file << 'N';
            break;
        case Figure::BISHOP:
            file << 'B';
            break;
        case Figure::ROOK:
        case Figure::ROOK_MOVED:
            file << 'R';
            break;
        case Figure::QUEEN:
            file << 'Q';
            break;
        case Figure::KING:
        case Figure::KING_MOVED:
            file << 'K';
            break;
    }
}

Recorder::~Recorder() {
    file << std::endl;
    file.close();
}
