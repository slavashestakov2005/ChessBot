#include <bot/bot.h>
#include <bot/legal_moves.h>
#include <figures/pseudo_moves.h>
#include <settings/settings.h>
#include <ui/storage.h>
#include <ui/ui.h>

AsyncSearcher::AsyncSearcher() {
    start_search = false;
    finish_search = false;
}

void AsyncSearcher::find(Position const& position, Color player) {
    start_search = true;
    if (player != position.currentPlayer()) {
        throw std::invalid_argument("Unexpected player color for async searcher");
    }
    thr = std::thread([position, player, this](){
        best_move = Bot::getBestMove(position);
        finish_search = true;
    });
}

bool AsyncSearcher::is_started() const {
    return start_search;
}

bool AsyncSearcher::is_finished() const {
    return finish_search;
}

Move AsyncSearcher::getMove() {
    thr.join();
    start_search = false;
    finish_search = false;
    return best_move;
}

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
    Storage::addFont("font", "fonts/HSESans-Regular.otf");

    window.create(sf::VideoMode(800, 600), "", sf::Style::Default);
    window.setFramerateLimit(20);

    try {
        Board board;
        board.placement(Settings::getPlacement());
        position = Position(board);
    } catch (std::invalid_argument &ex) {
        position = Position();
    }
    buff = sf::Vector2i(INT32_MAX, INT32_MAX);
    status = GameStatus::UNKNOWN;
    recorder.settings();
}

std::pair<bool, Move> UI::readUserStep(Color our, Color opponent) {
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
    if (cell == sf::Vector2i(INT32_MAX, INT32_MAX)) {   // no step
        return {false, {}};
    }
    if (buff == sf::Vector2i(INT32_MAX, INT32_MAX)) {   // step from
        buff = cell;
        return {false, {}};
    }
    if (cell == buff) {                                 // from = to
        buff = sf::Vector2i(INT32_MAX, INT32_MAX);
        sound.setBuffer(*Storage::getSound("move"));
        sound.play();
        return {false, {}};
    }
    bool castle = position.getBoard().getFigureBitBoard(our, Figure::KING).getBit(buff.y * 8 + buff.x) &&
                  position.getBoard().getFigureBitBoard(our, Figure::ROOK).getBit(cell.y * 8 + cell.x);
    if (!castle && position.getBoard().getColorBitBoard(our).getBit(cell.y * 8 + cell.x)) {     // change from
        buff = cell;
        sound.setBuffer(*Storage::getSound("move"));
        sound.play();
        return {false, {}};
    }

    SpecialMove pawn_transform;
    if ((float)mouse.y - getCellPosition(cell.x, cell.y).y < getCellSize().y / 2) {
        if ((float)mouse.x - getCellPosition(cell.x, cell.y).x < getCellSize().x * 0.33f) {
            pawn_transform = SpecialMove::PAWN_KNIGHT;
        }
        else if ((float)mouse.x - getCellPosition(cell.x, cell.y).x < getCellSize().x * 0.67f) {
            pawn_transform = SpecialMove::PAWN_BISHOP;
        } else {
            pawn_transform = SpecialMove::PAWN_ROOK;
        }
    } else {
        if ((float)mouse.x - getCellPosition(cell.x, cell.y).x < getCellSize().x / 2) {
            pawn_transform = SpecialMove::PAWN_QUEEN;
        }
        else {
            pawn_transform = SpecialMove::PAWN_KING;
        }
    }
    
    Moves moves = LegalMoves::generate(position, our);
    for (int32_t i = 0; i < moves.size(); ++i) {
        Move move = moves[i];
        if (move.cell_from == buff.y * 8 + buff.x && move.cell_to == cell.y * 8 + cell.x && (move.special == pawn_transform ||
            (move.special != SpecialMove::PAWN_KNIGHT && move.special != SpecialMove::PAWN_BISHOP &&
             move.special != SpecialMove::PAWN_ROOK && move.special != SpecialMove::PAWN_QUEEN))) {
            return {true, move};
        }
    }
    return {false, {}};
}

