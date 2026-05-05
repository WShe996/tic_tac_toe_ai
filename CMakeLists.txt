cmake_minimum_required(VERSION 3.16)
project(tic_tac_toe_ai LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tic_tac_toe_ai
    src/main.cpp
    src/node.cpp
    src/hidden_layer.cpp
    src/neural_network.cpp
    src/game_board.cpp
)

target_include_directories(tic_tac_toe_ai PRIVATE include)
