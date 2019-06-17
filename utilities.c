//
// Created by yiz18 on 06/06/19.
//

#include "utilities.h"

#include <stdlib.h>
#include <string.h>


void draw_text(game_t *game, char *str, uint32_t font_size, SDL_Color colour, SDL_Rect rect){
    static TTF_Font *font = NULL;
    if (!font){
         font =  TTF_OpenFont("Sans.ttf", font_size);
    }
    SDL_Surface *surface_message = TTF_RenderText_Solid(font, str, colour);
    SDL_Texture *message = SDL_CreateTextureFromSurface(game->renderer, surface_message);
    SDL_RenderCopy(game->renderer, message, NULL, &rect);
    SDL_DestroyTexture(message);
    SDL_FreeSurface(surface_message);
}

void add_padding(beatmap beatmap, int index) {
    for (int i = 1; i < PADDING; ++i) {
        beatmap[index + i] = calloc(4, sizeof(tile_t));
    }
}

// Returns true iff the gamemap is loaded sucessfully
bool load_gamemap(char *address, gamemap_t *gamemap) {
    FILE *fp = fopen(address, "r");
    if (fp == NULL){
        SDL_Log("Could not open leaderboard");
        exit(EXIT_FAILURE);
    }
    char buffer[20];
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        char *rest;
        char *token = strtok_r(buffer, ": \n", &rest);
        if (token == NULL){
            continue;
        }
        if (!strcmp(token, "accel")){
            gamemap->tiles_acceleration = strtod(strtok_r(NULL, "= ", &rest), NULL);
        }else if (!strcmp(token, "speed")){
            set_tiles_speed(gamemap, strtod(strtok_r(NULL, "= ", &rest), NULL));
        }
        else if (!strcmp(token, "--BEGIN-GAME--")){
            break;
        }else{
            SDL_Log("Invalid input for bin file");
            exit(EXIT_FAILURE);
        }
    }

    beatmap beatmap = calloc(MAX_SIZE, sizeof(row));
    if (!load_beatmap(beatmap, fp, &gamemap->total_beats)){
        SDL_Log("Could not load beatmap");
        exit(EXIT_FAILURE);
    }

    fclose(fp);
    gamemap->completed_rows = 0;
    gamemap->elapsed_beat_time = 0;
    gamemap->current_row = 0;
    set_tile_period(gamemap);
    gamemap->beatmap = beatmap;
    return true;
}

// Returns true iff the beatmap is loaded successfully
bool load_beatmap(beatmap beatmap, FILE *fp, uint32_t *total_rows){
    uint32_t index = 0;
    while(true){
        beatmap[index] = calloc(4, sizeof(tile_t));
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
                *total_rows = index;
                // Add padding to allow indexes to be read after the game end
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

int compare_desc_scores(const void *a, const void *b)
{
    return strtod(a,NULL) < strtod(b,NULL);
}

int compare_asc_scores(const void *a, const void *b)
{
    return strtod(a,NULL) > strtod(b,NULL);
}

uint32_t get_file_lines_length(FILE *fp){
    fseek ( fp , 0 , SEEK_SET );
    uint32_t output = 0;
    int chr;
    while((chr = getc(fp)) != EOF){
        if (chr == '\n'){
            output ++;
        }
    }
    fseek ( fp , 0 , SEEK_SET);
    return output;
}