//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_UTILITIES_H
#define PIANOTILES_UTILITIES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gamemap.h"
#include "game.h"

#define PADDING 10
#define SMOOTH 100
#define ROUGH 24
#define BLACK ((SDL_Color) {0, 0, 0})
#define WHITE ((SDL_Color) {255, 255, 255})
#define RED ((SDL_Color) {255, 0, 0})
#define DARK_RED ((SDL_Color) {200, 0, 0})

static const uint32_t MAX_SIZE = 65536;

void draw_text(game_t *game, char *str, uint32_t font_size,SDL_Color colour, SDL_Rect rect);

void add_padding(beatmap beatmap, int index);

bool load_gamemap(char *address, gamemap_t *gamemap);

bool load_beatmap(beatmap beatmap, FILE *fp, uint32_t *total_rows);

int compare_scores(const void* a, const void* b);

uint32_t get_file_lines_length(FILE *fp);

#endif //PIANOTILES_UTILITIES_H
