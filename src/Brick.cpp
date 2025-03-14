#include "Brick.h"

Brick::Brick(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h, SDL_Color color, int hitPoints)
    : renderer(renderer), rect({x, y, w, h}), color(color), hitPoints(hitPoints) {
        modifier = nullptr;
    }

Brick::Brick(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h, SDL_Color color,const std::shared_ptr<Modifier>& modifier, int hitPoints)
    : renderer(renderer), rect({x, y, w, h}), color(color), hitPoints(hitPoints), modifier(modifier){}

void Brick::draw() const {
    if (!isDestroyed()) {
        SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer.get(), &rect);
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

void Brick::setColor(const SDL_Color& color){
    this->color = color;
}

SDL_Color Brick::getColor()
{
    return color;
}

void Brick::setModifier(const std::shared_ptr<Modifier>& modifier){
    this->modifier = modifier;
}

std::shared_ptr<Modifier> Brick::getModifier() const
{
    return modifier;
}