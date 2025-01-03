#include <ui/ui.h>
#include <bot/bot.h>
#include <bot/legal_moves.h>
#include <figures/pseudo_moves.h>
#include <ui/storage.h>

int32_t UI::BOARD_MARGIN = 20;

UI::UI() {
    Storage::setRoot("../data");
    Storage::addTexture("logotype", "images/logotype.png");
    Storage::addTexture("whitePawn", "images/chessmen/white/pawn.png");
    Storage::addTexture("whiteKnight", "images/chessmen/white/knight.png");
    Storage::addTexture("whiteBishop", "images/chessmen/white/bishop.png");
    Storage::addTexture("whiteRook", "images/chessmen/white/rook.png");
    Storage::addTexture("whiteQueen", "images/chessmen/white/queen.png");
    Storage::addTexture("whiteKing", "images/chessmen/white/king.png");
    Storage::addTexture("blackPawn", "images/chessmen/black/pawn.png");
    Storage::addTexture("blackKnight", "images/chessmen/black/knight.png");
    Storage::addTexture("blackBishop", "images/chessmen/black/bishop.png");
    Storage::addTexture("blackRook", "images/chessmen/black/rook.png");
    Storage::addTexture("blackQueen", "images/chessmen/black/queen.png");
    Storage::addTexture("blackKing", "images/chessmen/black/king.png");
    Storage::addSound("move", "sounds/move.ogg");
    Storage::addSound("capture", "sounds/capture.ogg");
    Storage::addSound("message", "sounds/message.ogg");

    window.create(sf::VideoMode(600, 600), "", sf::Style::Default);
    window.setFramerateLimit(20);

    position = Position();
    buff = sf::Vector2i(INT32_MAX, INT32_MAX);
}

void UI::start() {
    sf::Sound sound;
    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return;
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, (float) window.getSize().x, (float) window.getSize().y);
                window.setView(sf::View(visibleArea));
            }
            else if (event.type == sf::Event::MouseButtonPressed && getStatus() == GameStatus::WHITE_TO_MOVE) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::Vector2i cell = sf::Vector2i(INT32_MAX, INT32_MAX);
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        int32_t cx = getCellPosition(x, y).x, cy = getCellPosition(x, y).y;
                        int32_t cx2 = cx + getCellSize().x, cy2 = cy + getCellSize().y;
                        if (mouse.x > cx && mouse.y > cy && mouse.x < cx2 && mouse.y < cy2) {
                            cell = sf::Vector2i(x, y);
                        }
                    }
                }
                if (cell != sf::Vector2i(INT32_MAX, INT32_MAX)) {
                    SpecialMove special;
                    if ((float)mouse.x - getCellPosition(cell.x, cell.y).x < getCellSize().x / 2) {
                        if ((float)mouse.y - getCellPosition(cell.x, cell.y).y < getCellSize().y / 2) {
                            special = SpecialMove::PAWN_KNIGHT;
                        }
                        else {
                            special = SpecialMove::PAWN_BISHOP;
                        }
                    }
                    else {
                        if ((float)mouse.y - getCellPosition(cell.x, cell.y).y < getCellSize().y / 2) {
                            special = SpecialMove::PAWN_ROOK;
                        }
                        else {
                            special = SpecialMove::PAWN_QUEEN;
                        }
                    }
                    if (cell == buff) {
                        buff = sf::Vector2i(INT32_MAX, INT32_MAX);
                        sound.setBuffer(*Storage::getSound("move"));
                        sound.play();
                    }
                    else if (position.getBoard().getColorBitBoard(Color::WHITE).getBit(cell.y * 8 + cell.x)) {
                        buff = cell;
                        sound.setBuffer(*Storage::getSound("move"));
                        sound.play();
                    }
                    else {
                        Moves moves = LegalMoves::generate(position, Color::WHITE);
                        int32_t moveId = -1;
                        for (int32_t i = 0; i < moves.size(); ++i) {
                            Move move = moves[i];
                            if (move.cell_from == buff.y * 8 + buff.x && move.cell_to == cell.y * 8 + cell.x && (special == moves[i].special ||
                                (moves[i].special != SpecialMove::PAWN_KNIGHT && moves[i].special != SpecialMove::PAWN_BISHOP &&
                                 moves[i].special != SpecialMove::PAWN_ROOK && moves[i].special != SpecialMove::PAWN_QUEEN))) {
                                moveId = i;
                                break;
                            }
                        }
                        buff = sf::Vector2i(INT32_MAX, INT32_MAX);
                        if (moveId != -1) {
                            position.move(moves[moveId]);
                            sound.setBuffer(*Storage::getSound("move"));
                            sound.play();
                            if (moves[moveId].figure_to != Figure::NONE || moves[moveId].special == SpecialMove::EN_PASSANT) {
                                sound.setBuffer(*Storage::getSound("capture"));
                                sound.play();
                            }
                            if (getStatus() == GameStatus::WHITE_WON || getStatus() == GameStatus::DRAW) {
                                sound.setBuffer(*Storage::getSound("message"));
                                sound.play();
                            }
                            else {
                                update();
                                Move move = Bot::getBestMove(position, Color::BLACK);
                                position.move(move);
                                sound.setBuffer(*Storage::getSound("move"));
                                sound.play();
                                if (move.figure_to != Figure::NONE || move.special == SpecialMove::EN_PASSANT) {
                                    sound.setBuffer(*Storage::getSound("capture"));
                                    sound.play();
                                }
                                if (getStatus() == GameStatus::BLACK_WON || getStatus() == GameStatus::DRAW) {
                                    sound.setBuffer(*Storage::getSound("message"));
                                    sound.play();
                                }
                            }
                        }
                    }
                }
            }
        }
        update();
    }
}

