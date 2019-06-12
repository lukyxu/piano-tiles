//
// Created by yiz18 on 06/06/19.
//

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

void add_padding(beatmap beatmap, int index) {
    for (int i = 1; i < 10; ++i) {
        beatmap[index + i] = calloc(4, sizeof(beat_t));
    }
}

bool load_beatmap(char *address, beatmap beatmap) {
    FILE *fp = fopen(address, "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while(true){
        beatmap[index] = calloc(4, sizeof(beat_t));
        for (int i = 0; i < 4; ++i) {
            int read_char = fgetc(fp);
            if(read_char == '\n'){
                i--;
                continue;
            }
            if (read_char == '3'){
                beatmap[index][0] = 3;
                beatmap[index][1] = 3;
                beatmap[index][2] = 3;
                beatmap[index][3] = 3;
                fclose(fp);
                add_padding(beatmap, index);
                return true;
            }
            else if(read_char == EOF || read_char < '0' || read_char > '2'){
                fclose(fp);
                return false;
            }
            beatmap[index][i] = read_char - '0';
        }
        index++;
    }
}