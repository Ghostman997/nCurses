#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int main (void) {
    WINDOW *mainwin;// *gpiowin;
    int ch;
    int row;
    int col;
    int szx,szy;
    int i;
    char buf[15];
    WINDOW *gpiowinlist[8];

    if ( (mainwin = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }
    //getmaxyx(stdscr, sizew, sizeh);
    getmaxyx(stdscr, szy, szx);
    getmaxyx(stdscr, row, col);
    snprintf(buf, sizeof(buf), "r = %d, c = %d\n", szy, szx);
    //int width = (col) / 4 - 2, height = (row) / 2 - 2;
    int sizew = (col) / 4, sizeh = (row) / 2;
    //int rows = (row) / 2 - 2, cols = (col) / 4 - 2;
    //int x = (width);
    //int y = (height);
    int x = 1;
    int y = 1;

    noecho();
    keypad(mainwin, TRUE);

    gpiowinlist[0] = subwin(mainwin, sizeh, sizew, y, x);
    gpiowinlist[1] = subwin(mainwin, sizeh, sizew, y, x + sizew);
    gpiowinlist[2] = subwin(mainwin, sizeh, sizew, y, x + sizew*2);
    gpiowinlist[3] = subwin(mainwin, sizeh, sizew, y, x + sizew*3);
    gpiowinlist[4] = subwin(mainwin, sizeh, sizew, y + sizeh, x);
    gpiowinlist[5] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew);
    gpiowinlist[6] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew*2);
    gpiowinlist[7] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew*3);
    box(mainwin, '+','+');
    box(gpiowinlist[0], 0, 0);
    box(gpiowinlist[1], 0, 0);
    box(gpiowinlist[2], 0, 0);
    box(gpiowinlist[3], 0, 0);
    box(gpiowinlist[4], 0, 0);
    box(gpiowinlist[5], 0, 0);
    box(gpiowinlist[6], 0, 0);
    box(gpiowinlist[7], 0, 0);
    mvwaddstr(gpiowinlist[0], 1, 4, "lololololol");
    mvwaddstr(gpiowinlist[0], (sizeh) / 2, (sizew) / 2, buf);
    //mvwaddstr(gpiowinlist[0], (height) / 2, (width) / 2, buf);
    /*for (i = 1; i++; i <= 3) {
        gpiowinlist[i] = subwin(mainwin, sizeh, sizew, y, x + sizew); //- sizew);//*(i+1)-1);
        box(gpiowinlist[i], 0, 0);
        snprintf(buf, sizeof(buf), "%d", i);
        mvwaddstr(gpiowinlist[i], sizeh / 2, sizew / 2, buf);
        mvwaddstr(gpiowinlist[i], 1, 4, "lololololol");
        refresh();
    }*/

    refresh();



    while ( (ch = getch()) != 'q' ) {

    //    switch (ch) {
    //    case KEY_RIGHT:
    //        break;
    //    case KEY_LEFT:
    //        break;
    //    break;
    //    clrscr();
    //    }
    }
    delwin(gpiowinlist[0]);
    delwin(gpiowinlist[1]);
    delwin(gpiowinlist[2]);
    delwin(gpiowinlist[3]);
    delwin(gpiowinlist[4]);
    delwin(gpiowinlist[5]);
    delwin(gpiowinlist[6]);
    delwin(gpiowinlist[7]);
   /* for (i = 1; i++; i < 4) {
        delwin(gpiowinlist[i]);
    }*/
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
