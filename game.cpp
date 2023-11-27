#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>
#include <csignal>
#include "grid.h"

const int WIDTH = 700;
const int HEIGHT = 2 * WIDTH;

int blockDim;

Display * dpy;
Window win;
GC gc;

Grid grid;
unsigned int * paintedGrid[GRID_X];

struct timespec t_begin;
struct timespec t_end;
int gameover = 0;

inline void init() {
    dpy = XOpenDisplay(nullptr);
    win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, WIDTH, HEIGHT, 0, WhitePixel(dpy, 0), BlackPixel(dpy, 0));
    gc = XCreateGC(dpy, win, 0, nullptr);

    XMapWindow(dpy, win);
    blockDim = WIDTH/10;
    blockDim = (blockDim * 20) > HEIGHT ? HEIGHT/20 : blockDim;
}

void paintGrid(/*unsigned int ** result*/) {
    grid.getGrid(paintedGrid);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            XSetForeground(dpy,gc, paintedGrid[i][j]);
            XFillRectangle(dpy, win, gc, i*blockDim, j*blockDim, blockDim, blockDim);
        }
    }
//    XFlush(dpy);
}

void timedMove(int signum) {
    clock_gettime(CLOCK_TAI, &t_end);
    long d = ((t_end.tv_sec * 1000) + (t_end.tv_nsec / 1000000)) - ((t_begin.tv_sec * 1000) + (t_begin.tv_nsec / 1000000));
    if(!grid.moveBlock(DOWN) && d > 200) {
        gameover = grid.placeBlock();
    }
    paintGrid();
    XFlush(dpy);

    if(gameover){
        exit(0);
    }
    else {
        ualarm(500000, 0);
    }
}

int main() {

    init();


    XEvent event;
    XSelectInput(dpy, win, KeyPressMask);

    for(unsigned int *& i : paintedGrid) {
        i = new unsigned int[GRID_Y];
    }

    signal(SIGALRM, timedMove);

    ualarm(500000, 0);

    while(1) {
        XNextEvent(dpy, &event);
        clock_gettime(CLOCK_TAI, &t_begin);
        if(event.type == KeyPress) {
            grid.moveBlock(event.xkey.keycode);
            paintGrid();
        }

    }
    XCloseDisplay(dpy);

    return 0;
}
