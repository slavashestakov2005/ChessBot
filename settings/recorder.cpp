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
    output.open(filename);
    prev = Color::NONE;
    step = 0;
    default_placement = false;
}

void Recorder::settings() {
    default_placement = Settings::getPlacement().empty();
    output << "Game cycle: " << Settings::getGameCycle() << std::endl;
    output << "White player: " << Settings::getWhitePlayerType() << "; ";
    output << "Black player: " << Settings::getBlackPlayerType() << std::endl;
    output << "Placement: " << (default_placement ? "default" : Settings::getPlacement()) << std::endl;
    output << "White goal: <= " << Settings::getWhiteGoal() << " black kings; ";
    output << "Black goal: <= " << Settings::getBlackGoal() << " white kings" << std::endl;
    output.saveBuffer(true);
}

void Recorder::append(Move move) {
    if (move.color_from == Color::WHITE) {
        if (prev == Color::WHITE) {
            output << " ..." << std::endl;
            ++step;
            output << step << ". ";
        } else if (prev == Color::BLACK) {
            output << std::endl;
            ++step;
            output << step << ". ";
        } else if (prev == Color::NONE) {
            ++step;
            output << step << ". ";
        }
        write(move);
    } else {
        if (prev == Color::WHITE) {
            output << " ";
        } else if (prev == Color::BLACK) {
            output << std::endl;
            ++step;
            output << step << ". ... ";
        } else if (prev == Color::NONE) {
            ++step;
            output << step << ". ... ";
        }
        write(move);
    }
    prev = move.color_from;
}

std::vector<std::string> const& Recorder::getBuffer() const {
    return output.getBuffer();
}

void Recorder::write(Move move) {
    if (move.special == SpecialMove::EN_PASSANT) {
        write(move.figure_from);
        write(move.cell_from);
        output << TAKING;
        write(move.cell_to);
    } else if (move.special == SpecialMove::CASTLE) {
        if (default_placement) {
            if (move.cell_to % 8 == 0) {
                output << "0-0-0";
            } else {
                output << "0-0";
            }
        } else {
            output << "00_";
            write(move.cell_from);
            output << "_";
            write(move.cell_to);
        }
    } else if (move.special == SpecialMove::PAWN_LONG) {
        write(move.figure_from);
        write(move.cell_from);
        output << QUIET;
        write(move.cell_to);
    } else if (move.special == SpecialMove::NONE) {
        write(move.figure_from);
        write(move.cell_from);
        if (move.color_to == Color::NONE) {
            output << QUIET;
        } else {
            output << TAKING;
        }
        write(move.cell_to);
    } else {
        write(move.figure_from);
        write(move.cell_from);
        if (move.color_to == Color::NONE) {
            output << QUIET;
        } else {
            output << TAKING;
        }
        write(move.cell_to);
        switch (move.special) {
            case SpecialMove::PAWN_KNIGHT:
                output << 'N';
                break;
            case SpecialMove::PAWN_BISHOP:
                output << 'B';
                break;
            case SpecialMove::PAWN_ROOK:
                output << 'R';
                break;
            case SpecialMove::PAWN_QUEEN:
                output << 'Q';
                break;
            case SpecialMove::PAWN_KING:
                output << 'K';
                break;
        }
    }
}

void Recorder::write(uint8_t cell) {
    output << char('a' + cell % 8) << char('1' + cell / 8);
}

void Recorder::write(Figure figure) {
    switch (figure) {
        case Figure::KNIGHT:
            output << 'N';
            break;
        case Figure::BISHOP:
            output << 'B';
            break;
        case Figure::ROOK:
        case Figure::ROOK_MOVED:
            output << 'R';
            break;
        case Figure::QUEEN:
            output << 'Q';
            break;
        case Figure::KING:
        case Figure::KING_MOVED:
            output << 'K';
            break;
    }
}

Recorder::~Recorder() {
    output << std::endl;
}
