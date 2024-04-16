#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>

class Rectangle {
public:
    Rectangle(SDL_Renderer* renderer, int x, int y, int w, int h);

    void draw() const;
    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void setPosition(int x, int y);
    void setSize(int w, int h);

    // Méthodes getters pour obtenir la position du rectangle
    int getX() const;
    int getY() const;

    int getW() const;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Color color;
};

#endif /* RECTANGLE_H */
