//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_BEATMAP_H
#define PIANOTILES_BEATMAP_H


#include <stdint.h>
typedef enum Beat{
    NOTHING = 0,
    SINGLE_BEAT = 1,
    HELD_BEAT = 2,
    END = 3,
    FINISHED_BEAT = 4,
    FAILED_BEAT = 5
} beat_t;

typedef beat_t *row;
typedef beat_t **beatmap;

typedef struct gamemap{
    beatmap beatmap;
    uint32_t total_beats;
    double tiles_speed;
    double tiles_acceleration;
    uint32_t tile_period_buffer;
    uint32_t tile_period;
    uint32_t completed_rows;
    uint32_t current_row;
    uint32_t elapsed_beat_time;
} gamemap_t;

static inline void set_tile_period_buffer(gamemap_t *gamemap, uint32_t period){
    gamemap->tile_period_buffer = period;
    gamemap->tiles_speed = 1000/gamemap->tile_period_buffer;
}
//SDL_Log("%3f", game->map->tiles_speed);

static inline void set_tiles_speed(gamemap_t *gamemap, double TPS){
    gamemap->tiles_speed = TPS;
    gamemap->tile_period_buffer = (uint32_t) (1000 / gamemap->tiles_speed);
}

static inline void set_tile_period(gamemap_t *gamemap){
    gamemap->tile_period = gamemap->tile_period_buffer;
}

void decode_beat(int *input, row r);

void print_beatmap(beatmap map);
#endif //PIANOTILES_BEATMAP_H

bool game_over(row current_row);