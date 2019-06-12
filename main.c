#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "SDL2/SDL.h"
#include "game.h"
#include "stack.h"

void game_loop(game_t *game) {
    uint32_t frame_start = SDL_GetTicks();

    handle_game_events(game);
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

int main(int argc, char *argv[]) {
    gamemap_t *gamemap = malloc(sizeof(gamemap_t));
    game_t *game = malloc(sizeof(game_t));
    game->menu_stack = malloc(sizeof(stack));
    game->loaded_gamemap = false;

    init_sdl_window(game, "Piano Tiles", 0, 0, window_width, window_height);
    while (game->is_running) {
//        if (game->loaded_gamemap == false) {
            load_gamemap(argv[1], gamemap);
            init_game(game, gamemap);
            while (SDL_PollEvent(&game->event));
//            game->loaded_gamemap = true;
//        }

//        if (!stack_empty(*game->menu_stack)) {
//            SDL_Log("Main Menu Render");
//            switch (peek(*game->menu_stack)) {
//                case MAIN_MENU:
////                    main_menu_loop();
//                    continue;
//                case LEADER_BOARD:
//                    continue;
//                default:
//                    break;
//            }
//        }
        game_loop(game);


//        if (game->gamestatus == GAME_WON || game->gamestatus == GAME_LOST) {
//            SDL_Log("Game Over");
//            SDL_Delay(1000);
//        }
    }
    delete_game(game);
    free(game);
}