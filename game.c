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
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            SDL_Log("Music Error %s",Mix_GetError());
        }
        game->is_running = true;
    } else {
        game->is_running = false;
    }
}

void init_gamemap(game_t *game, gamemap_t *gamemap) {
    game->map = gamemap;
    game->menu_pointer = 0;
    game->gamestatus = PAUSED;
    game->audio->music = NULL;
    game->audio->fail = NULL;

    if (game->gamemode == HUNDRED) {
        if (gamemap->total_beats >= HUNDRED_TILE_AMOUNT) {
            // Randomly generate
            for (int i = HUNDRED_TILE_AMOUNT; i < HUNDRED_TILE_AMOUNT + col_tile_amount + 1; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i == HUNDRED_TILE_AMOUNT) {
                        gamemap->beatmap[i][j] = END;
                    }else{
                        gamemap->beatmap[i][j] = NOTHING;
                    }
                }
            }
        }else{
            SDL_Log("Beatmap not enough notes for classic");
        }
    }
}

void play_beat(game_t *game, uint32_t column){
    switch (game->map->beatmap[game->map->current_row][column]){
        case NOTHING:
            // Game is lost if tapped tile of the current row is nothing
            game->map->beatmap[game->map->current_row][column] = FAILED_BEAT;
            Mix_PlayChannel(-1, game->audio->fail, 0);
            Mix_HaltMusic();
            game->gamestatus = GAME_LOST;
            break;
        case FINISHED_BEAT:
            // Game is lost if tapped tile of current row tile is finished
            game->map->beatmap[game->map->current_row + 1][column] = FAILED_BEAT;
            Mix_PlayChannel(-1, game->audio->fail, 0);
            Mix_HaltMusic();
            game->gamestatus = GAME_LOST;
            break;
        default:
            game->map->beatmap[game->map->current_row][column] = FINISHED_BEAT;
            break;
    }
}

// Returns true iff a valid input is received
bool handle_game_io(game_t *game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN && game->map->current_row < col_tile_amount) {
            switch (game->event.key.keysym.sym) {
                case SDLK_d:
                    play_beat(game, 0);
                    return true;
                case SDLK_f:
                    play_beat(game, 1);
                    return true;
                case SDLK_j:
                    play_beat(game, 2);
                    return true;
                case SDLK_k:
                    play_beat(game, 3);
                    return true;
                default:
                    return false;
            }
        }
    }
    return false;
}

// Returns true iff the row is completed
bool completed_row(const tile_t *row) {
    return ((row[0] == NOTHING || row[0] == FINISHED_BEAT) &&
            (row[1] == NOTHING || row[1] == FINISHED_BEAT) &&
            (row[2] == NOTHING || row[2] == FINISHED_BEAT) &&
            (row[3] == NOTHING || row[3] == FINISHED_BEAT));
}

void update_game(game_t *game) {
    if (game->gamestatus == PAUSED) {
        // Wait for input when paused
        if (handle_game_io(game)) {
            if (!Mix_PlayingMusic() && (game->gamestatus != GAME_LOST &&
            game->gamestatus != GAME_WON)) {
                // Plays music when a valid input is first pressed and game is not over
                Mix_PlayMusic(game->audio->music, -1);
            }
            if (completed_row(game->map->beatmap[game->map->current_row])) {
                // Unpauses the game
                game->map->completed_rows++;
                game->map->current_row++;
                game->game_start_time = SDL_GetTicks();
                if((game->gamemode != RUSH)){
                    game->map->elapsed_beat_time = game->map->tile_period;
                }
                game->gamestatus = PLAYING;
                return;
            }
        }
        return;
    } else {
        if (handle_game_io(game)) {
            if (completed_row(game->map->beatmap[game->map->current_row])) {
                game->map->completed_rows++;
                game->map->current_row++;
                if((game->gamemode != RUSH)){
                    game->map->elapsed_beat_time = game->map->tile_period;
                }
            }
        };
        if (!(game->gamestatus == PLAYING)) {
            return;
        }
        // Increases speed of tiles each second by tiles_acceleration
        set_tiles_speed(game->map,
                        1.0 / FPS * game->map->tiles_acceleration + game->map->tiles_speed);
    }

    if(game->gamemode == SPEED && ((double) SPEED_TIMER_LENGTH) - (SDL_GetTicks() - (double)game->game_start_time) < 0){
        Mix_PlayChannel(-1, game->audio->fail, 0);
        Mix_HaltMusic();
        game->gamestatus = GAME_LOST;
    }

    for (int i = 0; i < row_tile_amount; ++i) {
        if (game->map->beatmap[game->map->current_row][i] == END) {
            // Game is won when the current row reaches the end
            game->gamestatus = GAME_WON;
            return;
        }

        if ((game->map->beatmap[0][i] == SINGLE_BEAT || game->map->beatmap[0][i] == HELD_BEAT) &&
            game->map->elapsed_beat_time >= game->map->tile_period) {
            // Game is lost as a tile is not tapped and goes out of the window
            Mix_PlayChannel(-1, game->audio->fail, 0);
            Mix_HaltMusic();
            game->gamestatus = GAME_LOST;
            return;
        }
    }
    if (game->map->elapsed_beat_time >= game->map->tile_period) {
        // Tile goes out of the window
        game->map->beatmap++;
        game->map->elapsed_beat_time = 0;
        game->map->current_row--;
        // Buffer is used to smooth rendering as rendering is dependent on tile period
        game->map->tile_period = game->map->tile_period_buffer;
    }
    if(game->gamemode != RUSH){
        game->map->elapsed_beat_time = 0;
    }
}

