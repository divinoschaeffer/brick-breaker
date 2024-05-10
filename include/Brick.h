#ifndef BRICK_H
#define BRICK_H

#include <vector>
#include <SDL2/SDL.h>
#include <memory>

class Brick {
public:
    Brick(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h, SDL_Color color, int hitPoints = 2);

    void draw() const;
    void hit(); // Méthode pour indiquer qu'une brique a été touchée
    bool isDestroyed() const;

    // Méthodes getters pour obtenir la position et la taille de la brique
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    int getHitPoints() const;
    void setColor(const SDL_Color& color);
    
protected:
    std::shared_ptr<SDL_Renderer> renderer;
    SDL_Rect rect;
    SDL_Color color;
    int hitPoints; // Nombre de points de vie de la brique
};

#endif /* BRICK_H */
