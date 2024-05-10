//
// Created by Bryan on 15/04/2024.
//

#include "Ball.h"

Ball::Ball() : paddle(Paddle(nullptr, 0, 0, 0, 0)) {
    position = Vector2(0, 0);
    velocity = Vector2(1, -1);
    radius = 10.0f;
    speed = 10.0f;
    color = {255, 255, 255, 255}; // White color
    texture = nullptr; // Will be set later
    paddle = Paddle(nullptr, 0, 0, 0, 0);
}

 // Constructeur de copie
    Ball::Ball(const Ball& other) : 
        position(other.position),
        velocity(other.velocity),
        radius(other.radius),
        speed(other.speed),
        color(other.color),
        texture(nullptr), // Will be set later
        bricks(other.bricks), // Copying the pointer, not the data
        paddle(other.paddle) // Copying the Paddle object
    {}

Vector2 Ball::getPosition(){
    return this->position;
}

// Implémentation du constructeur avec spécification de paddle et bricks
Ball::Ball(Paddle& pdl, std::shared_ptr<std::vector<Brick>> brs) :
    paddle(pdl),
    bricks(brs)
{
    // Les autres attributs sont initialisés avec des valeurs par défaut
    position = Vector2(320, 240);
    velocity = Vector2(0, 1);
    radius = 10.0f;
    speed = 10.0f;
    color = {255, 0, 0, 255}; // White color
    texture = nullptr; // Will be set later
}

void Ball::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, position.x + dx, position.y + dy);
            }
        }
    }
}

void Ball::updatePosition(int screenWidth, int screenHeight) {
    position = position + velocity * speed;
    checkCollision(screenWidth, screenHeight);
    checkEveryBricks();
}

void Ball::checkCollision(int screenWidth, int screenHeight) {
    if (position.x - radius < 0 || position.x + radius > screenWidth) {
        velocity.x = -velocity.x; // Invert x velocity
    } else if (position.y - radius < 0) {
        velocity.y = -velocity.y; // Invert y velocity
    } else if ((position.x + radius >= paddle.getX() && position.x - radius <= paddle.getX() + paddle.getW()) &&
            (position.y - radius <= paddle.getY() + paddle.getH() / 2 && position.y + radius >= paddle.getY()))
    {
        // Calculate the distance between the ball and the center of the paddle
        float distance = position.x - (paddle.getX() + paddle.getW() / 2);

        // Calculate the speed factor based on the distance
        float speedFactor = distance / (paddle.getW() / 2);

        // Apply the speed factor to the ball's velocity
        velocity.y = -velocity.y;
        velocity.x = speedFactor;
    }
    /*
    else if ((position.y >= paddle.getY() - paddle.getH() / 2 && position.y <= paddle.getY() + paddle.getH() / 2) &&
        (position.x - radius <= paddle.getX() + paddle.getW() / 2 && position.x + radius >= paddle.getX() - paddle.getW() / 2))
    {
        velocity.x = -velocity.x;
    }*/

}

// Check every bricks from the list
void Ball::checkEveryBricks() {
    int brickHeight = (*bricks)[0].getH();
    int brickWidth = (*bricks)[0].getW();


    for (auto& brick : *bricks) {
        if ((position.x >= brick.getX() && position.x <= brick.getX() + brickWidth) &&
            (position.y - radius <= brick.getY() + brickHeight && position.y + radius >= brick.getY()))
        {
            brick.hit();
            velocity.y = -velocity.y;
            return;
        }
        else if ((position.y >= brick.getY() && position.y <= brick.getY() + brickHeight) &&
            (position.x - radius <= brick.getX() + brickWidth && position.x + radius >= brick.getX()))
        {
            brick.hit();
            velocity.x = -velocity.x;
            return;
        }
    }
}

bool::Ball::isOut(int height) const {
    return position.y > height;
}