//
// Created by Bryan on 13/04/2024.
//

#include <vector>
#include "HelloWorld.h"
#include "Paddle.h"
#include "Brick.h"

#define WINDOW_X 640
#define WINDOW_Y 480
#define PAD_W 100
#define PAD_H 10
#define PAD_SPEED 60

// Fonction pour créer une liste de briques
std::vector<Brick> createBrickList(SDL_Renderer* renderer, int windowWidth, int brickWidth, int brickHeight) {
    std::vector<Brick> bricks;

    // Nombre de briques par ligne
    int bricksPerRow = windowWidth / brickWidth;

    // Espace horizontal entre les briques
    int horizontalSpace = (windowWidth - bricksPerRow * brickWidth) / (bricksPerRow + 1);

    // Position initiale des briques sur l'axe horizontal
    int initialX = horizontalSpace;

    // Position initiale des briques sur l'axe vertical
    int initialY = 10; // Réglage de la position verticale initiale des briques

    // Créer deux lignes de briques en haut de la fenêtre
    for (int row = 0; row < 4; ++row) {
        for (int i = 0; i < bricksPerRow; ++i) {
            int x = initialX + i * (brickWidth + horizontalSpace);
            int y = initialY + row * (brickHeight + 10); // Espacement vertical entre les lignes de briques
            Brick brick(renderer, x, y, brickWidth, brickHeight, {255, 0, 0, 255}); // Création de la brique rouge
            bricks.push_back(brick);
        }
    }

    return bricks;
}


HelloWorld::HelloWorld() {
    OpenHelloWorld();
}

void HelloWorld::OpenHelloWorld()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_X, WINDOW_Y, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    Paddle paddle(renderer, WINDOW_X / 2 - (PAD_W / 2), WINDOW_Y - 40, PAD_W, PAD_H);

    std::vector<Brick> bricks = createBrickList(renderer, WINDOW_X, 60, 20); // Réglage de la largeur et de la hauteur des briques

    // Variables pour le calcul du temps
    Uint32 lastTime = SDL_GetTicks();
    const Uint32 targetFrameTime = 1000 / 60; // Cible de 60 images par seconde

    // Wait for the user to close the window
    bool quit = false;
    while (!quit) {
        // Calcul du temps écoulé depuis la dernière trame
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - lastTime;

        // Si le temps écoulé dépasse le temps cible pour une trame, effectuer une nouvelle trame
        if (elapsedTime >= targetFrameTime) {

            // Mettre à jour le temps de la dernière trame
            lastTime = currentTime;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            paddle.moveLeft(PAD_SPEED , WINDOW_X);
                            break;
                        case SDLK_RIGHT:
                            paddle.moveRight(PAD_SPEED , WINDOW_X);
                            break;
                        default:
                            break;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            paddle.draw();
            for (const auto& brick : bricks) {
                brick.draw();
            }

            SDL_RenderPresent(renderer);
        }
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}