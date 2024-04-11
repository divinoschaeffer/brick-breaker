#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[]) {
    
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Impossible d'initialiser SDL : %s", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Impossible d'initialiser SDL_ttf : " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Création d'une fenêtre
    SDL_Window* window = SDL_CreateWindow("Brick Breaker",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          600, 800,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Impossible de créer la fenêtre : %s", SDL_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("font/Roboto-Regular.ttf", 22);
    if (font == nullptr) {
        std::cerr << "Impossible de charger la police : " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = {255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor);
    if (textSurface == nullptr) {
        std::cerr << "Impossible de créer la surface de texte : " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Impossible de créer le renderer : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Impossible de créer la texture de texte : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Libération de la surface de texte, maintenant que la texture est créée
    SDL_FreeSurface(textSurface);

    // Effacement de l'écran
    SDL_RenderClear(renderer);

    // Affichage de la texture de texte
    SDL_Rect textRect = {100, 100, 0, 0}; // Position du texte à l'écran
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Mise à jour de l'affichage
    SDL_RenderPresent(renderer);
    
    // Boucle de jeu
    bool running = true;
    SDL_Event event;
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        std::cout << "Flèche gauche pressée" << std::endl;
                        break;
                    case SDLK_RIGHT:
                        std::cout << "Flèche droite pressée" << std::endl;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Nettoyage et fermeture de SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
