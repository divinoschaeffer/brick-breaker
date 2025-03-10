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
    paddle = Paddle(nullptr, 0, 0, 0, 0);
}

 // Constructeur de copie
    Ball::Ball(const Ball& other) : 
        position(other.position),
        velocity(other.velocity),
        radius(other.radius),
        speed(other.speed),
        color(other.color),
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
}

void Ball::draw(const std::shared_ptr<SDL_Renderer>& renderer) const {
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer.get(), position.x + dx, position.y + dy);
            }
        }
    }
}

void Ball::updatePosition(int screenWidth, int screenHeight) {
    position = position + velocity * speed;
    checkCollision(screenWidth, screenHeight);
    if(!(*bricks).empty())checkEveryBricks();
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

SDL_Color decreaseBrightness(const SDL_Color& color, const int& amount) {
    int r = color.r - amount;
    int g = color.g - amount;
    int b = color.b - amount;

    // Assurez-vous que les valeurs restent dans la plage [0, 255]
    r = std::max(0, std::min(r, 255));
    g = std::max(0, std::min(g, 255));
    b = std::max(0, std::min(b, 255));

    return {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), color.a};
}

// Check every bricks from the list
void Ball::checkEveryBricks() {
    int brickHeight = (*bricks)[0].getH();
    int brickWidth = (*bricks)[0].getW();


    auto processBrickCollision = [&](Brick& brick, bool hitXAxis) {
        brick.hit();
        if (brick.getModifier()) 
            brick.setColor(decreaseBrightness(brick.getColor(), 30));
        if (hitXAxis)
            velocity.x = -velocity.x;
        else
            velocity.y = -velocity.y;
    };

    for (auto& brick : *bricks) {
        if ((position.x >= brick.getX() && position.x <= brick.getX() + brickWidth) &&
            (position.y - radius <= brick.getY() + brickHeight && position.y + radius >= brick.getY()))
        {
            processBrickCollision(brick, false);
            return;
        }
        else if ((position.y >= brick.getY() && position.y <= brick.getY() + brickHeight) &&
                (position.x - radius <= brick.getX() + brickWidth && position.x + radius >= brick.getX()))
        {
            processBrickCollision(brick, true);
            return;
        }
    }
}

bool::Ball::isOut(int height) const {
    return position.y > height;
}

void Ball::setPaddle(Paddle& pad){
    paddle = pad;
}

void Ball::setPostion(const int &x, const int &y)
{
    this->position.x = x;
    this->position.y = y;
}

void Ball::setSpeed(float speed)
{
    this->speed = speed;
}

float Ball::getSpeed()
{
    return speed;
}
