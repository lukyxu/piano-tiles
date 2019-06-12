//
// Created by kx3418 on 11/06/19.
//

#include "game.h"


void init(game_t *game, const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_Log("Game initialized");
        game->window = SDL_CreateWindow(title, xpos, ypos, width, height, false);
        if (game->window) {
            SDL_Log("Window created");
        }
        game->renderer = SDL_CreateRenderer(game->window, -1, 0);
        if (game->renderer) {
            SDL_Log("Renderer created");
        }
        game->is_running = true;
    } else {
        game->is_running = false;
    }
    game->gamestatus = INVALID;
}

void init_beatmap(game_t *game, beatmap map) {
    game->map = map;
    render_game(game);
    game->gamestatus = PLAYING;
    game->paused = true;
    game->elapsed_beat_time = 0;
}

void handle_game_events(game_t *game) {

}

bool handle_game_io(game_t *game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN) {
            switch (game->event.key.keysym.sym) {
                case SDLK_d:
                    SDL_Log("D");
                    if (!(game->map[0][0] == NOTHING)) {
                        game->map[0][0] = FINISHED_BEAT;
                    } else {
                        game->map[0][0] = FAILED_BEAT;
                        game->gamestatus = GAME_LOST;
                    }
                    return true;
                case SDLK_f:
                    SDL_Log("F");
                    if (!(game->map[0][1] == NOTHING)) {
                        game->map[0][1] = FINISHED_BEAT;
                    } else {
                        game->map[0][1] = FAILED_BEAT;
                        game->gamestatus = GAME_LOST;
                    }
                    return true;
                case SDLK_j:
                    SDL_Log("J");
                    if (!(game->map[0][2] == NOTHING)) {
                        game->map[0][2] = FINISHED_BEAT;
                    } else {
                        game->map[0][2] = FAILED_BEAT;
                        game->gamestatus = GAME_LOST;
                    }
                    return true;
                case SDLK_k:
                    SDL_Log("K");
                    if (!(game->map[0][3] == NOTHING)) {
                        game->map[0][3] = FINISHED_BEAT;
                    } else {
                        game->map[0][3] = FAILED_BEAT;
                        game->gamestatus = GAME_LOST;
                    }
                    return true;
                default:
                    return false;
            }
//            }
        }
    }
}

bool completed_row(const beat_t *row) {
    return ((row[0] == NOTHING || row[0] == FINISHED_BEAT) &&
            (row[1] == NOTHING || row[1] == FINISHED_BEAT) &&
            (row[2] == NOTHING || row[2] == FINISHED_BEAT) &&
            (row[3] == NOTHING || row[3] == FINISHED_BEAT));
}

void update_game(game_t *game) {
    if (game->paused) {
        // Wait for input when paused
        if (handle_game_io(game)) {
            if (completed_row(game->map[0])) {
                SDL_Log("completed row");
                game->map++;
                game->paused = false;
                game->elapsed_beat_time = 0;
                return;
            }
        }
        return;
    } else {
        if (handle_game_io(game)) {
            SDL_Log("Input");
            if (completed_row(game->map[0])) {
                SDL_Log("completed row");
                game->map++;
                game->elapsed_beat_time = 0;
                return;
            }
        };
        if (!(game->gamestatus == PLAYING)) {
            return;
        }
    }
    for (int i = 0; i < row_tile_amount; ++i) {
        if ((game->map[0][i] == SINGLE_BEAT || game->map[0][i] == HELD_BEAT) &&
            game->elapsed_beat_time >= 500) {
            game->gamestatus = GAME_LOST;
            return;
        }
        if (game->map[0][i] == END) {
            game->gamestatus = GAME_WON;
        }
    }
//    game->map++;
}

void render_game(game_t *game) {
    SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
    SDL_RenderClear(game->renderer);
    for (int j = -1; j < col_tile_amount; ++j) {
//        for (int j = 0; j < col_tile_amount; ++j) {
        for (int i = 0; i < row_tile_amount; ++i) {
            switch (game->map[col_tile_amount - (j + 1)][i]) {
                // 6 - (1:6)
                case FINISHED_BEAT:
                    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
                    break;
                case SINGLE_BEAT:
                case HELD_BEAT:
                    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
                    break;
                case END:
                    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
                    break;
                case FAILED_BEAT:
                    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            }
            if (j == 0) {
                if (game->gamestatus == GAME_WON) {
                    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
                } else if (game->gamestatus == GAME_LOST) {
                    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
                }
            }
            SDL_RenderFillRect(game->renderer, &(SDL_Rect) {row_padding * (i + 1) + i * tile_width,
                                                            col_padding * (j + 1) + j * tile_height,
                                                            tile_width, tile_height});
        }
    }
    SDL_RenderPresent(game->renderer);
}

void delete_game(game_t *game) {
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
    SDL_Log("Game exited");
}