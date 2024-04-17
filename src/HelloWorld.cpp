//
// Created by Bryan on 13/04/2024.
//

#include <filesystem> // Pour accéder aux fonctionnalités de système de fichiers
#include <fstream>
#include <vector>
#include "HelloWorld.h"
#include "Paddle.h"
#include "Brick.h"

#define WINDOW_X 640
#define WINDOW_Y 480
#define PAD_W 100
#define PAD_H 10
#define PAD_SPEED 60

// Fonction pour créer des briques à partir d'un fichier ASCII
std::vector<Brick> createBricksFromFile(SDL_Renderer* renderer, const std::string& filename, int brickWidth, int brickHeight, int windowWidth, int windowHeight) {
    std::vector<Brick> bricks;

    // Construire le chemin complet du fichier en utilisant le dossier "grilles"
    std::string filepath = "grilles/" + filename;

    // Vérifier si le fichier existe
    if (!std::__fs::filesystem::exists(filepath)) {
        std::cerr << "File does not exist: " << filepath << std::endl;
        return bricks;
    }

    // Ouvrir le fichier
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filepath << std::endl;
        return bricks;
    }

    // Calculer la position y de la première ligne de briques
    int startY = 10;

    // Lire le fichier ligne par ligne
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        // Calculer la position y de la ligne pour la centrer verticalement dans la fenêtre
        int lineY = startY + y * (brickHeight + 10);

        // Calculer l'espacement horizontal entre les briques
        int horizontalSpace = (windowWidth - line.size() * brickWidth) / (line.size() + 1);

        int x = 0;
        for (char c : line) {
            // Calculer la position x de la brique
            int brickX = horizontalSpace + x * (brickWidth + horizontalSpace);

            int brickY = lineY; // Position y de la brique
            switch (c) {
                case '0':
                    // Brique indestructible
                    bricks.emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, SDL_Color{255, 255, 255, 255}, -1);
                    break;
                case '1':
                    // Brique normale avec 1 point de vie
                    bricks.emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, SDL_Color{255, 0, 0, 255}, 1);
                    break;
                case '2':
                    // Brique normale avec 2 points de vie
                    bricks.emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, SDL_Color{0, 255, 0, 255}, 2);
                    break;
                case '3':
                    // Brique normale avec 3 points de vie
                    bricks.emplace_back(renderer, brickX, brickY, brickWidth, brickHeight, SDL_Color{0, 255, 255, 255}, 3);
                    break;
            }
            x++;
        }
        y++;
    }

    // Fermer le fichier
    file.close();

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

    std::vector<Brick> bricks = createBricksFromFile(renderer, "grille1.txt", 60, 20, WINDOW_X, WINDOW_Y); // Réglage de la largeur et de la hauteur des briques

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
                switch (event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
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
                        break;
                    case SDL_MOUSEMOTION:
                        // Déplacer la raquette en fonction de la position de la souris
                        paddle.setPosition(event.motion.x - PAD_W / 2, WINDOW_Y - 40);
                        break;
                    default:
                        break;
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