void UI::update() {
    window.clear(sf::Color(22, 21, 18));
    drawCells();
    drawPieces();
    drawSelectedPieceMoves();
    updateWindowTitle();
    window.display();
}

void UI::drawCells() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            sf::RectangleShape cell;
            cell.setSize(getCellSize());
            cell.setPosition(getCellPosition(x, y));
            if ((x + y) % 2 == 0) {
                cell.setFillColor(sf::Color(181, 136, 99));
            }
            else {
                cell.setFillColor(sf::Color(240, 217, 181));
            }
            window.draw(cell);
        }
    }
}

void UI::drawPieces() {
    for (int32_t x = 0; x < 8; ++x) {
        for (int32_t y = 0; y < 8; ++y) {
            sf::Sprite sprite;
            std::string name = getTextureName(x, y);
            if (name.empty()) {
                continue;
            }
            sprite.setTexture(*Storage::getTexture(name));
            sprite.setScale(getCellSize().x / sprite.getLocalBounds().width, getCellSize().y / sprite.getLocalBounds().height);
            sprite.setPosition(getCellPosition(x, y));
            if (sf::Vector2i(x, y) == buff)  {
                sf::Vector2f oldSize = sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
                sprite.setScale(sprite.getScale().x * 1.2f, sprite.getScale().y * 1.2f);
                sf::Vector2f newSize = sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
                sprite.setPosition(sprite.getPosition().x - (newSize.x - oldSize.x) / 2, sprite.getPosition().y - (newSize.y - oldSize.y) / 2);
            }
            window.draw(sprite);
        }
    }
}

void UI::drawSelectedPieceMoves() {
    if (buff == sf::Vector2i(INT32_MAX, INT32_MAX)) {
        return;
    }

    std::string name = getTextureName(buff.x, buff.y);
    if (name.empty()) {
        return;
    }
    std::string side = name.substr(0, 5);

    Moves moves;
    if (side == "white") {
        moves = LegalMoves::generate(position, Color::WHITE);
    }
    else {
        moves = LegalMoves::generate(position, Color::BLACK);
    }

    for (int32_t i = 0; i < moves.size(); i = i + 1) {
        if (moves[i].cell_from == buff.y * 8 + buff.x) {
            uint8_t x = moves[i].cell_to % 8;
            uint8_t y = moves[i].cell_to / 8;
            if (moves[i].figure_from == Figure::PAWN && (y == 0 || y == 7)) {
                sf::Sprite sprite;
                sprite.setTexture(*Storage::getTexture(side + "Knight"));
                sprite.setScale(getCellSize().x / sprite.getLocalBounds().width * 0.5f, getCellSize().y / sprite.getLocalBounds().height * 0.5f);
                sprite.setColor(sf::Color(255, 255, 255, 63));

                sprite.setPosition(getCellPosition(x, y));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Bishop"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x, getCellPosition(x, y).y + getCellSize().y / 2));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Rook"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x + getCellSize().x / 2, getCellPosition(x, y).y));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Queen"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x + getCellSize().x / 2, getCellPosition(x, y).y + getCellSize().y / 2));
                window.draw(sprite);
            }
            else {
                sf::Sprite sprite;
                sprite.setTexture(*Storage::getTexture(name));
                sprite.setScale(getCellSize().x / sprite.getLocalBounds().width, getCellSize().y / sprite.getLocalBounds().height);
                sprite.setPosition(getCellPosition(x, y));
                sprite.setColor(sf::Color(255, 255, 255, 63));
                window.draw(sprite);
            }
        }
    }
}

void UI::updateWindowTitle() {
    GameStatus status = getStatus();
    switch (status) {
        case GameStatus::WHITE_TO_MOVE:
            window.setTitle(L"Ваш ход");
            break;
        case GameStatus::BLACK_TO_MOVE:
            window.setTitle(L"Бот думает...");
            break;
        case GameStatus::WHITE_WON:
            window.setTitle(L"Вы победили");
            break;
        case GameStatus::BLACK_WON:
            window.setTitle(L"Бот победил");
            break;
        case GameStatus::DRAW:
            window.setTitle(L"Ничья");
            break;
    }
}

