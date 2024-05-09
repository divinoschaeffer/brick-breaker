#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height) : width(width), height(height),
    window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer),
    defaultFont(nullptr, &TTF_CloseFont), selectedFont(nullptr, &TTF_CloseFont) {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        return;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Création de la fenêtre
    window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Création du renderer
    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!renderer) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Chargement des polices
    defaultFont.reset(TTF_OpenFont("fonts/minecraft_font.ttf", 32));
    if (!defaultFont) {
        std::cerr << "Police par défaut non chargée! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit(); // Libérer les ressources de SDL_ttf
        SDL_Quit();
        return;
    }

    selectedFont.reset(TTF_OpenFont("fonts/minecraft_font.ttf", 36));
    if (!selectedFont) {
        std::cerr << "Police sélectionnée non chargée! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit(); // Libérer les ressources de SDL_ttf
        SDL_Quit();
        return;
    }

}

Window::~Window() {
    // Fermeture de la SDL
    SDL_Quit();
}

void Window::clear() {
    // Effacer l'écran avec une couleur spécifique (ici blanc)
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());
}

void Window::present() {
    // Mettre à jour l'écran
    SDL_RenderPresent(renderer.get());
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

SDL_Renderer* Window::getRenderer(){
    return renderer.get();
}

SDL_Window* Window::getWindow(){
    return window.get();
}

TTF_Font* Window::getDefaultFont(){
    return defaultFont.get();
}

TTF_Font* Window::getSelectedFont(){
    return selectedFont.get();
}