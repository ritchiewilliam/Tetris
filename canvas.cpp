#include "canvas.h"

Canvas::Canvas(SDL_Rect dimensions, SDL_Color backgroundColor, int borderWidth, SDL_Color borderColor) {
    this->dimensions = dimensions;
    this->backgroundColor = backgroundColor;
    this->borderWidth = (borderWidth > 0) * borderWidth;
    this->borderColor = borderColor;
}

Canvas::Canvas(const Canvas& canvas) {
    (*this) = canvas;
}

void Canvas::operator=(const Canvas& canvas) {
    dimensions = canvas.dimensions;
    backgroundColor = canvas.backgroundColor;
    borderWidth = canvas.borderWidth;
    borderColor = canvas.borderColor;
}

void Canvas::renderTexture(SDL_Renderer * renderer, Texture * texture, SDL_Rect rect) {
    rect.x += dimensions.x;
    rect.y += dimensions.y;
    
    texture->renderTexture(renderer, rect);
}

void Canvas::renderCanvas(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &dimensions);

    if(borderWidth) {
	for(int i = 0; i < borderWidth; i++) {
		SDL_Rect temp = dimensions;
		temp.x = temp.x - i;
		temp.y = temp.y - i;
		temp.w = temp.w + (2 * i);
		temp.h = temp.h + (2 * i);

		SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderDrawRect(renderer, &temp);
	}
    }
}

SDL_Rect Canvas::getDimensions() {
    return dimensions;
}

RasteredCanvas::RasteredCanvas(int w, int h, SDL_Rect dimensions, SDL_Color backgroundColor, int borderWidth, SDL_Color borderColor): Canvas(dimensions, backgroundColor, borderWidth, borderColor) {
    
    rasterDim = {w, h};
    
    regionWidth = dimensions.w/rasterDim.x;
    regionHeight = dimensions.h/rasterDim.y;
}

void RasteredCanvas::renderRegion(SDL_Renderer * renderer, Texture * texture, point p) {
    if(p.x > rasterDim.x || p.x < 0 || p.y > rasterDim.y || p.y < 0) {
	return;
    }
    texture->renderTexture(renderer, {dimensions.x + (p.x * regionWidth),
				      dimensions.y + (p.y * regionHeight),
				      regionWidth, regionHeight});
}

point RasteredCanvas::getRasterDimensions() {
    return rasterDim;
}

/*
SDL_Color Canvas::getBackgroundColor() {
    return backgroundColor;
}

int Canvas::getBorderWidth() {
    return borderWidth;
}

SDL_Color Canvas::getBorderColor() {
    return borderColor;
}

void Canvas::setDimensions(SDL_Rect dimensions) {
    this->dimensions = dimensions;
}
*/
