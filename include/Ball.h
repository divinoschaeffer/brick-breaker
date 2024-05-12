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
protected:
    Vector2 position;
    Vector2 velocity;
    float radius;
    float speed;
    SDL_Color color;
    std::shared_ptr<std::vector<Brick>> bricks;
    Paddle paddle;

public:
    Ball();
    Ball(const Ball& other);
    // Constructeur avec spécification de paddle et bricks
    Ball(Paddle& pdl, std::shared_ptr<std::vector<Brick>> brs);
    void draw(const std::shared_ptr<SDL_Renderer>& renderer) const;
    void checkCollision(int screenWidth, int screenHeight);
    void checkEveryBricks();
    void updatePosition(int screenWidth, int screenHeight);
    bool isOut(int height) const;
    Vector2 getPosition();
    void setPaddle(Paddle& pad);
    void setPostion(const int& x, const int& y);
    void setSpeed(float speed);
    float getSpeed();
};



#endif //BALL_H
