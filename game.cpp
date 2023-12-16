#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "grid.h"
#include "texture.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Texture *textures = nullptr;

Grid grid;
int * renderedGrid[GRID_X];
int blockDim;
bool running;

void quit() {
    running = false;

    for(int *& i : renderedGrid) {
        delete(i);
    }
    grid.quit();
    textures->quit();
    SDL_Quit();
}

bool init_sdl(const char * title, int xpos, int ypos, int width, int height, int flags) {
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
    return true;
}

void render() {
    grid.getGrid(renderedGrid);
    SDL_Rect rect;

//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            rect = {i*blockDim, j*blockDim, blockDim, blockDim};
            textures->renderTexture(renderer, &rect, renderedGrid[i][j]);
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

int main(int argc, char ** argv) {
    int width = 700;
    int height = width * 2;

    if(init_sdl("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)) {
        running = true;
    }
    else {
        return 1;
    }
//    std::string path = argv[0];
    if(argc > 1) {
        textures = new Texture(renderer, argv[0], argv[1]);
    }
    else {
        textures = new Texture(renderer, argv[0], nullptr);
    }
    blockDim = width/10;
    blockDim = (blockDim * 20) > height ? height/20 : blockDim;

    for(int *& i : renderedGrid) {
        i = new int[GRID_Y];
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
