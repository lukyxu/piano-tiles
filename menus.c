//
// Created by kx3418 on 13/06/19.
//

#include "menus.h"
#include "utilities.h"

bool update_leaderboard(game_t *game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN) {
            switch (game->event.key.keysym.sym) {
                case SDLK_k:
                    // Sets next menu is main menu
                    pop(game->menu_stack);
                    push(game->menu_stack, MAIN_MENU);
                    return true;
                default:
                    break;
            }
        }
    }
    return false;
}

void add_leaderboard(game_t *game) {
    FILE *fp = fopen(LEADER_BOARD_ADDRESS, "a+");
    if (fp == NULL) {
        SDL_Log("Could not open leaderboard");
        exit(EXIT_FAILURE);
    }

    // Appends the relevant scores to the leader board file
    switch (game->gamemode) {
        case CLASSIC:
            fwrite("CLASSIC: ", 1, sizeof("CLASSIC: ") - 1, fp);
            fprintf(fp, "%d\n", game->map->completed_rows);
            break;
        case SPEED:
            fwrite("SPEED: ", 1, sizeof("SPEED: ") - 1, fp);
            fprintf(fp, "%d\n", game->map->completed_rows);
            break;
        case RUSH:
            fwrite("RUSH: ", 1, sizeof("RUSH: ") - 1, fp);
            fprintf(fp, "%-.2f\n", game->map->tiles_speed);
            break;
        case HUNDRED:
            if (game->map->completed_rows == HUNDRED_TILE_AMOUNT) {
                fwrite("HUNDRED: ", 1, sizeof("HUNDRED: ") - 1, fp);
                fprintf(fp, "%-.2f\n", ((double) game->game_time_tracker) / 1000);
            }
            break;
        default:
            break;
    }
    fclose(fp);
}

//char buffer[10];
//switch (game->gamemode){
//case CLASSIC:
//sprintf(buffer, "  %d  ", game->map->completed_rows);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//break;
//case SPEED:
//if (flag == SCORE_LEADERBOARD){
//sprintf(buffer, "  %d  ", game->map->completed_rows);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//}else if (game->gamestatus == PAUSED || game->map->completed_rows == 0){
//sprintf(buffer, "%-.2f", (double) SPEED_TIMER_LENGTH/1000);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//} else {
//if ((((double) SPEED_TIMER_LENGTH / 1000) -
//(SDL_GetTicks() - (double) game->game_start_time) /
//1000) < 0){
//sprintf(buffer, "0.00");
//}else {
//sprintf(buffer, "%-.2f", ((double) SPEED_TIMER_LENGTH / 1000) -
//(SDL_GetTicks() - (double) game->game_start_time) /
//1000);
//}
//draw_text(game, buffer, ROUGH, DARK_RED,rect);
//}
//break;
//case RUSH:
//sprintf(buffer, "%-.2f", game->map->tiles_speed);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//break;
//case HUNDRED:
//if (flag == SCORE_LEADERBOARD){
//if (game->map->completed_rows == HUNDRED_TILE_AMOUNT){
//sprintf(buffer, "  %-.2f  ", (SDL_GetTicks() - (double) game->game_start_time) /
//1000);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//}else{
//sprintf(buffer, "N/A");
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//}
//}else {
//sprintf(buffer, "  %d  ", HUNDRED_TILE_AMOUNT - game->map->completed_rows);
//draw_text(game, buffer, ROUGH, DARK_RED, rect);
//}
//break;
//default:break;
//}

void draw_leaderboard(game_t *game) {
    // Draws the background
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);

    // Draws the leaderboard header
    draw_text(game, "LEADER BOARD", ROUGH, BLACK, (SDL_Rect) {window_width / 16, 0,
                                                                              (7 * window_width /
                                                                               8),
                                                                              window_height / 5});
    FILE *fp = fopen(LEADER_BOARD_ADDRESS, "r");
    if (fp == NULL) {
        SDL_Log("Could not open leaderboard");
        exit(EXIT_FAILURE);
    }

    char buffer[20];
    int i = 0;

