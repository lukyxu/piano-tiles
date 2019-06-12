//
// Created by yiz18 on 06/06/19.
//

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "beatmap.h"

void print_beatmap(beatmap map){
    row currentBeat = *map;
    int i = 0;
    while(true) {
        if (game_over( currentBeat)) {
            return;
        }
        printf("{%d, %d, %d, %d}\n" ,currentBeat[0], currentBeat[1],
               currentBeat[2], currentBeat[3]);
        currentBeat = map[++i];
    }
}

bool game_over(row current_row){
    return ((current_row[0] == END) || (current_row[1] == END) ||
    (current_row[2] == END) || (current_row[3] == END));
}