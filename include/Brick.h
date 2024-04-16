#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>

class Brick {
public:
    Brick(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color);

    void draw() const;
    bool isDestroyed() const;
    void destroy();

    // Méthodes getters pour obtenir la position et la taille de la brique
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Color color;
    bool destroyed;
};

#endif /* BRICK_H */
