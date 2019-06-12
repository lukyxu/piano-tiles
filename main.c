#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "SDL2/SDL.h"
#include "game.h"

int main(int argc, char *argv[]) {
    gamemap_t *gamemap = malloc(sizeof(gamemap_t));
    game_t *game = malloc(sizeof(game_t));
    init_sdl_window(game, "Piano Tiles", 0, 0, window_width, window_height);
    while(game->is_running) {
        load_gamemap(argv[1], gamemap);
        init_game(game, gamemap);

        uint32_t frame_start = 0;
        uint32_t frame_time = 0;
        while (SDL_PollEvent(&game->event));
        while(game->gamestatus == PLAYING || game->gamestatus == PAUSED){
            frame_start = SDL_GetTicks();

            handle_game_events(game);
            update_game(game);
            render_game(game);

            frame_time = SDL_GetTicks() - frame_start;

            if (frame_delay > frame_time){
                SDL_Delay(frame_delay - frame_time);
            }
            if (game->gamestatus == PLAYING) {
                game->map->elapsed_beat_time += frame_delay;
            }
        }
        SDL_Log("Game Over");
        SDL_Delay(1000);
    }
    delete_game(game);
    free(game);
}