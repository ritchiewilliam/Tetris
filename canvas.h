//
// Created by william on 02/01/24.
//

#ifndef TETRIS_CANVAS_H
#define TETRIS_CANVAS_H
#include <SDL2/SDL.h>
#include "global.h"
#include "texture.h"

class Canvas {
public:
    Canvas(SDL_Rect dimensions, SDL_Color backgroundColor = {0, 0, 0, 255}, int borderWidth = 0, SDL_Color borderColor = {0, 0, 0, 0});

    Canvas(const Canvas& canvas);
    void operator=(const Canvas& canvas);

    void renderTexture(SDL_Renderer * renderer, Texture * texture, SDL_Rect rect);
    void renderCanvas(SDL_Renderer * renderer);

    SDL_Rect getDimensions();
    SDL_Color getBackgroundColor();
    int getBorderWidth();
    SDL_Color getBorderColor();
    //void drawText
    //void

protected:
    SDL_Rect dimensions;

    SDL_Color backgroundColor;

    int borderWidth;
    SDL_Color borderColor;
};

class RasteredCanvas : public Canvas{
public:
    RasteredCanvas(int w, int h, SDL_Rect dimensions, SDL_Color backgroundColor = {0, 0, 0, 255},
		  int borderWidth = 0, SDL_Color borderColor = {0, 0, 0, 0});

    void renderRegion(SDL_Renderer * renderer, Texture * texture, point p);

    point getRasterDimensions();

private:

    point rasterDim;

    int regionWidth;
    int regionHeight;
};


#endif //TETRIS_CANVAS_H
