//
// Created by yiz18 on 06/06/19.
//

#ifndef PIANOTILES_UTILITIES_H
#define PIANOTILES_UTILITIES_H

#include <stdbool.h>
#include <stdint.h>
#include "beatmap.h"

static const uint32_t MAX_SIZE = 65536;

bool load(char *address, beatmap beatmap);
beat decode_beat(uint8_t i);

void print_beatmap(beatmap beatmap);
#endif //PIANOTILES_UTILITIES_H
