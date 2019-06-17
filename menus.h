//
// Created by kx3418 on 13/06/19.
//

#ifndef PIANO_TILES_MENUS_H
#define PIANO_TILES_MENUS_H

#include <stdbool.h>
#define LEADER_BOARD_ADDRESS "leaderboard"


typedef struct game game_t;

typedef enum main_menu_pointer{
    MENU_CLASSIC,
    MENU_SPEED,
    MENU_RUSH,
    MENU_HUNDRED,
    MENU_OPTION,
    TOTAL_MENU_OPTIONS
} main_menu_pointer_t;

typedef enum option_menu_pointer{
    MENU_BEATMAP_ADDRESS
} option_menu_pointer_t;

typedef union option_pointer{
    main_menu_pointer_t main_menu_pointer;
}menu_pointer_t;



bool update_main_menu(game_t *game);

void draw_main_menu(game_t *game);

bool update_leaderboard(game_t *game);

void draw_leaderboard(game_t *game);

void add_leaderboard(game_t *game);

void draw_options_menu(game_t *game);

bool update_options_menu(game_t *game);
#endif //PIANO_TILES_MENUS_H
