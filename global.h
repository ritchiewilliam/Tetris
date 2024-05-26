#ifndef TETRIS_GLOBAL_H
#define TETRIS_GLOBAL_H
#include <SDL2/SDL_keycode.h>

const int GRID_Y = 20;
const int GRID_X = 10;  

const int queueSize = 4;
const int blockSize = 4;
const int typeNums = 7;

enum Direction {UP = SDLK_UP, DOWN = SDLK_DOWN, LEFT = SDLK_LEFT, RIGHT = SDLK_RIGHT, SPACE = SDLK_SPACE, SAVE = SDLK_c};

const char blockOrder[typeNums] {
    'i', 'o', 't', 'l', 'j', 's', 'z'
};

const unsigned int COLORS[typeNums] {
        0x00FFFF, //I - cyan
        0xFFFF00, //O - yellow
        0x800080, //T - purple
        0xFF7F00, //L - orange
        0x0000FF, //J - blue
        0x00FF00, //S - green
        0xFF0000  //Z - red
};

typedef struct{
    int x;
    int y;
} point;

const point TEMPLATES[7][blockSize] { //Note: PIVOT IS ALWAYS FIRST VALUE
            {{5,1}, {5,0}, {5,2}, {5,3}}, //I
            {{5,1}, {5,0}, {6,0}, {6,1}}, //O
            {{5,1}, {5,0}, {4,1}, {6,1}}, //T
            {{5,1}, {5,0}, {5,2}, {6,2}}, //L
            {{5,1}, {5,0}, {5,2}, {4,2}}, //J
            {{5,1}, {5,0}, {4,1}, {6,0}}, //S
            {{5,1}, {5,0}, {6,1}, {4,0}}  //Z
    };


#endif //TETRIS_GLOBAL_H
