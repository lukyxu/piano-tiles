//
// Created by yiz18 on 06/06/19.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>


bool load_beatmap(char *address, beatmap beatmap) {
    uint8_t *memory = (uint8_t *) calloc(MAX_SIZE, sizeof(uint8_t));
    FILE *fp = fopen(address, "rb");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    size_t count = fread(memory, sizeof(uint8_t), MAX_SIZE, fp);


    fclose(fp);
    for (int i = 0; i < count + 8; i++) {
        beatmap[i] = calloc (4, sizeof(beat_t));
        if (i < count) {
            decode_beat(memory[i], beatmap[i]);
        }
    }

    free(memory);

    return true;
}