bool UI::apply_move(Move move) {
    status = GameStatus::UNKNOWN;
    position.move(move);
    recorder.append(move);
    update();
    sound.setBuffer(*Storage::getSound("move"));
    sound.play();
    if (move.figure_to != Figure::NONE && move.special != SpecialMove::CASTLE || move.special == SpecialMove::EN_PASSANT) {
        sound.setBuffer(*Storage::getSound("capture"));
        sound.play();
    }
    if (getStatus() == GameStatus::WHITE_WON || getStatus() == GameStatus::DRAW || getStatus() == GameStatus::BLACK_WON) {
        sound.setBuffer(*Storage::getSound("message"));
        sound.play();
        return false;
    }
    return true;
}

bool UI::ui_loop() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return false;
        }
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, (float) window.getSize().x, (float) window.getSize().y);
            window.setView(sf::View(visibleArea));
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (getStatus() == GameStatus::WHITE_TO_MOVE && Settings::getWhitePlayerType() == PlayerType::USER) {
                auto [state, move] = readUserStep(Color::WHITE, Color::BLACK);
                if (!state) {
                    continue;
                }
                buff = sf::Vector2i(INT32_MAX, INT32_MAX);
                apply_move(move);
            }
            if (getStatus() == GameStatus::BLACK_TO_MOVE && Settings::getBlackPlayerType() == PlayerType::USER) {
                auto [state, move] = readUserStep(Color::BLACK, Color::WHITE);
                if (!state) {
                    continue;
                }
                buff = sf::Vector2i(INT32_MAX, INT32_MAX);
                apply_move(move);
            }
        }
    }
    if (Settings::getWhitePlayerType() == PlayerType::BOT && getStatus() == GameStatus::WHITE_TO_MOVE) {
        if (!searcher.is_started()) {
            searcher.find(position, Color::WHITE);
        } else if (searcher.is_finished()) {
            apply_move(searcher.getMove());
        }
    }
    if (Settings::getBlackPlayerType() == PlayerType::BOT && getStatus() == GameStatus::BLACK_TO_MOVE) {
        if (!searcher.is_started()) {
            searcher.find(position, Color::BLACK);
        } else if (searcher.is_finished()) {
            apply_move(searcher.getMove());
        }
    }
    return true;
}

void UI::start() {
    while (ui_loop()) {
        update();
    }
}

void UI::update() {
    window.clear(sf::Color(22, 21, 18));
    drawCells();
    drawPieces();
    drawSelectedPieceMoves();
    drawNextPlayers();
    drawText();
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

    if (status == GameStatus::UNKNOWN) getStatus();

    for (int32_t i = 0; i < selected.size(); i = i + 1) {
        if (selected[i].cell_from == buff.y * 8 + buff.x) {
            uint8_t x = selected[i].cell_to % 8;
            uint8_t y = selected[i].cell_to / 8;
            if (selected[i].figure_from == Figure::PAWN && (y == 0 || y == 7)) {
                sf::Sprite sprite;
                sprite.setTexture(*Storage::getTexture(side + "Knight"));
                sprite.setScale(getCellSize().x / sprite.getLocalBounds().width * 0.33f, getCellSize().y / sprite.getLocalBounds().height * 0.33f);
                sprite.setColor(sf::Color(255, 255, 255, 63));

                sprite.setPosition(getCellPosition(x, y));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Bishop"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x + getCellSize().x * 0.33, getCellPosition(x, y).y));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Rook"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x + getCellSize().x * 0.67, getCellPosition(x, y).y));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "Queen"));
                sprite.setScale(getCellSize().x / sprite.getLocalBounds().width * 0.5f, getCellSize().y / sprite.getLocalBounds().height * 0.5f);
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x, getCellPosition(x, y).y + getCellSize().y / 2));
                window.draw(sprite);

                sprite.setTexture(*Storage::getTexture(side + "King"));
                sprite.setPosition(sf::Vector2f(getCellPosition(x, y).x + getCellSize().x * 0.5f, getCellPosition(x, y).y + getCellSize().y / 2));
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

