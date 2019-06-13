#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "utilities.h"
#include "game.h"
#include "stack.h"
#include "menus.h"


void game_loop(game_t *game) {
    uint32_t frame_start = SDL_GetTicks();

//    handle_game_events(game);
    update_game(game);
    render_game(game);

    uint32_t frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time) {
        SDL_Delay(frame_delay - frame_time);
    }
    if (game->gamestatus == PLAYING) {
        game->map->elapsed_beat_time += frame_delay;
    }
}

void main_menu_loop(game_t *game) {
    update_main_menu(game);
    render_main_menu(game);
}

void leaderboard_loop(game_t *game){
    update_leaderboard(game);
    render_leaderboard(game);
};

int main(int argc, char *argv[]) {
    gamemap_t *gamemap = malloc(sizeof(gamemap_t));
    game_t *game = malloc(sizeof(game_t));
    game->menu_stack = malloc(sizeof(stack));
    *(game->menu_stack) = NULL;
    push(game->menu_stack, MAIN_MENU);
    game->loaded_beatmap = false;

    init_sdl_window(game, "Piano Tiles", 0, 0, window_width, window_height);
    while (game->is_running) {
        //initialize gamemap
        if (!game->loaded_beatmap) {
            load_gamemap(argv[1], gamemap);
            init_game(game, gamemap);
            game->loaded_beatmap = true;
        }

        game_loop(game);

        if (!stack_empty(*game->menu_stack)) {
            switch (peek(*game->menu_stack)) {
                case MAIN_MENU:
                    main_menu_loop(game);
                    break;
                case LEADER_BOARD:
                    leaderboard_loop(game);
                    break;
                default:
                    break;
            }
            SDL_RenderPresent(game->renderer);
            continue;
        }else{
            SDL_RenderPresent(game->renderer);
        }

        if (game->gamestatus == GAME_WON || game->gamestatus == GAME_LOST) {
            game->gamestatus = PAUSED;
            push(game->menu_stack, LEADER_BOARD);
            SDL_Log("Game Over");
            SDL_Delay(1000);
        }

    }
    delete_game(game);
    free(game);
}