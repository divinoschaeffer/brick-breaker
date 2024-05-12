//
// Created by Bryan on 13/04/2024.
//

#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <Ball.h>
#include "Window.h"

class GameLoop {
public:
    SDL_Event event;
    SDL_Color defaultColor;
    SDL_Color selectedColor;
    GameLoop();
    Window win;
    std::vector<Ball> balls;

    void FirstPageLoop();
    void Loop();
    void addBall(Ball& b);
    void applyModifier(const std::shared_ptr<Modifier>& modifier, const std::shared_ptr<std::vector<Brick>>& bricks, Paddle& pad);
    void BonusMultiball();
    void BonusSpeedBall();
    void BonusPaddle(Paddle& pad);
    void MalusPaddle(Paddle& pad);

    ~GameLoop();
};



#endif //GAMELOOP_H
