#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int main (void) {
    WINDOW *mainwin, *gpiowin;
    int ch;
    int row;
    int col;
    const char *gpiowinlist[7];
    gpiowinlist[0] = "gpio0";
    gpiowinlist[1] = "gpio1";
    gpiowinlist[2] = "gpio2";
    gpiowinlist[3] = "gpio3";
    gpiowinlist[4] = "gpio4";
    gpiowinlist[5] = "gpio5";
    gpiowinlist[6] = "gpio6";
    gpiowinlist[7] = "gpio7";



    if ( (mainwin = initscr()) == NULL) {
    fprintf(stderr, "Error initializing ncurses.\n");
    exit(EXIT_FAILURE);
    }
    getmaxyx(stdscr, row, col);
    int width = (col) / 4 , height = (row) / 2 ;
    int rows = (row) / 2 - 2, cols = (col) / 4 - 2;
    int x = (cols - width) / 2;
    int y = (rows - height) / 2;

    noecho();
    keypad(mainwin, TRUE);

    gpiowinlist[0] = subwin(mainwin, height, width, y, x);
    box(mainwin, 0, 0);
    box(gpiowinlist[0], 0, 0);
    //mvwaddstr(gpiowin, 1, 4, "Move the window");
    //mvwaddstr(gpiowin, 2, 2, "with the arrow keys");
    //mvwaddstr(gpiowin, 3, 6, "or HOME/END");
    //mvwaddstr(gpiowin, 5, 3, "Press 'q' to quit");

    refresh();



    while ( (ch = getch()) != 'q' ) {

        switch (ch) {
        case KEY_RIGHT:     
            break;
        case KEY_LEFT:
            break;
        break;          
        }
    }
    delwin(gpiowin);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