sf::Vector2f UI::getCellSize() {
    uint32_t side = (std::min(window.getSize().x, window.getSize().y) - 2 * BOARD_MARGIN) / 8;
    return {(float)side, (float)side};
}

sf::Vector2f UI::getCellPosition(int32_t x, int32_t y) {
    sf::Vector2f size = getCellSize();
    return {BOARD_MARGIN + size.x * (float)x, (float)window.getSize().y - BOARD_MARGIN - size.y * (float)(y + 1)};
}

GameStatus UI::getStatus() {
    // if (position.fiftyMovesRuleDraw() || position.threefoldRepetitionDraw()) {
    //     return GameStatus::DRAW;
    // }

    if (!position.getBoard().getFigureBitBoard(Color::WHITE, Figure::PAWN) &&
        !position.getBoard().getFigureBitBoard(Color::BLACK, Figure::PAWN) &&
        !position.getBoard().getFigureBitBoard(Color::WHITE, Figure::ROOK) &&
        !position.getBoard().getFigureBitBoard(Color::BLACK, Figure::ROOK) &&
        !position.getBoard().getFigureBitBoard(Color::WHITE, Figure::QUEEN) &&
        !position.getBoard().getFigureBitBoard(Color::BLACK, Figure::QUEEN) &&
        !position.getBoard().getFigureBitBoard(Color::WHITE, Figure::ROOK_MOVED) && 
        !position.getBoard().getFigureBitBoard(Color::BLACK, Figure::ROOK_MOVED) && 
        (position.getBoard().getFigureBitBoard(Color::WHITE, Figure::KNIGHT) |
         position.getBoard().getFigureBitBoard(Color::WHITE, Figure::BISHOP)).ones() < 2 &&
        (position.getBoard().getFigureBitBoard(Color::BLACK, Figure::KNIGHT) |
         position.getBoard().getFigureBitBoard(Color::BLACK, Figure::BISHOP)).ones() < 2) {
        return GameStatus::DRAW;
    }

    if (position.currentPlayer() == Color::BLACK) {
        Moves moves = LegalMoves::generate(position, Color::BLACK);
        if (moves.size() == 0) {
            if (PseudoMoves::isBitten(position.getBoard(), position.getBoard().getFigureBitBoard(Color::BLACK, Figure::KING).getLow1(), Color::BLACK)) {
                return GameStatus::WHITE_WON;
            }
            return GameStatus::DRAW;
        }
        return GameStatus::BLACK_TO_MOVE;
    }

    Moves moves = LegalMoves::generate(position, Color::WHITE);
    if (moves.size() == 0) {
        if (PseudoMoves::isBitten(position.getBoard(), position.getBoard().getFigureBitBoard(Color::WHITE, Figure::KING).getLow1(), Color::WHITE)) {
            return GameStatus::BLACK_WON;
        }
        return GameStatus::DRAW;
    }
    return GameStatus::WHITE_TO_MOVE;
}

std::string UI::getTextureName(int32_t x, int32_t y) const {
    int32_t id = y * 8 + x;
    std::array<std::array<BitBoard, 8>, 2> bs = position.getBoard().getAllFigures();
    if (bs[(int) Color::WHITE][(int) Figure::PAWN].getBit(id)) return "whitePawn";
    if (bs[(int) Color::WHITE][(int) Figure::KNIGHT].getBit(id)) return "whiteKnight";
    if (bs[(int) Color::WHITE][(int) Figure::BISHOP].getBit(id)) return "whiteBishop";
    if (bs[(int) Color::WHITE][(int) Figure::ROOK].getBit(id)) return "whiteRook";
    if (bs[(int) Color::WHITE][(int) Figure::QUEEN].getBit(id)) return "whiteQueen";
    if (bs[(int) Color::WHITE][(int) Figure::KING].getBit(id)) return "whiteKing";
    if (bs[(int) Color::WHITE][(int) Figure::ROOK_MOVED].getBit(id)) return "whiteRook";
    if (bs[(int) Color::WHITE][(int) Figure::KING_MOVED].getBit(id)) return "whiteKing";
    if (bs[(int) Color::BLACK][(int) Figure::PAWN].getBit(id)) return "blackPawn";
    if (bs[(int) Color::BLACK][(int) Figure::KNIGHT].getBit(id)) return "blackKnight";
    if (bs[(int) Color::BLACK][(int) Figure::BISHOP].getBit(id)) return "blackBishop";
    if (bs[(int) Color::BLACK][(int) Figure::ROOK].getBit(id)) return "blackRook";
    if (bs[(int) Color::BLACK][(int) Figure::QUEEN].getBit(id)) return "blackQueen";
    if (bs[(int) Color::BLACK][(int) Figure::KING].getBit(id)) return "blackKing";
    if (bs[(int) Color::BLACK][(int) Figure::ROOK_MOVED].getBit(id)) return "blackRook";
    if (bs[(int) Color::BLACK][(int) Figure::KING_MOVED].getBit(id)) return "blackKing";
    return "";
}
