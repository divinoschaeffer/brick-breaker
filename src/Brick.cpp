#include "Brick.h"

Brick::Brick(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color)
    : renderer(renderer), rect({x, y, w, h}), color(color), destroyed(false) {}

void Brick::draw() const {
    if (!destroyed) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Brick::isDestroyed() const {
    return destroyed;
}

void Brick::destroy() {
    destroyed = true;
}

int Brick::getX() const {
    return rect.x;
}

int Brick::getY() const {
    return rect.y;
}

int Brick::getW() const {
    return rect.w;
}

int Brick::getH() const {
    return rect.h;
}
