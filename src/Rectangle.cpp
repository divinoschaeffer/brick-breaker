#include "Rectangle.h"

Rectangle::Rectangle(SDL_Renderer* renderer, int x, int y, int w, int h)
    : renderer(renderer), rect({x, y, w, h}) {
    color = {255, 255, 255, 255}; // Initialisation de la couleur par défaut
}

void Rectangle::draw() const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Rectangle::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

void Rectangle::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Rectangle::setSize(int w, int h) {
    rect.w = w;
    rect.h = h;
}

int Rectangle::getX() const {
    return rect.x;
}

int Rectangle::getY() const {
    return rect.y;
}
