//
// Created by yiz18 on 06/06/19.
//

#include "utilities.h"

#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void draw_text(game_t *game, char *str, uint32_t font_size, SDL_Color colour, SDL_Rect rect){
    static TTF_Font *font = NULL;
    if (!font){
         font =  TTF_OpenFont("Sans.ttf", font_size);
    }
    SDL_Surface *surface_message = TTF_RenderText_Solid(font, str, colour);
    SDL_Texture *message = SDL_CreateTextureFromSurface(game->renderer, surface_message);
    free(surface_message);
    SDL_RenderCopy(game->renderer, message, NULL, &rect);
}

void add_padding(beatmap beatmap, int index) {
    for (int i = 1; i < PADDING; ++i) {
        beatmap[index + i] = calloc(4, sizeof(beat_t));
    }
}

bool load_gamemap(char *address, gamemap_t *gamemap) {
    FILE *fp = fopen(address, "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[20];
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        char *rest;
        char *token = strtok_r(buffer, ": \n", &rest);
        if (!strcmp(token, "accel")){
            gamemap->tiles_acceleration = strtod(strtok_r(NULL, "= ", &rest), NULL);
        }else if (!strcmp(token, "speed")){
            set_tiles_speed(gamemap, strtod(strtok_r(NULL, "= ", &rest), NULL));
        }
        else if (!strcmp(token, "--BEGIN-GAME--")){
            break;
        }else{
            exit(EXIT_FAILURE);
        }
    }

    beatmap beatmap = calloc(MAX_SIZE, sizeof(row));
    if (!load_beatmap(beatmap, fp, &gamemap->total_beats)){
        exit(EXIT_FAILURE);
    }

    fclose(fp);
    gamemap->completed_rows = 0;
    gamemap->elapsed_beat_time = 0;
    gamemap->current_row = 0;
    set_tile_period(gamemap);
    gamemap->beatmap = beatmap;
}

bool load_beatmap(beatmap beatmap, FILE *fp, uint32_t *total_beats){
    uint32_t index = 0;
    while(true){
        beatmap[index] = calloc(4, sizeof(beat_t));
        for (int i = 0; i < 4; ++i) {
            int read_char = fgetc(fp);
            if(read_char == '\n'){
                i--;
                continue;
            }
            if (read_char == '3'){
                beatmap[index][0] = 3;
                beatmap[index][1] = 3;
                beatmap[index][2] = 3;
                beatmap[index][3] = 3;
                *total_beats = index;
                add_padding(beatmap, index);
                return true;
            }
            else if(read_char == EOF || read_char < '0' || read_char > '2'){
                fclose(fp);
                return false;
            }
            beatmap[index][i] = read_char - '0';
        }
        index++;
    }
}

int compare_scores(const void* a, const void* b)
{
//    const char *ia = (const char *)a;
//    const char *ib = (const char *)b;
//    return strcmp(ia, ib);
    return strtod(a,NULL) < strtod(b,NULL);
}