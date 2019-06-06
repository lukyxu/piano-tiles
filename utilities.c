//
// Created by yiz18 on 06/06/19.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

bool load(char *address, beatmap beatmap){
    uint8_t *memory = malloc(MAX_SIZE);
    FILE *fp = fopen(address, "rb");
    if (fp == NULL){
        return false;
    }

    size_t count = fread(memory, sizeof(uint8_t), MAX_SIZE, fp);
    fclose(fp);
    for (int i = 0; i < count; i++) {
        *(beatmap+i) = malloc(sizeof(beat_t));
        *(beatmap+i) = decode_beat(*memory);
    }
    free(memory);
    return true;
}


beat decode_beat(uint8_t i) {
    beat decoded_beat = malloc (sizeof(beat_t));
    decoded_beat[0] = i >> 6 & 0x2;
    decoded_beat[1] = i >> 4 & 0x2;
    decoded_beat[2] = i >> 2 & 0x2;
    decoded_beat[3] = i & 0x2;
    return decoded_beat;
}

void print_beatmap(beatmap beatmap){
    beat currentBeat = *beatmap;
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