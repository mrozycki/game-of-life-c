cmake_minimum_required(VERSION 3.10)

project(AdventCodendar)

set(CMAKE_CC_FLAGS_DEBUG "-g")
set(CMAKE_CC_FLAGS_RELEASE "-O3")

add_executable(gol main.c game_of_life.c canvas.c)