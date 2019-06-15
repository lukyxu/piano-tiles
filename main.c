#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "utilities.h"
#include "game.h"
#include "stack.h"
#include "menus.h"

void init_game(game_t *game) {
    game->menu_stack = malloc(sizeof(stack));
    *(game->menu_stack) = NULL;
    push(game->menu_stack, MAIN_MENU);
    game->loaded_beatmap = false;
    game->audio = malloc(sizeof(audio_files_t));
}

void game_loop(game_t *game) {
    uint32_t frame_start = SDL_GetTicks();
    if (stack_empty(*game->menu_stack)){
        update_game(game);
    }
    draw_game(game);

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
    draw_main_menu(game);
}

void leaderboard_loop(game_t *game){
    draw_leaderboard(game);
    SDL_RenderPresent(game->renderer);
    // Loops until a valid input is received
    while (!update_leaderboard(game));
};

int main(int argc, char *argv[]) {
    gamemap_t *gamemap = malloc(sizeof(gamemap_t));
    game_t *game = malloc(sizeof(game_t));
    init_game(game);
    if (argc != 2){
        printf("First argument should be beatmap file");
    }
    init_sdl_window(game, "Piano Tiles", 0, 0, window_width, window_height);

    while (game->is_running) {
        if (!game->loaded_beatmap) {
            // Initializes gamemap
            load_gamemap(argv[1], gamemap);
            init_gamemap(game, gamemap);
            load_audio(game);
            game->loaded_beatmap = true;
        }

        game_loop(game);

        if (!stack_empty(*game->menu_stack)) {
            // Overlays menu on game if a menu is on the menu stack
            Mix_HaltMusic();
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
        }

        SDL_RenderPresent(game->renderer);

        // Stack is empty so game is in progress or over
        if (game->gamestatus == GAME_WON || game->gamestatus == GAME_LOST) {
            // Game is won/lost
            game->gamestatus = PAUSED;
            game->game_time_tracker = (SDL_GetTicks() - game->game_time_tracker);
            add_leaderboard(game);
            push(game->menu_stack, LEADER_BOARD);
            SDL_Log("Game Over");
            SDL_Delay(1000);
            while(SDL_PollEvent(&game->event));
        }
    }
    // Game is over
    free_audio(game);
    delete_game(game);
    return EXIT_SUCCESS;
}


