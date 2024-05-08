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

class GameLoop {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* defaultFont;
    TTF_Font* selectedFont;
    SDL_Event event;
    SDL_Color defaultColor;
    SDL_Color selectedColor;
    GameLoop();
    std::vector<Ball> balls;

    void WindowInit();
    void FirstPageLoop();
    void Loop();
    void addBall(Ball& b);
    ~GameLoop();
};



#endif //GAMELOOP_H
