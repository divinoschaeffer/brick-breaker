#include "Brick.h"

Brick::Brick(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color, int hitPoints)
    : renderer(renderer), rect({x, y, w, h}), color(color), hitPoints(hitPoints) {}

void Brick::draw() const {
    if (!isDestroyed()) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Brick::hit() {
    hitPoints--;
}

bool Brick::isDestroyed() const {
    return hitPoints <= 0;
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

int Brick::getHitPoints() const {
    return hitPoints;
}
