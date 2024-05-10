#ifndef PADDLE_H
#define PADDLE_H

#include <Rectangle.h> // Inclure la classe Rectangle
#include <Vector2.h>

class Paddle : public Rectangle {
public:
    Vector2 velocity;
    // Constructeur : appelle le constructeur de la classe de base Rectangle
    Paddle(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int w, int h);

    // Méthode pour déplacer le pad vers la gauche
    void moveLeft(int speed, int window_width);

    // Méthode pour déplacer le pad vers la droite
    void moveRight(int speed, int window_width);

    void updatePosition(int speed, int window_width);
};

#endif /* PADDLE_H */
