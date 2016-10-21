#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <ncurses.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

// defines to make life easier
#define COLOR_ACTIVE COLOR_PAIR(1)
#define COLOR_INACTIVE COLOR_PAIR(14)
#define LIST_MAX 8
#define GPIO_LOW 0
#define GPIO_HIGH 1

// code stolen from http://elinux.org/RPi_GPIO_Code_Sample#sysfs
#define VALUE_MAX 64
#define BUFFER_MAX 3
#define DIRECTION_MAX 64
#define IN  0
#define OUT 1

static int GPIOExport(int pin) {
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open export for writing!\n");
        return(-1);
    }
    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

static int GPIOUnexport(int pin) {
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open unexport for writing!\n");
        return(-1);
    }
    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

static int GPIODirection(int pin, int dir) {
    static const char s_direction_in[]  = "in";
    static const char s_direction_out[] = "out";
    char path[DIRECTION_MAX];
    int fd;
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    printf("writing path: %s\n", path);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio direction for writing!\n");
        return(-1);
    }
    if (dir == IN) {
        write(fd, &s_direction_in, 2);
    }
    else {
        write(fd, &s_direction_out, 3);
    }
    close(fd);
    return(0);
}

static int GPIORead(int pin) {
    char path[VALUE_MAX];
    char value_str[3];
    int fd;
    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for reading!\n");
        return(-1);
    }
    if (-1 == read(fd, value_str, 3)) {
        fprintf(stderr, "Failed to read value!\n");
        return(-1);
    }
    close(fd);
    return(atoi(value_str));
}

static int GPIOWrite(int pin, int value) {
    static const char s_values_str[] = "01";
    char path[VALUE_MAX];
    int fd;
    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for writing!\n");
        return(-1);
    }
    if (1 != write(fd, &s_values_str[GPIO_LOW == value ? 0 : 1], 1)) {
        fprintf(stderr, "Failed to write value!\n");
        return(-1);
    }
    close(fd);
    return(0);
}

int main (void) {
    WINDOW *mainwin;// *gpiowin;
    int ch;
    int row;
    int col;
    int szx,szy;
    int v, h;
    int i;
    int gpiostate[LIST_MAX];
    char buf[15];
    WINDOW *gpiowinlist[LIST_MAX];

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

    box(mainwin, '|','-');
    //mvwaddstr(gpiowinlist[0], (height) / 2, (width) / 2, buf);
    for (i = 0; i < LIST_MAX; i++) {
        gpiowinlist[i] = subwin(mainwin, sizeh - 1, sizew, y, x + (sizew*i)); //- sizew);//*(i+1)-1);
        //box(gpiowinlist[i], '-', '|');
        wborder(gpiowinlist[i], 176, 176, 176, 176, 176, 176, 176, 176);
        if (i >= 4) {
            gpiowinlist[i] = subwin(mainwin, sizeh - 1, sizew, y + sizeh, x + sizew*(i-4));
            //box(gpiowinlist[i], '-', '|');
            wborder(gpiowinlist[i], 176, 176, 176, 176, 176, 176, 176, 176);
        }
        //box(gpiowinlist[i], 0, 0);
        snprintf(buf, sizeof(buf), "%d", i);
        mvwaddstr(gpiowinlist[i], sizeh / 2, sizew / 2, buf);
        mvwaddstr(gpiowinlist[i], 1, 4, "lololololol");
        //refresh();
    }

    // loop through all windows, set GPIO state to low, print display
    for (i = 0; i < LIST_MAX; i++) {
        gpiostate[i] = GPIO_LOW;
        mvwaddstr(gpiowinlist[i], 3, 3, "OFF");
        GPIOExport(i); // create a /sys/class/gpio/gpioX entry
        // it takes a while to create the gpioX entries so
        // adding 10ms delay
        usleep(100000);
        GPIODirection(i, OUT); // set pin to output
        GPIOWrite(i, GPIO_LOW); // set to '0' output
    }

    refresh();

    i = 0;
    // wbkgd(gpiowinlist[i], COLOR_PAIR(8));
    // color pair to match "active"
    wbkgd(gpiowinlist[i], COLOR_ACTIVE);
    wrefresh(gpiowinlist[i]);
    while ( (ch = getch()) != 'q' ) {
        // testing "enter"
        //fprintf(stdout, "%d\r\n", ch);
        switch (ch) {
            case 'a':
            case KEY_RIGHT:
                wbkgd(gpiowinlist[i], COLOR_INACTIVE);
                wrefresh(gpiowinlist[i]);
                i++;
                if (i >= LIST_MAX ) {
                    i = 0;
                }
                //gpiowinlist[i++];
                //box(gpiowinlist[i++],v, 0);
                wbkgd(gpiowinlist[i], COLOR_ACTIVE);
                //mvwaddstr(gpiowinlist[i], 3, 3, "wat");
                wrefresh(gpiowinlist[i]);
                break;
            case 'd':
            case KEY_LEFT:
                wbkgd(gpiowinlist[i], COLOR_INACTIVE);
                wrefresh(gpiowinlist[i]);
                i--;
                if (i < 0) {
                    i = LIST_MAX-1;
                }
                //gpiowinlist[i--];
                //box(gpiowinlist[i--]);
                wbkgd(gpiowinlist[i], COLOR_ACTIVE);
                //mvwaddstr(gpiowinlist[i], 3, 3, "nah");
                wrefresh(gpiowinlist[i]);
                break;
            case KEY_UP:
                wbkgd(gpiowinlist[i], COLOR_INACTIVE);
                wrefresh(gpiowinlist[i]);
                if ((i > 3) && (i < LIST_MAX)) {
                    i -= 4; // i = i - 4
                }
                else if((i < 4) && (i >= 0)) {
                    i += 4;
                }
                //if (i / (i+4) == 0){
                //    i = i - 4;
                // }
                wbkgd(gpiowinlist[i], COLOR_ACTIVE);
                //mvwaddstr(gpiowinlist[i], 3, 3, "lol");
                wrefresh(gpiowinlist[i]);
                break;
            case KEY_DOWN:
                wbkgd(gpiowinlist[i], COLOR_INACTIVE);
                wrefresh(gpiowinlist[i]);
                if ((i >=0) && (i < 4)){
                    i += 4;
                }
                else if((i < 8) && (i > 3)){
                    i -= 4;
                }
                wbkgd(gpiowinlist[i], COLOR_ACTIVE);
                //mvwaddstr(gpiowinlist[i], 3, 3, "lul");
                wrefresh(gpiowinlist[i]);
                break;
            case 10:
                // handle key press
                if (gpiostate[i] == GPIO_HIGH) {
                    // set to low
                    mvwaddstr(gpiowinlist[i], 3, 3, "OFF");
                    gpiostate[i] = GPIO_LOW;
                    GPIOWrite(i, GPIO_LOW); // set pin to '0'
                }
                else if (gpiostate[i] == GPIO_LOW) {
                    // set to high
                    mvwaddstr(gpiowinlist[i], 3, 3, "ON "); // added extra space to cover up 'OFF'
                    gpiostate[i] = GPIO_HIGH;
                    GPIOWrite(i, GPIO_HIGH); // set pin to '1'
                }
                wrefresh(gpiowinlist[i]);
                break;
            default:
                // always good to define "default" behavior, even if nothing
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

    // cleanup
    for (i = 0; i < LIST_MAX; i++) {
        delwin(gpiowinlist[i]);
        GPIOUnexport(i);
    }

   /* for (i = 1; i++; i < 4) {
        delwin(gpiowinlist[i]);
    }*/
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
