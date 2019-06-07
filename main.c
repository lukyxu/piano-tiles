#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include <ncurses.h>

int main(int argc, char *argv[]) {
    beatmap map = calloc(MAX_SIZE, sizeof(row));
    load_beatmap(argv[1], map);
    print_beatmap(map);

    initscr();			/* Start curses mode 		  */
    cbreak();
    noecho();

    printw("|    |    |    |    |\n");
    printw("|    |    |    |    |\n");
    printw("|____|____|____|____|\n");
    printw("|    |    |    |    |\n");
    printw("|    |    |    |    |\n");
    printw("|____|____|____|____|\n");
    printw("|    |    |    |    |\n");
    printw("|    |    |    |    |\n");
    printw("|____|____|____|____|\n");
    printw("|    |    |    |    |\n");
    printw("|    |    |    |    |\n");
    printw("|____|____|____|____|\n");
    printw("|    |    |    |    |\n");
    printw("|    |    |    |    |\n");
    printw("|____|____|____|____|\n");	/* Print Hello World		  */
    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    refresh();
    getch();
    getch();
    endwin();			/* End curses mode		  */
}