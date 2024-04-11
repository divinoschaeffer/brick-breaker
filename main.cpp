#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Impossible d'initialiser SDL : %s", SDL_GetError());
        return 1;
    }

    // Création d'une fenêtre
    SDL_Window* window = SDL_CreateWindow("Ma première fenêtre SDL",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Impossible de créer la fenêtre : %s", SDL_GetError());
        return 1;
    }

    // besoin du bloc pour que la fenêtre s'affiche
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    // Nettoyage et fermeture de SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
