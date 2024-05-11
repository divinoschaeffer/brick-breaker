#ifndef BRICK_H
#define BRICK_H

#include <vector>
#include <SDL2/SDL.h>
#include "Modifier.h"
#include <memory>

class Brick {
public:
    Brick(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h, SDL_Color color, int hitPoints = 2);
    Brick(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h, SDL_Color color, const std::shared_ptr<Modifier>& modifier, int hitPoints = 2);

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
    void setModifier(const std::shared_ptr<Modifier>& modifier);
    std::shared_ptr<Modifier> getModifier() const;
    
protected:
    std::shared_ptr<SDL_Renderer> renderer;
    SDL_Rect rect;
    SDL_Color color;
    int hitPoints; // Nombre de points de vie de la brique
    std::shared_ptr<Modifier> modifier;
};

#endif /* BRICK_H */