void UI::drawNextPlayers() {
    sf::Vector2f box = getCellSize();
    sf::Vector2f pos = getCellPosition(0, 8);
    float part = box.x * 0.25;
    pos.y -= part;
    {
        sf::CircleShape cell;
        cell.setRadius(box.x / 2);
        cell.setPosition(pos);
        cell.setFillColor(sf::Color(15, 165, 58));
        window.draw(cell);
    }
    box.x = 2 * part;
    box.y = 2 * part;
    pos.x += part;
    pos.y += part;
    for (int32_t i = 0; i < 8; ++i) {
        char player = Settings::player(position.getStep() + i);
        sf::CircleShape cell;
        cell.setRadius(box.x / 2);
        cell.setPosition(pos);
        if (player == 'b') {
            cell.setFillColor(sf::Color(139, 105, 76));
        } else {
            cell.setFillColor(sf::Color(240, 232, 192));
        }
        window.draw(cell);
        pos.x += box.x + 2 * part;
    }
}

#include <iostream>

void UI::drawText() {
    // sf::Text text(L"СМЕШНОЙ шрифт", *Storage::getFont("font"), 20);
    // text.setColor(sf::Color::Red
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    // text.setPosition(0, 0);
    sf::Vector2f box = getCellSize();
    float width = box.x * 4;
    float height = box.x;
    drawText(getCellPosition(-4, 8), {width, height}, sf::Text(L"Ходы:", *Storage::getFont("font")));
    std::vector<std::string> const& lines = recorder.getBuffer();
    int start = lines.size() - 8;
    if (start < 0) {
        start = 0;
    }
    for (int pos = start; pos < lines.size(); ++pos) {
        drawText(getCellPosition(-4, start - pos + 7), {width, height}, sf::Text(lines[pos], *Storage::getFont("font")));
    }
}

void UI::drawText(sf::Vector2f pos, sf::Vector2f box, sf::Text text) {
    sf::FloatRect bound = text.getLocalBounds();
    float scale = std::min(box.x / bound.width, box.y / bound.width);
    // text.setScale(scale, scale);
    // bound = text.getLocalBounds();
    // text.setPosition(pos.x + (box.x - bound.width) / 2, pos.y + (box.y - bound.height) / 2);
    text.setPosition(pos);
    window.draw(text);
}

void UI::updateWindowTitle() {
    GameStatus status = getStatus();
    switch (status) {
        case GameStatus::WHITE_TO_MOVE:
            if (Settings::getWhitePlayerType() == PlayerType::USER) {
                window.setTitle(L"Ваш ход за белых");
            } else {
                window.setTitle(L"Бот думает за белых...");
            }
            break;
        case GameStatus::BLACK_TO_MOVE:
            if (Settings::getBlackPlayerType() == PlayerType::USER) {
                window.setTitle(L"Ваш ход за чёрных");
            } else {
                window.setTitle(L"Бот думает за чёрных...");
            }
            break;
        case GameStatus::WHITE_WON:
            window.setTitle(L"Белые победили");
            break;
        case GameStatus::BLACK_WON:
            window.setTitle(L"Чёрные победили");
            break;
        case GameStatus::DRAW:
            window.setTitle(L"Ничья");
            break;
    }
}

sf::Vector2f UI::getCellSize() {
    uint32_t width = (window.getSize().x - 2 * BOARD_MARGIN) / 12;
    uint32_t height = (window.getSize().y - 2 * BOARD_MARGIN) / 9;
    uint32_t side = std::min(width, height);
    return {(float) side, (float) side};
}

sf::Vector2f UI::getCellPosition(int32_t x, int32_t y) {
    sf::Vector2f cell = getCellSize();
    return {window.getSize().x - cell.x * 8 - BOARD_MARGIN + cell.x * (float)(x + 1 - 1),
            window.getSize().y - BOARD_MARGIN - cell.y * (float)(y + 1)};
}

GameStatus UI::getStatus() {
    if (status != GameStatus::UNKNOWN) return status;
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
        return status = GameStatus::DRAW;
    }

    if (position.isWhiteWon()) return status = GameStatus::WHITE_WON;
    if (position.isBlackWon()) return status = GameStatus::BLACK_WON;

    if (position.currentPlayer() == Color::BLACK) {
        selected = LegalMoves::generate(position, Color::BLACK);
        if (selected.size() == 0) return status = GameStatus::DRAW;
        return status = GameStatus::BLACK_TO_MOVE;
    } else {
        selected = LegalMoves::generate(position, Color::WHITE);
        if (selected.size() == 0) return status = GameStatus::DRAW;
        return status = GameStatus::WHITE_TO_MOVE;
    }
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
