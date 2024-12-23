cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

project(ChessBot)
include_directories(.)

set(SOURCE_BOARD
)

set(SOURCE_BOT
)

set(SOURCE_FIGURES
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
