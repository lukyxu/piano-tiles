//
// Created by kx3418 on 13/06/19.
//

#include "menus.h"
#include "utilities.h"
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
        case 0:
            draw_text(game, "Classic", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
            break;
        case 1:
            draw_text(game, "-------", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16 + window_width/2, window_height - window_width + (window_width/8), (3*window_width)/8, (window_width/4)});
            break;
        case 2:
            draw_text(game, "-------", SMOOTH, (SDL_Color){255,0,0}, (SDL_Rect) {window_width/16, window_height - window_width + (window_width/8) + (window_width/2), (3*window_width)/8, (window_width/4)});
            break;
        case 3:
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
                    SDL_PollEvent(&game->event);
                    break;
                default:
                    return;
            }
        }
    }
}