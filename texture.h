#ifndef TETRIS_TEXTURE_H
#define TETRIS_TEXTURE_H
#include <SDL2/SDL_image.h>
#include <iostream>
#include "global.h"

class Texture {
public:
    Texture(SDL_Renderer*, std::string path, const char* name);
    int setTexture(const char*, SDL_Renderer*);
    void renderTexture(SDL_Renderer*, SDL_Rect*, int);
    void quit();
private:
    std::string path;
    int loaded = 0;
    SDL_Surface* surfaces[typeNums];
    SDL_Texture* textures[typeNums];
//    SDL_Rect dimensions;
};
#endif //TETRIS_TEXTURE_H