void draw_score(game_t *game, SDL_Rect rect, bool flag){
    char buffer[10];
    switch (game->gamemode){
        case CLASSIC:
            sprintf(buffer, "  %d  ", game->map->completed_rows);
            draw_text(game, buffer, ROUGH, DARK_RED, rect);
            break;
        case SPEED:
            if (flag == SCORE_LEADERBOARD){
                sprintf(buffer, "  %d  ", game->map->completed_rows);
                draw_text(game, buffer, ROUGH, DARK_RED, rect);
            }else if (game->gamestatus == PAUSED || game->map->completed_rows == 0){
                sprintf(buffer, "%-.2f", (double) SPEED_TIMER_LENGTH/1000);
                draw_text(game, buffer, ROUGH, DARK_RED, rect);
            } else {
                if ((((double) SPEED_TIMER_LENGTH / 1000) -
                     (SDL_GetTicks() - (double) game->game_start_time) /
                     1000) < 0){
                    sprintf(buffer, "0.00");
                }else {
                    sprintf(buffer, "%-.2f", ((double) SPEED_TIMER_LENGTH / 1000) -
                                             (SDL_GetTicks() - (double) game->game_start_time) /
                                             1000);
                }
                draw_text(game, buffer, ROUGH, DARK_RED,rect);
            }
            break;
        case RUSH:
            sprintf(buffer, "%-.2f", game->map->tiles_speed);
            draw_text(game, buffer, ROUGH, DARK_RED, rect);
            break;
        case HUNDRED:
            if (flag == SCORE_LEADERBOARD){
                if (game->map->completed_rows == HUNDRED_TILE_AMOUNT){
                    sprintf(buffer, "  %-.2f  ", (SDL_GetTicks() - (double) game->game_start_time) /
                                              1000);
                    draw_text(game, buffer, ROUGH, DARK_RED, rect);
                }else{
                    sprintf(buffer, "N/A");
                    draw_text(game, buffer, ROUGH, DARK_RED, rect);
                }
            }else {
                sprintf(buffer, "  %d  ", HUNDRED_TILE_AMOUNT - game->map->completed_rows);
                draw_text(game, buffer, ROUGH, DARK_RED, rect);
            }
            break;
        default:break;
    }
}

void draw_game(game_t *game) {
    // Draws the background colour
    SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
    SDL_RenderClear(game->renderer);
    // Draws all the tiles
    for (int j = -1; j < col_tile_amount; ++j) {
        for (int i = 0; i < row_tile_amount; ++i) {
            switch (game->map->beatmap[col_tile_amount - (j + 1)][i]) {
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
            if (j == -1 || j == 0) {
                if (game->gamestatus == GAME_WON) {
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
    // Draw the tiles per second indicator

    draw_score(game, (SDL_Rect) {window_width / 4, window_height / 20, window_width / 2,
                                 window_height / 5}, SCORE_GAME);
}

void delete_game(game_t *game) {
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
    free(game->audio);
    free(game->map);
    free(game->menu_stack);
    SDL_Log("Game Exited");
    free(game);
}

bool load_audio(game_t *game){
    game->audio->music = Mix_LoadMUS(MUS_PATH);

    // If there was a problem loading the music
    if (game->audio->music == NULL) {
        return false;
    }

    // Load the sound effect
    game->audio->fail = Mix_LoadWAV(FAIL_EFFECT_PATH);

    // If there was a problem loading the fail sound effect
    if (game->audio->fail == NULL) {
        SDL_Log("Could not open test.wav: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void free_audio(game_t *game) {
    // Free the sound effects
    Mix_FreeChunk(game->audio->fail);

    // Free the music
    Mix_FreeMusic(game->audio->music);

    // Quit SDL_mixer
    Mix_CloseAudio();

    // Quit SDL
    SDL_Quit();
}