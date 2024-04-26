#include "Paddle.h"

// Définition du constructeur
Paddle::Paddle(SDL_Renderer* renderer, int x, int y, int w, int h)
    : Rectangle(renderer, x, y, w, h) {}

// Définition de la méthode pour déplacer le pad vers la gauche
void Paddle::moveLeft(int speed, int window_width) {
    if(getX() - speed > 0)
        setPosition(getX() - speed, getY());
}

// Définition de la méthode pour déplacer le pad vers la droite
void Paddle::moveRight(int speed, int window_width) {
    if(getX() + speed +  getW() < window_width)
        setPosition(getX() + speed, getY());
}

int positiveModulo(int i, int n) {
    int result = i % n;
    if (result < 0) {
        result += n;
    }
    return result;
}

void Paddle::updatePosition(int speed, int window_width) {
    int newX = (getX() + static_cast<int>(velocity.x) * speed) % (window_width + getW());
    if (getX() + getW() < 0)
        setPosition(positiveModulo(getX() + static_cast<int>(velocity.x) * 10, (window_width + getW())), getY());
    else
        setPosition(newX, getY());
}

