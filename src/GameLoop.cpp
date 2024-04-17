//
// Created by Bryan on 13/04/2024.
//

#include "GameLoop.h"

#include "SelectableText.h"
#include "Text.h"
#define HEIGHT 800
#define WIDTH 640

int menuSelection = 0;

GameLoop::GameLoop() {
    window = nullptr;
    renderer = nullptr;
    defaultFont = nullptr;
    selectedFont = nullptr;
    defaultColor = {255, 255, 255, 255};  // Blanc
    selectedColor = {255, 0, 0, 255};  // Rouge
    WindowInit();
}

GameLoop::~GameLoop() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (defaultFont != nullptr) {
        TTF_CloseFont(defaultFont);
    }
    if (selectedFont != nullptr) {
        TTF_CloseFont(selectedFont);
    }
    SDL_Quit();
}



/*
 *  On initialise la fenêtre du jeu, le début de la partie, donc on init la balle, la raquette et les briques
 */
void GameLoop::WindowInit()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a window
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    // Initialize the fonts
    defaultFont = TTF_OpenFont("fonts/minecraft_font.ttf", 32);
    if (defaultFont == nullptr) {
        std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    selectedFont = TTF_OpenFont("fonts/minecraft_font.ttf", 36);
    if (defaultFont == nullptr) {
        std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void GameLoop::FirstPageLoop() {
    Text title(renderer, defaultColor, "Brick Breaker", defaultFont);
    SelectableText playTxt(renderer, defaultColor, selectedColor, "Play", defaultFont, selectedFont);
    SelectableText quitTxt(renderer, defaultColor, selectedColor, "Quit", defaultFont, selectedFont);
    // Rafraichissement de la page
    bool running = true;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        std::cout << "Flèche gauche pressée" << std::endl;
                    break;
                    case SDLK_RIGHT:
                        std::cout << "Flèche droite pressée" << std::endl;
                    break;
                    case SDLK_UP:
                        std::cout << "Flèche haut pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                        SDL_RenderPresent(renderer);
                    break;
                    case SDLK_DOWN:
                        std::cout << "Flèche bas pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                        SDL_RenderPresent(renderer);
                    break;
                    case SDLK_ESCAPE:
                        std::cout << "Sortie du jeu." << std::endl;
                        running = false;
                    break;
                    case SDLK_RETURN:
                        std::cout << "Selection du menu" << std::endl;
                        if (menuSelection == 0) {
                            Loop();
                        } else {
                            running = false;
                        }
                    default:
                        break;
                }
            }
        }
        // Rafraichissement de la page
        SDL_RenderClear(renderer);
        title.render(renderer, WIDTH / 2, 50);
        playTxt.render(renderer, WIDTH / 2,  HEIGHT / 7, menuSelection == 0);
        quitTxt.render(renderer, WIDTH / 2, 2 * HEIGHT / 7, menuSelection == 1);
        SDL_RenderPresent(renderer);
    }
}

void GameLoop::Loop() {
    bool running = true;
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        std::cout << "Flèche gauche pressée" << std::endl;
                    break;
                    case SDLK_RIGHT:
                        std::cout << "Flèche droite pressée" << std::endl;
                        break;
                    case SDLK_UP:
                        std::cout << "Flèche haut pressée" << std::endl;
                        menuSelection = (menuSelection + 1) % 2;
                    break;
                    case SDLK_DOWN:
                        std::cout << "Flèche bas pressée" << std::endl;
                        menuSelection = (menuSelection - 1) % 2;
                    break;
                    case SDLK_ESCAPE:
                        std::cout << "Sortie du jeu." << std::endl;
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}