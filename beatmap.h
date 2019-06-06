//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_BEATMAP_H
#define PIANOTILES_BEATMAP_H
typedef enum Beat{
    NOTHING = 0,
    SINGLE_BEAT = 1,
    HELD_BEAT = 2,
    END = 3
} beat_t;

typedef beat_t *beat;
typedef beat_t **beatmap;
#endif //PIANOTILES_BEATMAP_H
