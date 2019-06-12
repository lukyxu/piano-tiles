//
// Created by kx3418 on 11/06/19.
//

#ifndef PIANO_TILES_GAME_H
#define PIANO_TILES_GAME_H

#include "stdbool.h"
#include "SDL2/SDL.h"
#include "beatmap.h"

#define window_width 600
#define window_height 974
#define row_padding 2
#define col_padding 2
#define row_tile_amount 4
#define col_tile_amount 6
#define tile_width ((window_width - (row_tile_amount + 1)*row_padding)/row_tile_amount)
#define tile_height ((window_height - (col_tile_amount + 1)*col_padding)/col_tile_amount)
#define FPS 60
#define frame_delay  (1000 / FPS)
typedef enum GameStatus {
    PLAYING,
    GAME_WON,
    GAME_LOST,
    INVALID
} gamestatus_t;

typedef struct game {
    bool is_running;
    gamestatus_t gamestatus;
    bool paused;
    uint32_t elapsed_beat_time;
    SDL_Window *window;
    SDL_Renderer *renderer;
    beatmap map;
    SDL_Event event;
} game_t;

void init(game_t *game, const char* title, int xpos, int ypos, int width, int height);

void init_beatmap(game_t *game, beatmap map);

void handle_game_events(game_t *game);
void update_game(game_t *game);
void render_game(game_t *game);
void delete_game(game_t *game);
#endif //PIANO_TILES_GAME_H
