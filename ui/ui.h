#pragma once
#include <cstdint>
#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <board/position.h>
#include <bot/moves.h>
#include <settings/recorder.h>

class AsyncSearcher {
public:
    AsyncSearcher();
    ~AsyncSearcher();
    void find(Position const& position, Color player);
    bool is_started() const;
    bool is_finished() const;
    Move getMove();
private:
    bool start_search, finish_search;
    Move best_move;
    std::thread thr;
};

enum class GameStatus {
    WHITE_TO_MOVE,
    BLACK_TO_MOVE,
    WHITE_WON,
    BLACK_WON,
    DRAW,
    UNKNOWN,
};

class UI {
public:
    UI();
    void start();
private:
    sf::RenderWindow window;
    sf::Event event;
    Position position;
    sf::Vector2i buff;
    GameStatus status;
    Moves selected;
    sf::Sound sound;
    Recorder recorder;
    AsyncSearcher searcher;

    static int32_t BOARD_MARGIN;

    std::pair<bool, Move> readUserStep(Color our, Color opponent);
    bool apply_move(Move move);
    bool ui_loop();

    void update();
    void drawCells();
    void drawPieces();
    void drawSelectedPieceMoves();
    void drawNextPlayers();
    void drawText();
    void drawText(sf::Vector2f pos, sf::Vector2f box, sf::Text text);
    void updateWindowTitle();

    sf::Vector2f getCellSize();
    sf::Vector2f getCellPosition(int32_t x, int32_t y);
    GameStatus getStatus();
    std::string getTextureName(int32_t x, int32_t y) const;
};
