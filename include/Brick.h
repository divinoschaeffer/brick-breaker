#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>

class Brick {
public:
    Brick(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color, int hitPoints = 2); // Défaut à 2 points de vie

    void draw() const;
    void hit(); // Méthode pour indiquer qu'une brique a été touchée
    bool isDestroyed() const;

    // Méthodes getters pour obtenir la position et la taille de la brique
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    int getHitPoints() const;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Color color;
    int hitPoints; // Nombre de points de vie de la brique
};

#endif /* BRICK_H */