//    char scores[100][10] = {0};
    int file_length = get_file_lines_length(fp);
    char (*scores)[10] = malloc(file_length * sizeof(char[10]));
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *rest;
        char *token = strtok_r(buffer, ": \n", &rest);
        switch (game->gamemode) {
            case CLASSIC:
                if (token != NULL && !strcmp(token, "CLASSIC")) {
                    sprintf(scores[i], "%4d", (int) strtol(strtok_r(NULL, ": ", &rest), NULL, 0));
                    i++;
                }
                break;
            case SPEED:
                if (token != NULL && !strcmp(token, "SPEED")) {
                    sprintf(scores[i], "%4d", (int) strtol(strtok_r(NULL, ": ", &rest), NULL, 0));
                    i++;
                }
                break;
            case RUSH:
                if (token != NULL && !strcmp(token, "RUSH")) {
                    sprintf(scores[i], "%.2f",strtod(strtok_r(NULL, ": ", &rest),NULL));
                    i++;
                }
                break;
            case HUNDRED:
                if (token != NULL && !strcmp(token, "HUNDRED")) {
                    sprintf(scores[i], "%.2f",strtod(strtok_r(NULL, ": ", &rest),NULL));
                    i++;
                }
                break;
            default:
                break;
        }
    }

    draw_score(game, (SDL_Rect) {window_width / 4, window_height / 8, window_width / 2,
                                 window_height / 5}, SCORE_LEADERBOARD);

    if (game->gamemode == HUNDRED) {
        qsort(scores, (size_t) i, sizeof(char[10]), &compare_asc_scores);

    }else{
        qsort(scores, (size_t) i, sizeof(char[10]), &compare_desc_scores);
    }

    uint32_t max_col1 = 0;

    while (3 * window_height / 10 + max_col1 * window_height / 10 + window_height / 10 <
           window_height) {
        max_col1++;
    }
    if (i > max_col1) {
        SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(game->renderer,
                           &(SDL_Rect) {window_width / 2 + 4, 8 * window_height / 25, 4,
                                        17 * window_height / 25});
    }

    for (int j = 0; j < i; ++j) {
        sprintf(buffer, "%d", j + 1);

        if (j < max_col1) {
            // Draws the left index
            draw_text(game, buffer, ROUGH, BLACK,
                      (SDL_Rect) {window_width / 20,
                                  3 * window_height / 10 + j * window_height / 10,
                                  window_width / 10,
                                  window_height / 10});
            // Draws the left score
            draw_text(game, scores[j], ROUGH, BLACK,
                      (SDL_Rect) {1 * window_width / 4,
                                  3 * window_height / 10 + j * window_height / 10, window_width / 4,
                                  window_height / 10});
        } else if (j < 2 * max_col1) {
            // Draws the right index
            draw_text(game, buffer, ROUGH, BLACK,
                      (SDL_Rect) {1 * window_width / 2 + window_width / 20,
                                  3 * window_height / 10 + (j - max_col1) * window_height / 10,
                                  window_width / 10,
                                  window_height / 10});
            // Draws the right score
            draw_text(game, scores[j], ROUGH, BLACK,
                      (SDL_Rect) {3 * window_width / 4,
                                  3 * window_height / 10 + (j - max_col1) * window_height / 10,
                                  window_width / 4, window_height / 10});
        }
    }

    free(scores);
    fclose(fp);
}

void update_main_menu(game_t *game) {
    handle_menu_io(game);
}

void draw_main_menu(game_t *game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // 100 400
    draw_text(game, "Piano Tiles", ROUGH, BLACK,
              (SDL_Rect) {window_width / 6, window_height / 30,
                          (int) (window_width / 1.5), window_height / 5});
    SDL_RenderFillRect(game->renderer,
                       &(SDL_Rect) {0, window_height - window_width, window_width / 2,
                                    window_width / 2});
    SDL_RenderFillRect(game->renderer,
                       &(SDL_Rect) {window_width / 2, (window_height - window_width / 2),
                                    window_width / 2, window_width / 2});

    // Top left option
    draw_text(game, "CLASSIC", SMOOTH, WHITE,
              (SDL_Rect) {window_width / 16, window_height - window_width + (window_width / 8),
                          (3 * window_width) / 8, (window_width / 4)});
    // Top right option
    draw_text(game, " SPEED ", SMOOTH, BLACK,
              (SDL_Rect) {window_width / 16 + window_width / 2,
                          window_height - window_width + (window_width / 8), (3 * window_width) / 8,
                          (window_width / 4)});
    // Bottom left option
    draw_text(game, " RUSH ", SMOOTH, BLACK, (SDL_Rect) {window_width / 16,
                                                                          window_height -
                                                                          window_width +
                                                                          (window_width / 8) +
                                                                          (window_width / 2),
                                                                          (3 * window_width) / 8,
                                                                          (window_width / 4)});
    // Bottom right option
    draw_text(game, "HUNDRED", SMOOTH, WHITE,
              (SDL_Rect) {window_width / 16 + window_width / 2,
                          window_height - window_width + (window_width / 8) + (window_width / 2),
                          (3 * window_width) / 8, (window_width / 4)});

    switch (game->menu_pointer) {
        case MENU_CLASSIC:
            draw_text(game, "CLASSIC", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16,
                                  window_height - window_width + (window_width / 8),
                                  (3 * window_width) / 8, (window_width / 4)});
            break;
        case MENU_SPEED:
            draw_text(game, " SPEED ", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16 + window_width / 2,
                                  window_height - window_width + (window_width / 8),
                                  (3 * window_width) / 8, (window_width / 4)});
            break;
        case MENU_RUSH:
            draw_text(game, " RUSH ", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16,
                                  window_height - window_width + (window_width / 8) +
                                  (window_width / 2), (3 * window_width) / 8, (window_width / 4)});
            break;
        case MENU_HUNDRED:
            draw_text(game, "HUNDRED", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16 + window_width / 2,
                                  window_height - window_width + (window_width / 8) +
                                  (window_width / 2), (3 * window_width) / 8, (window_width / 4)});
            break;
        default:
            break;
    }
}


void handle_menu_io(game_t *game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN) {
            switch (game->event.key.keysym.sym) {
                case SDLK_f:
                    game->menu_pointer = (game->menu_pointer - 1) % (TOTAL_MENU_OPTIONS);
                    break;
                case SDLK_j:
                    game->menu_pointer = (game->menu_pointer + 1) % (TOTAL_MENU_OPTIONS);
                    break;
                case SDLK_k:
                    switch (game->menu_pointer){
                        case MENU_CLASSIC:
                            game->gamemode = CLASSIC;
                            break;
                        case MENU_SPEED:
                            game->gamemode = SPEED;
                            break;
                        case MENU_RUSH:
                            game->gamemode = RUSH;
                            break;
                        case MENU_HUNDRED:
                            game->gamemode = HUNDRED;
                            break;
                        default:break;
                    }
                    pop(game->menu_stack);
                    game->loaded_beatmap = false;
                    while (SDL_PollEvent(&game->event));
                    break;
                default:
                    return;
            }
        }
    }
}
