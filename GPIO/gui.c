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
    int v, h;
    int i;
    char buf[15];
    WINDOW *gpiowinlist[8];

    if ( (mainwin = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }


    start_color();



    init_pair(1,  COLOR_RED,     COLOR_BLACK);
    init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
    init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
    init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
    init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
    init_pair(8,  COLOR_WHITE,   COLOR_RED);
    init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
    init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
    init_pair(11, COLOR_WHITE,   COLOR_BLUE);
    init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
    init_pair(13, COLOR_BLACK,   COLOR_CYAN);
    init_pair(14, COLOR_WHITE, COLOR_BLACK);


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

    //noecho();
    keypad(mainwin, TRUE);

   /* gpiowinlist[0] = subwin(mainwin, sizeh, sizew, y, x);
    gpiowinlist[1] = subwin(mainwin, sizeh, sizew, y, x + sizew);
    gpiowinlist[2] = subwin(mainwin, sizeh, sizew, y, x + sizew*2);
    gpiowinlist[3] = subwin(mainwin, sizeh, sizew, y, x + sizew*3);
    gpiowinlist[4] = subwin(mainwin, sizeh, sizew, y + sizeh, x);
    gpiowinlist[5] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew);
    gpiowinlist[6] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew*2);
    gpiowinlist[7] = subwin(mainwin, sizeh, sizew, y + sizeh, x + sizew*3);
    */
    box(mainwin, '|','-');
    /*box(gpiowinlist[0], 0, 0);
    box(gpiowinlist[1], 0, 0);
    box(gpiowinlist[2], 0, 0);
    box(gpiowinlist[3], 0, 0);
    box(gpiowinlist[4], 0, 0);
    box(gpiowinlist[5], 0, 0);
    box(gpiowinlist[6], 0, 0);
    box(gpiowinlist[7], 0, 0);
    mvwaddstr(gpiowinlist[0], 1, 4, "lololololol");
    mvwaddstr(gpiowinlist[0], (sizeh) / 2, (sizew) / 2, buf);
    */
    //mvwaddstr(gpiowinlist[0], (height) / 2, (width) / 2, buf);
    for (i = 0; i < 8; i++) {
        gpiowinlist[i] = subwin(mainwin, sizeh - 1, sizew, y, x + (sizew*i)); //- sizew);//*(i+1)-1);
        //box(gpiowinlist[i], '-', '|');
        wborder(gpiowinlist[i], 176, 176, 176, 176, 176, 176, 176, 176);
        if (i >= 4) {
            gpiowinlist[i] = subwin(mainwin, sizeh - 1, sizew, y + sizeh, x + sizew*(i-4));
            //box(gpiowinlist[i], '-', '|');
            wborder(gpiowinlist[i], 176, 176, 176, 176, 176, 176, 176, 176);
        }
        //box(gpiowinlist[i], 0, 0);
        snprintf(buf, sizeof(buf), "%d", i+1);
        mvwaddstr(gpiowinlist[i], sizeh / 2, sizew / 2, buf);
        mvwaddstr(gpiowinlist[i], 1, 4, "lololololol");
        //refresh();
    }

    refresh();

    i = 0;
    wbkgd(gpiowinlist[i], COLOR_PAIR(8));
    wrefresh(gpiowinlist[i]);
    while ( (ch = getch()) != 'q' ) {
        switch (ch) {
            case 'a':
            case KEY_RIGHT:
                wbkgd(gpiowinlist[i], COLOR_PAIR(14));
                wrefresh(gpiowinlist[i]);
                i++;
                if (i > 7) {
                    i = 0;
                }
                //gpiowinlist[i++];
                //box(gpiowinlist[i++],v, 0);
                wbkgd(gpiowinlist[i], COLOR_PAIR(1));
                mvwaddstr(gpiowinlist[i], 3, 3, "wat");
                wrefresh(gpiowinlist[i]);
                break;
            case 'd':
            case KEY_LEFT:
                wbkgd(gpiowinlist[i], COLOR_PAIR(14));
                wrefresh(gpiowinlist[i]);
                i--;
                if (i < 0) {
                    i = 7;
                }
                //gpiowinlist[i--];
                //box(gpiowinlist[i--]);
                wbkgd(gpiowinlist[i], COLOR_PAIR(1));
                mvwaddstr(gpiowinlist[i], 3, 3, "nah");
                wrefresh(gpiowinlist[i]);
                break;
            case KEY_UP:
                wbkgd(gpiowinlist[i], COLOR_PAIR(14));
                wrefresh(gpiowinlist[i]);
                if ((i > 3) && (i < 8)) {
                    i -= 4; // i = i - 4
                }
                else if((i < 4) && (i >= 0)) {
                    i += 4;
                }
                //if (i / (i+4) == 0){
                //    i = i - 4;
                // }
                wbkgd(gpiowinlist[i], COLOR_PAIR(1));
                mvwaddstr(gpiowinlist[i], 3, 3, "lol");
                wrefresh(gpiowinlist[i]);
                break;
            case KEY_DOWN:
                wbkgd(gpiowinlist[i], COLOR_PAIR(14));
                wrefresh(gpiowinlist[i]);
                if ((i >=0) && (i < 4)){
                    i += 4;
                }
                else if((i < 8) && (i > 3)){
                    i -= 4;
                }
                wbkgd(gpiowinlist[i], COLOR_PAIR(1));
                mvwaddstr(gpiowinlist[i], 3, 3, "lul");
                wrefresh(gpiowinlist[i]);
                break;
            //clrscr();
            //case 'o':
            //    mvwaddstr(gpiowinlist[i], 5, 5, "on");
            //    wrefresh(gpiowinlist[i]);
            //    break;
        }
        //mvwaddstr(gpiowinlist[i], 3, 3, "wat");
        //refresh();
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
