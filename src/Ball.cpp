//
// Created by Bryan on 15/04/2024.
//

#include "Ball.h"

Ball::Ball() {
    position = Vector2(0, 0);
    velocity = Vector2(1, -1);
    radius = 10.0f;
    speed = 10.0f;
    color = {255, 255, 255, 255}; // White color
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

void Ball::updatePosition(int DeltaTime, int screenWidth, int screenHeight) {
    position = position + (velocity * speed * DeltaTime);
    checkCollision(screenWidth, screenHeight);
}

void Ball::checkCollision(int screenWidth, int screenHeight) {
    if (position.x - radius < 0 || position.x + radius > screenWidth) {
        velocity.x = -velocity.x; // Invert x velocity
    } else if (position.y - radius < 0) {
        velocity.y = -velocity.y; // Invert y velocity
    } /* else if
    {
        // Check collision with other objects
    } */
}
