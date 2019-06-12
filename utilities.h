//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_UTILITIES_H
#define PIANOTILES_UTILITIES_H

#include <stdbool.h>
#include <stdint.h>
#include "beatmap.h"

static const uint32_t MAX_SIZE = 65536;

void add_padding(beatmap beatmap, int index);

bool load_beatmap(char *address, beatmap beatmap);

#endif //PIANOTILES_UTILITIES_H
