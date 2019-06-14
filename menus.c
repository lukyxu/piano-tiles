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
        exit(EXIT_FAILURE);
    }

    // Appends the relevant scores to the leader board file
    switch (game->menu_pointer) {
        case CLASSIC:
            fwrite("CLASSIC: ", 1, sizeof("CLASSIC: ") - 1, fp);
            fprintf(fp, "%-.2f\n", game->map->tiles_speed);
            break;
        default:
            break;
    }
    fclose(fp);
}

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
        exit(EXIT_FAILURE);
    }

    char buffer[20];
    int i = 0;
    char scores[100][10] = {0};
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *rest;
        char *token = strtok_r(buffer, ": \n", &rest);
        switch (game->menu_pointer) {
            case CLASSIC:
                if (!strcmp(token, "CLASSIC")) {
                    strcpy(scores[i], strtok_r(NULL, ": ", &rest));
                    i++;
                }
                break;
            default:
                break;
        }
    }
    sprintf(buffer, "%-.2f", game->map->tiles_speed);
    draw_text(game, buffer, ROUGH, DARK_RED,
              (SDL_Rect) {window_width / 4, window_height / 8, window_width / 2,
                          window_height / 5});
    qsort(scores, (size_t) i, sizeof(char) * 10, &compare_scores);
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

        if (strlen(scores[j]) == 5) {
            scores[j][strlen(scores[j]) - 1] = ' ';
        } else {
            scores[j][strlen(scores[j]) - 1] = '\0';
        }
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
    draw_text(game, "Classic", SMOOTH, WHITE,
              (SDL_Rect) {window_width / 16, window_height - window_width + (window_width / 8),
                          (3 * window_width) / 8, (window_width / 4)});
    // Top right option
    draw_text(game, "-------", SMOOTH, BLACK,
              (SDL_Rect) {window_width / 16 + window_width / 2,
                          window_height - window_width + (window_width / 8), (3 * window_width) / 8,
                          (window_width / 4)});
    // Bottom left option
    draw_text(game, "-------", SMOOTH, BLACK, (SDL_Rect) {window_width / 16,
                                                                          window_height -
                                                                          window_width +
                                                                          (window_width / 8) +
                                                                          (window_width / 2),
                                                                          (3 * window_width) / 8,
                                                                          (window_width / 4)});
    // Bottom right option
    draw_text(game, "-------", SMOOTH, WHITE,
              (SDL_Rect) {window_width / 16 + window_width / 2,
                          window_height - window_width + (window_width / 8) + (window_width / 2),
                          (3 * window_width) / 8, (window_width / 4)});

    switch (game->menu_pointer) {
        case CLASSIC:
            draw_text(game, "Classic", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16,
                                  window_height - window_width + (window_width / 8),
                                  (3 * window_width) / 8, (window_width / 4)});
            break;
        case TBC:
            draw_text(game, "-------", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16 + window_width / 2,
                                  window_height - window_width + (window_width / 8),
                                  (3 * window_width) / 8, (window_width / 4)});
            break;
        case TBC1:
            draw_text(game, "-------", SMOOTH, RED,
                      (SDL_Rect) {window_width / 16,
                                  window_height - window_width + (window_width / 8) +
                                  (window_width / 2), (3 * window_width) / 8, (window_width / 4)});
            break;
        case TBC2:
            draw_text(game, "-------", SMOOTH, RED,
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
                    if (game->menu_pointer == CLASSIC) {
                        pop(game->menu_stack);
                        game->loaded_beatmap = false;
                    }
                    while (SDL_PollEvent(&game->event));
                    break;
                default:
                    return;
            }
        }
    }
}
