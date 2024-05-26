//
// Created by william on 29/12/23.
//

#include "button.h"

Button::Button(SDL_Renderer *renderer, const Canvas& canvas, const std::string &path){
    this->canvas = new Canvas(canvas);
    this->texture = new Texture(renderer, path);
}

Button::~Button() {
    delete(texture);
}

bool Button::hovering(int x, int y) {
    SDL_Rect dim = canvas->getDimensions();
    return x > dim.x && x < dim.x + dim.w && y > dim.y && y < dim.y + dim.h;
}

void Button::renderButton(SDL_Renderer * renderer, uint8_t r, uint8_t g, uint8_t b) {
    texture->setColorMod(r, g, b);
    texture->renderTexture(renderer, {0,0,0,0}, canvas->getDimensions());
    SDL_RenderPresent(renderer);
}

void Button::onClick() {

}
