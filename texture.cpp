#include "texture.h"

Texture::Texture(SDL_Renderer * renderer, std::string path, const char * name) {
    for(; path[path.length()-1] != '/'; path.pop_back());
    this->path = path + "assets/";
    if(name != nullptr) {
        loaded = setTexture(name, renderer);
    }
    if(loaded < typeNums) {
        loaded = setTexture("default", renderer);
    }
}

void Texture::renderTexture(SDL_Renderer * renderer, SDL_Rect * rect, int id) {
    if(id >= typeNums) {
        id = id - typeNums;
        SDL_SetTextureColorMod(textures[id], 127, 127, 127);
        SDL_RenderCopy(renderer, textures[id], nullptr, rect);
        SDL_SetTextureColorMod(textures[id], 255, 255, 255);
    }
    else {
        SDL_RenderCopy(renderer, textures[id], nullptr, rect);
    }
}

int Texture::setTexture(const char * name, SDL_Renderer * renderer) {
    if(loaded) {
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
    }
    return typeNums;
}

void Texture::quit(){
    for(int i = 0; i < loaded; i++) {
        SDL_FreeSurface(surfaces[i]);
        SDL_DestroyTexture(textures[i]);
    }
}
