#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height) : width(width), height(height),
    window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer),
    defaultFont(nullptr, TTF_CloseFont), selectedFont(nullptr, TTF_CloseFont) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        return;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (!renderer) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    defaultFont = std::shared_ptr<TTF_Font>(TTF_OpenFont("fonts/minecraft_font.ttf", 32), TTF_CloseFont);
    if (!defaultFont) {
        std::cerr << "Police par défaut non chargée! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return;
    }

    selectedFont = std::shared_ptr<TTF_Font>(TTF_OpenFont("fonts/minecraft_font.ttf", 36), TTF_CloseFont);
    if (!selectedFont) {
        std::cerr << "Police sélectionnée non chargée! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return;
    }
}

Window::~Window() {
    SDL_Quit();
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());
}

void Window::present() {
    SDL_RenderPresent(renderer.get());
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

std::shared_ptr<SDL_Renderer> Window::getRenderer(){
    return renderer;
}

std::shared_ptr<SDL_Window> Window::getWindow(){
    return window;
}

std::shared_ptr<TTF_Font> Window::getDefaultFont(){
    return defaultFont;
}

std::shared_ptr<TTF_Font> Window::getSelectedFont(){
    return selectedFont;
}
