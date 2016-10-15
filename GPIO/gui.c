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
    int szx,szy;
    //char buf[32];
    char buf[15];
    /*
    const char *gpiowinlist[7];
    gpiowinlist[0] = "gpio0";
    gpiowinlist[1] = "gpio1";
    gpiowinlist[2] = "gpio2";
    gpiowinlist[3] = "gpio3";
    gpiowinlist[4] = "gpio4";
    gpiowinlist[5] = "gpio5";
    gpiowinlist[6] = "gpio6";
    gpiowinlist[7] = "gpio7";
    */
    WINDOW *gpiowinlist[8];

    //int      width = 23, height = 7;
    //int      rows  = 25, cols   = 80;
    //int      x = (cols - width)  / 2;
    //int      y = (rows - height) / 2;




    if ( (mainwin = initscr()) == NULL) {
    fprintf(stderr, "Error initializing ncurses.\n");
    exit(EXIT_FAILURE);
    }
    getmaxyx(stdscr, row, col);
    getmaxyx(stdscr, szy, szx);
    snprintf(buf, sizeof(buf), "r = %d, c = %d\n", szy, szx);
    int width = (col) / 4 - 2, height = (row) / 2 - 2;
    int sizew = (col) / 4, sizeh = (row) / 2;
    //int rows = (row) / 2 - 2, cols = (col) / 4 - 2;
    //int x = (width);
    //int y = (height);
    int x = 1;
    int y = 1;

    noecho();
    keypad(mainwin, TRUE);

    gpiowinlist[0] = subwin(mainwin, sizeh, sizew, y, x);
    box(mainwin, '+','+');
    box(gpiowinlist[0], 0, 0);
    mvwaddstr(gpiowinlist[0], 1, 4, "lololololol");
    mvwaddstr(gpiowinlist[0], (sizeh) / 2, (sizew) / 2, buf);
    //mvwaddstr(gpiowinlist[0], (height) / 2, (width) / 2, buf);
    //for gpiowinlist[i], i=1, i++:
    //    gpiowinlist[i] = subwin(mainwin, sizeh, , y , x + sizew);
    //    box(gpiowinlist[i], 0, 0);
    //    mvwaddstr(gpiowinlist[i], 
    //    if i>=4:
    //         
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
    delwin(gpiowinlist[0]);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
