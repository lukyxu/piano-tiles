//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_UTILITIES_H
#define PIANOTILES_UTILITIES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "beatmap.h"


static const uint32_t MAX_SIZE = 65536;

void add_padding(beatmap beatmap, int index);

bool load_gamemap(char *address, gamemap_t *gamemap);

bool load_beatmap(beatmap beatmap, FILE *fp, uint32_t *total_beats);

#endif //PIANOTILES_UTILITIES_H
