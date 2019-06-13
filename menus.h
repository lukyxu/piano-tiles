//
// Created by kx3418 on 13/06/19.
//

#ifndef PIANO_TILES_MENUS_H
#define PIANO_TILES_MENUS_H
#define LEADER_BOARD_ADDRESS "leaderboard"

typedef struct game game_t;
void update_main_menu(game_t *game);
void render_main_menu(game_t *game);
void update_leaderboard(game_t *game);
void render_leaderboard(game_t *game);
void handle_menu_io(game_t *game);
void add_leaderboard(game_t *game);
typedef enum menu_option{
    CLASSIC,
    TBC,
    TBC1,
    TBC2,
    TOTAL_MENU_OPTIONS
} menu_option_t;
#endif //PIANO_TILES_MENUS_H
