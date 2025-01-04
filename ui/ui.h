#pragma once
#include <board/position.h>
#include <bot/moves.h>
#include <cstdint>
#include <SFML/Graphics.hpp>

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

    static int32_t BOARD_MARGIN;

    void update();
    void drawCells();
    void drawPieces();
    void drawSelectedPieceMoves();
    void updateWindowTitle();

    sf::Vector2f getCellSize();
    sf::Vector2f getCellPosition(int32_t x, int32_t y);
    GameStatus getStatus();
    std::string getTextureName(int32_t x, int32_t y) const;
};
