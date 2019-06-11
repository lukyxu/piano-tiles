#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "SDL2/SDL.h"
#include "game.h"

void update(beatmap *map);
void play_beatmap(beatmap map);
bool *get_inputs(void);
bool check_valid_inputs(const bool *inputs, const beat_t *curr_row);

int main(int argc, char *argv[]) {
    beatmap map = calloc(MAX_SIZE, sizeof(row));

    game_t *game = malloc(sizeof(game_t));
    init(game, "Piano Tiles",0, 0, window_width, window_height);

    while(game->is_running) {
        load_beatmap(argv[1], map);
        init_beatmap(game, map);
        while (SDL_PollEvent(&game->event));

        while(game->gamestatus == PLAYING){
//            SDL_Log("playing");
            handle_game_events(game);
            update_game(game);
            render_game(game);
        }
        SDL_Log("game over");
        SDL_Delay(1000);
    }
    //play_beatmap(map);

    delete_game(game);
    free(game);
}