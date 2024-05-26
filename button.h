//
// Created by william on 29/12/23.
//

#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H
#include "texture.h"
#include "canvas.h"

class Button {

public:
    Button(SDL_Renderer *renderer, const Canvas& canvas, const std::string &path);
    ~Button();
    bool hovering(int x, int y);
    void onClick();
    void onHover();
    void renderButton(SDL_Renderer * renderer, uint8_t r, uint8_t g, uint8_t b);

private:
    Canvas * canvas;
    Texture * texture;
};


#endif //TETRIS_BUTTON_H
