//
// Created by kx3418 on 13/06/19.
//

#include "menus.h"
#include "utilities.h"

void update_leaderboard(game_t *game){

//    if(game->loaded_beatmap){
//        SDL_Log("whoops");
//        add_leaderboard(game);
//        game->loaded_beatmap = false;
//    }

    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_KEYDOWN) {
            switch (game->event.key.keysym.sym) {
                case SDLK_k:
                    pop(game->menu_stack);
                    push(game->menu_stack, MAIN_MENU);
                    break;
                default:
                    return;
            }
        }
    }
}

void add_leaderboard(game_t *game) {
    FILE *fp = fopen(LEADER_BOARD_ADDRESS, "a+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[20] = {0};
    switch (game->menu_pointer){
        case CLASSIC:
            strcpy(buffer, "CLASSIC");
            strcat(buffer, ": ");
            char convert_buffer[10];
            sprintf(convert_buffer, "%-.2f", game->map->tiles_speed);
            strcat(buffer, convert_buffer);
            strcat(buffer, "\n");
            break;
    }
    fwrite(buffer, 1, sizeof(buffer),fp);
    fclose(fp);
};
void render_leaderboard(game_t *game){
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);
    draw_text(game, "LEADER BOARD", ROUGH, (SDL_Color){0,0,0}, (SDL_Rect){window_width/16, 0,
                                                                         (7 * window_width / 8), window_height / 5});
};

void update_main_menu(game_t *game){
    handle_menu_io(game);
};
void render_main_menu(game_t *game){
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // 100 400
    draw_text(game, "Piano Tiles", ROUGH, (SDL_Color){0,0,0}, (SDL_Rect){window_width/6, window_height/30,
                                                                         (int) (window_width / 1.5), window_height / 5});
    SDL_RenderFillRect(game->renderer, &(SDL_Rect) {0, window_height - window_width, window_width/2, window_width/2});
    SDL_RenderFillRect(game->renderer, &(SDL_Rect) {window_width/2, (window_height - window_width/2), window_width/2, window_width/2});

    // Top left
    draw_text(game, "Classic", SMOOTH, (SDL_Color){255,255,255}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
    // Top right
    draw_text(game, "-------", SMOOTH, (SDL_Color){0,0,0}, (SDL_Rect) {window_width/16 + window_width/2, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
    // Bottom left
    draw_text(game, "-------", SMOOTH, (SDL_Color){0,0,0}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8) + (window_width/2), (3*window_width)/8, (window_width/4)});
    // Bottom right
    draw_text(game, "-------", SMOOTH, (SDL_Color){255,255,255}, (SDL_Rect) {window_width/16 + window_width/2, window_height - window_width + (window_width/8) + (window_width/2), (3*window_width)/8, (window_width/4)});

    switch (game->menu_pointer){
        case CLASSIC:
            draw_text(game, "Classic", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
            break;
        case TBC:
            draw_text(game, "-------", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16 + window_width/2, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
            break;
        case TBC1:
            draw_text(game, "-------", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8) + (window_width/2), (3*window_width)/8, (window_width/4)});
            break;
        case TBC2:
            draw_text(game, "-------", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16 + window_width/2, window_height - window_width + (window_width/8) + (window_width/2), (3*window_width)/8, (window_width/4)});
            break;
    }
//    SDL_RenderFillRect(game->renderer, &(SDL_Rect) {20, 20, 200, 200});
//    draw_text(game, "Hello", SMOOTH, (SDL_Color){255,255,255}, (SDL_Rect) {20, 20, 200, 200});
};

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
                    if (game->menu_pointer == 0) {
                        pop(game->menu_stack);
                    }
                    game->loaded_beatmap = false;
                    while (SDL_PollEvent(&game->event));
                    break;
                default:
                    return;
            }
        }
    }
}