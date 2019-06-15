//
// Created by kx3418 on 11/06/19.
//

#ifndef PIANO_TILES_GAME_H
#define PIANO_TILES_GAME_H

#include <SDL2/SDL_mixer.h>
#include "stdbool.h"
#include "SDL2/SDL.h"
#include "gamemap.h"
#include "stack.h"
#include "menus.h"

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

#define MUS_PATH "test.wav"
#define FAIL_EFFECT_PATH "fail.wav"

#define HUNDRED_TILE_AMOUNT 100
#define SPEED_TIMER_LENGTH 30000

enum{
    SCORE_LEADERBOARD,
    SCORE_GAME
};

typedef enum GameStatus {
    PLAYING,
    PAUSED,
    GAME_WON,
    GAME_LOST,
} gamestatus_t;

typedef enum Menus{
    MAIN_MENU,
    LEADER_BOARD
}menu_t;

typedef struct audio_files{
    Mix_Music *music;
    Mix_Chunk *fail;
}audio_files_t;

typedef enum game_mode{
    CLASSIC,
    SPEED,
    RUSH,
    HUNDRED,
    TOTAL_GAME_MODES_OPTIONS
} game_mode_t;

typedef struct game {
    bool is_running;
    bool loaded_beatmap;
    uint32_t game_start_time;
    game_mode_t gamemode;
    gamestatus_t gamestatus;
    gamemap_t *map;
    stack *menu_stack;
    menu_option_t menu_pointer;
    audio_files_t *audio;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
} game_t;


void init_sdl_window(game_t *game, const char *title, int xpos, int ypos, int width, int height);
void init_gamemap(game_t *game, gamemap_t *gamemap);
void play_beat(game_t *game, uint32_t column);
bool handle_game_io(game_t *game);
void update_game(game_t *game);
void draw_score(game_t *game, SDL_Rect rect, bool flag);
void draw_game(game_t *game);
void delete_game(game_t *game);
bool load_audio(game_t *game);
void free_audio(game_t *game);
#endif //PIANO_TILES_GAME_H
