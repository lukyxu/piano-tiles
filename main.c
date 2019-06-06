#include <stdio.h>
//#include <caca_conio.h>
#include <stdlib.h>
#include "utilities.h"

int main(int argc, char *argv[]) {
    beatmap map = {0};
    load(argv[1], map);
    print_beatmap(map);
}

//void update(void) {
//
//    clrscr();
//}