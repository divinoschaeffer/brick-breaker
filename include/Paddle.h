#ifndef PADDLE_H
#define PADDLE_H

#include "Rectangle.h" // Inclure la classe Rectangle

class Paddle : public Rectangle {
public:
    // Constructeur : appelle le constructeur de la classe de base Rectangle
    Paddle(SDL_Renderer* renderer, int x, int y, int w, int h);

    // Méthode pour déplacer le pad vers la gauche
    void moveLeft(int speed, int window_width);

    // Méthode pour déplacer le pad vers la droite
    void moveRight(int speed, int window_width);
};

#endif /* PADDLE_H */
