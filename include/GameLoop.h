//
// Created by Bryan on 13/04/2024.
//

#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

class GameLoop {
public:
    GameLoop();

    static void Window();
    static void Loop();
};



#endif //GAMELOOP_H
