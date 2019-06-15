//
// Created by kx3418 on 13/06/19.
//

#ifndef PIANO_TILES_MENUS_H
#define PIANO_TILES_MENUS_H

#include <stdbool.h>
#define LEADER_BOARD_ADDRESS "leaderboard"


typedef struct game game_t;

typedef enum menu_option{
    MENU_CLASSIC,
    MENU_SPEED,
    MENU_RUSH,
    MENU_HUNDRED,
    TOTAL_MENU_OPTIONS
} menu_option_t;


void update_main_menu(game_t *game);

void draw_main_menu(game_t *game);

bool update_leaderboard(game_t *game);

void draw_leaderboard(game_t *game);

void handle_menu_io(game_t *game);

void add_leaderboard(game_t *game);
#endif //PIANO_TILES_MENUS_H
