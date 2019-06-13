//
// Created by kx3418 on 11/06/19.
//

#include "game.h"
#include "utilities.h"
#include <SDL2/SDL_ttf.h>


void init_sdl_window(game_t *game, const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_Log("Game initialized");
        TTF_Init();
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

void init_game(game_t *game, gamemap_t *gamemap) {
    game->map = gamemap;
    game->menu_pointer = 0;
    *(game->menu_stack) = NULL;
    push(game->menu_stack, MAIN_MENU);
    game->gamestatus = PAUSED;
}

void handle_game_events(game_t *game) {

}

void play_beat(game_t *game, uint32_t column){
    switch (game->map->beatmap[game->map->current_row][column]){
        case NOTHING:
            game->map->beatmap[game->map->current_row][column] = FAILED_BEAT;
            game->gamestatus = GAME_LOST;
            break;
        case FINISHED_BEAT:
            game->map->beatmap[game->map->current_row + 1][column] = FAILED_BEAT;
            game->gamestatus = GAME_LOST;
            break;
        default:
            game->map->beatmap[game->map->current_row][column] = FINISHED_BEAT;
            break;
    }
}

bool handle_game_io(game_t *game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN && game->map->current_row < col_tile_amount) {
            switch (game->event.key.keysym.sym) {
                case SDLK_d:
                    SDL_Log("D");
                    play_beat(game, 0);
                    return true;
                case SDLK_f:
                    SDL_Log("F");
                    play_beat(game, 1);
                    return true;
                case SDLK_j:
                    SDL_Log("J");
                    play_beat(game, 2);
                    return true;
                case SDLK_k:
                    SDL_Log("K");
                    play_beat(game, 3);
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
    if (!stack_empty(*game->menu_stack)){
        return;
    }
    SDL_Log("return");
    if (game->gamestatus == PAUSED) {
        // Wait for input when paused
        if (handle_game_io(game)) {
            if (completed_row(game->map->beatmap[game->map->current_row])) {
//                SDL_Log("completed row");
                game->map->completed_rows++;
                game->map->current_row++;
                game->gamestatus = PLAYING;
                return;
            }
        }
        return;
    } else {
        if (handle_game_io(game)) {
//            SDL_Log("Input");
            if (completed_row(game->map->beatmap[game->map->current_row])) {
//                SDL_Log("completed row");
                game->map->completed_rows++;
                game->map->current_row++;
            }
        };
        if (!(game->gamestatus == PLAYING)) {
            return;
        }

        set_tiles_speed(game->map,
                        1.0 / FPS * game->map->tiles_acceleration + game->map->tiles_speed);
        // Each second increase by 0.2 tiles
        //
    }

    for (int i = 0; i < row_tile_amount; ++i) {
        if (game->map->beatmap[game->map->current_row][i] == END) {
            game->gamestatus = GAME_WON;
            return;
        }

        if ((game->map->beatmap[0][i] == SINGLE_BEAT || game->map->beatmap[0][i] == HELD_BEAT) &&
            game->map->elapsed_beat_time >= game->map->tile_period) {
            game->gamestatus = GAME_LOST;
            return;
        }
    }
    if (game->map->elapsed_beat_time >= game->map->tile_period) {
        game->map->beatmap++;
        game->map->elapsed_beat_time = 0;
        game->map->current_row--;
        game->map->tile_period = game->map->tile_period_buffer;
    }
}

void render_game(game_t *game) {
    SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
    SDL_RenderClear(game->renderer);
    for (int j = -1; j < col_tile_amount; ++j) {
//        for (int j = 0; j < col_tile_amount; ++j) {
        for (int i = 0; i < row_tile_amount; ++i) {
            switch (game->map->beatmap[col_tile_amount - (j + 1)][i]) {
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
//            if (j < (col_tile_amount + 1) - game->map->current_row){
            if (j == -1 || j == 0) {
                if (game->gamestatus
                    == GAME_WON) {
                    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
                } else if (game->gamestatus == GAME_LOST) {
                    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
                }
            }
            SDL_RenderFillRect(game->renderer, &(SDL_Rect) {row_padding * (i + 1) + i * tile_width,
                                                            col_padding * (j + 1) +
                                                            j * tile_height +
                                                            (((game->map->elapsed_beat_time) *
                                                              (tile_height + col_padding)) /
                                                             game->map->tile_period),
                                                            tile_width, tile_height});
        }
    }
    char buffer[10];
    sprintf(buffer, "%-.2f", game->map->tiles_speed);
    draw_text(game, buffer, ROUGH, (SDL_Color){200,0,0},(SDL_Rect){window_width/4, window_height/20, window_width/2, window_height/5});
}

void delete_game(game_t *game) {
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
    SDL_Log("Game Exited");
}