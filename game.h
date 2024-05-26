//
// Created by william on 14/12/23.
//

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include "grid.h"

class Game {
    // simply set the running variable to true
    bool init(const char *title, int xpos, int ypos, int width, int height, int flags);

    void render();
    void update();
    void handleEvents();
    void clean();

    // a function to access the private running variable
    bool isRunning() { return running; }

    void start() { running = true; }

    void stop() { running = false; }

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface * surface = nullptr;

    bool running;

    Grid grid;
    unsigned int * renderedGrid[GRID_X];
    int blockDim;

};


#endif //TETRIS_GAME_H
