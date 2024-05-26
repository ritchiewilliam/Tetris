#include "texture.h"

Texture::Texture(SDL_Renderer * renderer, const std::string& newPath) {

    path = newPath;

    sdlSurface = IMG_Load(path.c_str());
    if(sdlSurface == nullptr) {
        std::cout << "Error Loading images\n";
    }
    sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
    if(sdlTexture == nullptr) {
        std::cout << "Error creating textures\n";
    }
}

Texture::Texture(SDL_Renderer * renderer, const Texture &texture) {
    path = texture.path;
    sdlSurface = IMG_Load(texture.path.c_str());
    sdlTexture = SDL_CreateTextureFromSurface(renderer, texture.sdlSurface);
}

void Texture::setTexture(SDL_Renderer * renderer, const std::string& newPath) {
    if(sdlSurface != nullptr) {
        SDL_FreeSurface(sdlSurface);
    }
    sdlSurface = IMG_Load(newPath.c_str());

    if(sdlTexture != nullptr) {
        SDL_DestroyTexture(sdlTexture);
    }
    sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
}

void Texture::renderTexture(SDL_Renderer * renderer, SDL_Rect canvas, SDL_Rect rect) {

    rect.x += canvas.x;
    rect.y += canvas.y;

    SDL_RenderCopy(renderer, sdlTexture, nullptr, &rect);
}

void Texture::renderTexture(SDL_Renderer * renderer, SDL_Rect rect) {

    SDL_RenderCopy(renderer, sdlTexture, nullptr, &rect);
}

void Texture::setColorMod(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(sdlTexture, r, g, b);
}

void Texture::setAlphaMod(uint8_t a) {
    SDL_SetTextureAlphaMod(sdlTexture, a);
}

//void Texture::reloadTexture(SDL_Renderer * renderer, ) {
//
//}

//void Texture::renderTexture(SDL_Renderer * renderer, SDL_Rect * rect, int id) {
//    if(id >= typeNums) {
//        id = id - typeNums;
//        SDL_SetTextureColorMod(textures[id], 127, 127, 127);
//        SDL_RenderCopy(renderer, textures[id], nullptr, rect);
//        SDL_SetTextureColorMod(textures[id], 255, 255, 255);
//    }
//    else {
//        SDL_RenderCopy(renderer, textures[id], nullptr, rect);
//    }
//}

//bool Texture::setTexture(SDL_Renderer * renderer, const char * asset) {



/*    if(loaded) {
        for(int i = 0; i < loaded; i++) {
            SDL_FreeSurface(surfaces[i]);
            SDL_DestroyTexture(textures[i]);
        }
    }

    char letters[typeNums] = {'i', 'o', 't', 'l', 'j', 's', 'z'};

    std::string texturePath = path + name + "/x.png";
    uint length = texturePath.length();
    for(int i = 0; i < typeNums; i++) {
        texturePath[length - 5] = letters[i];
        surfaces[i] = IMG_Load(texturePath.c_str());
        if(surfaces[i] == nullptr) {
            std::cout << "Error Loading images\n";
            return i;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
        if(textures[i] == nullptr) {
            std::cout << "Error creating textures\n";
            return i;
        }
    }*/



//    return surface == nullptr;
//}

Texture::~Texture(){
    SDL_FreeSurface(sdlSurface);
    SDL_DestroyTexture(sdlTexture);
}