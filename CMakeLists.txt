cmake_minimum_required(VERSION 3.12)
project(piano_tiles C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(piano_tiles
        gamemap.h
        main.c
        utilities.c
        utilities.h game.c game.h stack.c stack.h menus.c menus.h)

target_link_libraries(piano_tiles ncurses)

target_link_libraries(piano_tiles SDL2main SDL2 SDL2_test SDL2_ttf SDL2_mixer)