#include "Rectangle.h"

Rectangle::Rectangle(const std::shared_ptr<SDL_Renderer>& renderer, const int& x, const int& y, const int& w, const int& h)
    : renderer(renderer), color{255, 255, 255, 255} {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Rectangle::draw() const {
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &rect);
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

int Rectangle::getW() const {
    return rect.w;
}

int Rectangle::getH() const {
    return rect.h;
}
