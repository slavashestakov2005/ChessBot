cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

set(SFML_FOLDER "C:/Users/Public/Plugins/SFML-2.5.1")
include_directories(${SFML_FOLDER}/include)
link_directories(${SFML_FOLDER}/lib)

project(ChessBot)
include_directories(.)

set(SOURCE_BOARD
    board/bitboard.cpp
    board/board.cpp
    board/figures.cpp
    board/hash.cpp
    board/move.cpp
    board/position.cpp
)

set(SOURCE_BOT
    bot/analyzer.cpp
    bot/bot.cpp
    bot/legal_moves.cpp
    bot/moves_sorter.cpp
    bot/moves.cpp
    bot/visited_states.cpp
)

set(SOURCE_FIGURES
    figures/pseudo_moves.cpp
)

set(SOURCE_SETTINGS
    settings/recorder.cpp
    settings/settings.cpp
)

set(SOURCE_TEST
    tests/tests.cpp
)

set(SOURCE_UI
    ui/storage.cpp
    ui/ui.cpp
)

add_executable(bot 
    main.cpp
    ${SOURCE_BOT}
    ${SOURCE_BOARD}
    ${SOURCE_FIGURES}
    ${SOURCE_TEST}
    ${SOURCE_SETTINGS}
)

add_executable(bot_ui
    main_ui.cpp
    ${SOURCE_BOT}
    ${SOURCE_BOARD}
    ${SOURCE_FIGURES}
    ${SOURCE_TEST}
    ${SOURCE_SETTINGS}
    ${SOURCE_UI}
)

add_definitions(-O3)
target_link_libraries(bot_ui sfml-system sfml-window sfml-graphics sfml-audio)
