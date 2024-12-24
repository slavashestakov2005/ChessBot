cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

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
)

set(SOURCE_FIGURES
    figures/pseudo_moves.cpp
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
