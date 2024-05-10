//
// Created by Bryan on 15/04/2024.
//

#ifndef BALL_H
#define BALL_H

#include <Vector2.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <Brick.h>
#include <vector>
#include <Paddle.h>

class Ball {
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    float speed;
    SDL_Color color;
    SDL_Texture* texture; // Texture de la balle si on en met une
    std::shared_ptr<std::vector<Brick>> bricks;
    Paddle paddle;

    Ball();
    Ball(const Ball& other);
    // Constructeur avec spécification de paddle et bricks
    Ball(Paddle& pdl, std::shared_ptr<std::vector<Brick>> brs);
    void getTexture();
    void draw(SDL_Renderer* renderer) const;
    void checkCollision(int screenWidth, int screenHeight);
    void checkEveryBricks();
    void updatePosition(int screenWidth, int screenHeight);
    bool isOut(int height) const;
    Vector2 getPosition();
};



#endif //BALL_H
