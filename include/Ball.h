//
// Created by Bryan on 15/04/2024.
//

#ifndef BALL_H
#define BALL_H

#include <Vector2.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class Ball {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 direction;
    Vector2 lastImpact;
    float radius;
    float speed;
    SDL_Color color;
    SDL_Texture* texture; // Texture de la balle si on en met une

    Ball();
    void getTexture();
    void draw(SDL_Renderer* renderer) const;
    void checkCollision(int screenWidth, int screenHeight);
    void updatePosition(int DeltaTime, int screenWidth, int screenHeight);
};



#endif //BALL_H
