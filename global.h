#ifndef TETRIS_GLOBAL_H
#define TETRIS_GLOBAL_H
#include <SDL2/SDL_keycode.h>
const int typeNums = 7;
enum Direction {UP = SDLK_UP, DOWN = SDLK_DOWN, LEFT = SDLK_LEFT, RIGHT = SDLK_RIGHT, SPACE = SDLK_SPACE, SAVE = SDLK_c};

const unsigned int COLORS[7] {
        0x00FFFF, //I - cyan
        0xFFFF00, //O - yellow
        0x800080, //T - purple
        0xFF7F00, //L - orange
        0x0000FF, //J - blue
        0x00FF00, //S - green
        0xFF0000  //Z - red
};

#endif //TETRIS_GLOBAL_H
