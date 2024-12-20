cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(ChessBot)
include_directories(.)

set(SOURCE_BOARD
    board/board.cpp
)

set(SOURCE_FIGURES
    figures/bishop.cpp
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
    ${SOURCE_BOARD}
    ${SOURCE_FIGURES}
    ${SOURCE_TEST}
)
