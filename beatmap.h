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

void decode_beat(uint8_t i, row r);

void print_beatmap(beatmap map);
#endif //PIANOTILES_BEATMAP_H

bool game_over(row current_row);