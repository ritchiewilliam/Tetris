#ifndef TETRIS_TEXTURE_H
#define TETRIS_TEXTURE_H
#include <SDL2/SDL_image.h>
#include <iostream>
#include "global.h"

class Texture {
public:
    Texture(SDL_Renderer*, const std::string& path);
    Texture(SDL_Renderer * renderer, const Texture &texture);
    ~Texture();


    void renderTexture(SDL_Renderer *renderer, SDL_Rect canvas, SDL_Rect rect);
    void renderTexture(SDL_Renderer *renderer, SDL_Rect rect);
    void setTexture(SDL_Renderer* renderer, const std::string& path);
    void setColorMod(uint8_t r, uint8_t g, uint8_t b);
    void setAlphaMod(uint8_t a);

private:
    std::string path;
    SDL_Texture* sdlTexture;
    SDL_Surface* sdlSurface;
};
#endif //TETRIS_TEXTURE_H
