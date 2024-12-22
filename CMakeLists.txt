cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_STANDARD 20)

project(ChessBot)
include_directories(.)

set(SOURCE_BOARD
    board/board.cpp
    board/figure_type.cpp
    board/pos.cpp
)

set(SOURCE_BOT
    bot/analyzer.cpp
    bot/stepper.cpp
)

set(SOURCE_FIGURES
    figures/bishop.cpp
    figures/empty.cpp
    figures/king.cpp
    figures/knight.cpp
    figures/pawn.cpp
    figures/queen.cpp
    figures/rook.cpp
)

set(SOURCE_TEST
    tests/tests.cpp
)

add_executable(bot 
    main.cpp
    ${SOURCE_BOT}
    ${SOURCE_BOARD}
    ${SOURCE_FIGURES}
    ${SOURCE_TEST}
)
