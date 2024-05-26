#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "grid.h"
#include "canvas.h"
#include "texture.h"
#include "button.h"

const int width = 920;
const int height = 1600;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Texture * blockTextures[typeNums];

Grid grid;
int renderedGrid[GRID_X][GRID_Y];
int blockDim;
bool running;

SDL_Rect gridDim = {(width * 21)/100,
                           (height * 125)/ 1000,
                           (width * 75)/100,
                           (width * 75 * 2)/100};

RasteredCanvas gridCanvas = RasteredCanvas(GRID_X, GRID_Y, gridDim, {120, 167, 255, 255}/*{255, 255, 255, 255}*/, 4, {128, 128, 128, 255});

const int nextItemWidth = 175;

SDL_Rect savedDim = {((width * 21) / 200) - ((width * nextItemWidth) / 2000),
				(height * 125) / 1000,
				(width * nextItemWidth) / 1000,
				(width * nextItemWidth) / 1000};

RasteredCanvas savedItemCanvas = RasteredCanvas(5, 5, savedDim,
				{120, 167, 255, 255}/*{255, 255, 255, 255}*/,
				4,
				{128, 128, 128, 255});

RasteredCanvas nextItemCanvas = RasteredCanvas(5, (5 * queueSize), {savedDim.x,
				savedDim.h + savedDim.y + 4 * 3,
				(width * nextItemWidth) / 1000,
				(width * nextItemWidth * queueSize) / 1000},
				{120, 167, 255, 255}/*{255, 255, 255, 255}*/,
				4,
				{128, 128, 128, 255});



//SDL_Rect gridCanvas;

Button * settings;

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
		//120, 167, 255,
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
    else {
        return false; // sdl could not initialize
    }
    return true;
}

void renderGrid() {
    gridCanvas.renderCanvas(renderer);

    grid.getGrid(renderedGrid);
    //SDL_Rect rect;

    for(int i = 0; i < GRID_X; i++) {
        for(int j = 0; j < GRID_Y; j++) {
            //rect = {i*blockDim, j*blockDim, blockDim, blockDim};
            if(renderedGrid[i][j] >= typeNums) {
                int id = renderedGrid[i][j] - typeNums;
                blockTextures[id]->setAlphaMod(127);

                //blockTextures[id]->renderTexture(renderer, gridCanvas, rect);

		gridCanvas.renderRegion(renderer, blockTextures[id], {i, j});

                blockTextures[id]->setAlphaMod(255);
            }
            else if(renderedGrid[i][j] >= 0){
		//gridCanvas.renderTexture(renderer, blockTextures[renderedGrid[i][j]], rect);
		gridCanvas.renderRegion(renderer, blockTextures[renderedGrid[i][j]], {i, j});

                //blockTextures[renderedGrid[i][j]]->renderTexture(renderer, gridCanvas, rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void renderNext() {
    nextItemCanvas.renderCanvas(renderer);

    point dims = nextItemCanvas.getRasterDimensions();

    int center = (dims.x / 2) - (GRID_X / 2);

    int i = 0;

    for(auto & id : grid.getNext()) {
	//std::cout << id << std::endl;
	for(point p : TEMPLATES[id]) {
		p.x = p.x + center;
		p.y = p.y + 1 + i;
		nextItemCanvas.renderRegion(renderer, blockTextures[id], p);

	}
	i = i + dims.x;
    }
}

void renderSaved() {
    savedItemCanvas.renderCanvas(renderer);

    point dims = savedItemCanvas.getRasterDimensions();

    int center = (dims.x / 2) - (GRID_X / 2);

    int id = grid.getSaved();

    if(id != 7) {    
	for(point p : TEMPLATES[id]) {
	    p.x = p.x + center;
	    p.y = p.y + 1;
	    savedItemCanvas.renderRegion(renderer, blockTextures[id], p);

	}
    }
}

void render(unsigned int key) {
	if(key == Direction::SAVE) renderSaved();
	if(key == Direction::SPACE) renderNext();
        renderGrid();
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                grid.moveBlock(event.key.keysym.sym);
		render(event.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                if(settings->hovering(x, y)){
                    settings->renderButton(renderer, 255, 255, 255);
                }
                else {
                    settings->renderButton(renderer, 128, 128, 128);
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
        }
    }

}

bool update() {
    if(!grid.moveBlock(DOWN)) {
        if(!grid.placeBlock()) {
            return false;
        }
	else {
	    renderNext();	
	}
    }
    renderGrid();
    return true;
}

void quit() {
    running = false;
    SDL_Quit();
    for(auto &i : blockTextures) {
	delete(i);
    }
}

int main(int argc, char ** argv) {

    //blockDim = gridCanvas.getDimensions().w/10;

    if(init_sdl("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)) {
        running = true;
    }
    else {
        return 1;
    }

    std::string assetPath = argv[0];
    for(; assetPath[assetPath.length()-1] != '/'; assetPath.pop_back());
    assetPath = assetPath + "assets/";
    assetPath = assetPath + (argc > 1 ? argv[1] : "default") + '/';

    for(int i = 0; i < typeNums; i++) {
        blockTextures[i] = new Texture(renderer, assetPath + blockOrder[i] + ".png");
    }
/*
    for(int *& i : renderedGrid) {
        i = new int[GRID_Y];
    }
*/

    settings = new Button(renderer, Canvas({ gridDim.x + gridDim.w - (gridDim.y / 2),
                              		     gridDim.y/4,
                              		     gridDim.y/2,
                              		     gridDim.y/2 }), assetPath + "settings.png");

    Uint32 capTimer;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;

    settings->renderButton(renderer, 255, 255, 255);
    renderNext();
    renderSaved();
    while(running) {
        capTimer = SDL_GetTicks();
        handleEvents();
        currentTime = SDL_GetTicks();
        if(currentTime - lastTime > 500) {
            running = update();
            lastTime = currentTime;
        }
        capTimer = SDL_GetTicks() - capTimer;
        if( capTimer < SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - capTimer );
        }
    }

    quit();

    return 0;
}
