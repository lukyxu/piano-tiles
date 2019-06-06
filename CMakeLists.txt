cmake_minimum_required(VERSION 3.12)
project(PianoTiles C)

set(CMAKE_C_STANDARD 11)

add_executable(PianoTiles main.c utilities.c utilities.h beatmap.c beatmap.h)