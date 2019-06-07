//
// Created by yiz18 on 06/06/19.
//

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "beatmap.h"

void decode_beat(uint8_t i, row r) {
    r[0] = (i >> 6) & 0x3;
    r[1] = (i >> 4) & 0x3;
    r[2] = (i >> 2) & 0x3;
    r[3] = i & 0x3;
}

void print_beatmap(beatmap beatmap){
    row currentBeat = *beatmap;
    int i = 0;
    while(true) {
        if (((currentBeat[0] == END) || (currentBeat[1] == END) ||
             (currentBeat[2] == END) || (currentBeat[3] == END))) {
            return;
        }
        printf("{%d, %d, %d, %d}\n" ,currentBeat[0], currentBeat[1],
               currentBeat[2], currentBeat[3]);
        currentBeat = beatmap[++i];
    }
}