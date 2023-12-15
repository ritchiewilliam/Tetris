//
// Created by william on 14/12/23.
//

//#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "grid.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Grid grid;
unsigned int * renderedGrid[GRID_X];
int blockDim;
bool running;

void quit() {

    running = false;

    for(unsigned int *& i : renderedGrid) {
        delete(i);
    }
    grid.quit();
    SDL_Quit();
}

bool init(const char * title, int xpos, int ypos, int width, int height, int flags) {
    // initialize SDL
    if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) >= 0) {
        // if succeeded create our window
        window = SDL_CreateWindow(title,
                                  xpos, ypos,
                                  width, height,
                                  flags);

        // if the window creation succeeded create our renderer
        if(window != nullptr){
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer != nullptr) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else {
                std::cout << "Renderer Failed";
                return false;
            }
        }
        else {
            std::cout << "Window Failed";
            return false;
        }

    }
    else
    {
        return false; // sdl could not initialize
    }

    blockDim = width/10;
    blockDim = (blockDim * 20) > height ? height/20 : blockDim;

    for(unsigned int *& i : renderedGrid) {
        i = new unsigned int[GRID_Y];
    }

    return true;
}

void render() {
    grid.getGrid(renderedGrid);
    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            SDL_SetRenderDrawColor(renderer, renderedGrid[i][j] >> 16, (renderedGrid[i][j] >> 8) & 0xFF, renderedGrid[i][j] & 0xFF, 255);
            rect = {i*blockDim, j*blockDim, blockDim, blockDim};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    // show the window
    SDL_RenderPresent(renderer);
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            grid.moveBlock(event.key.keysym.sym);
            render();
        } else if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

bool update() {
    if(!grid.moveBlock(DOWN)) {
        if(grid.placeBlock()) {
            return false;
        }
    }
    render();
    return true;
}

int main() {

    if(init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700 * 2, SDL_WINDOW_SHOWN)) {
        running = true;
    }
    else {
        return 1;
    }

    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    while(running) {
        handleEvents();
        currentTime = SDL_GetTicks();
        if(currentTime - lastTime > 500) {
            running = update();
            lastTime = currentTime;
        }

    }

    quit();
    return 0;
}
