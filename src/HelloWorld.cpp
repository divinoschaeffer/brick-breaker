//
// Created by Bryan on 13/04/2024.
//

#include "HelloWorld.h"

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
    SDL_Window* window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Create a font
    TTF_Font* font = TTF_OpenFont("fonts/minecraft_font.ttf", 32);
    if (font == nullptr) {
        std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a surface from the font
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Brick Breaker", textColor);
    if (textSurface == nullptr) {
        std::cerr << "Text surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Text texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Get the dimensions of the texture
    const int textWidth = textSurface->w;
    const int textHeight = textSurface->h;

    // Set the position of the text
    SDL_Rect textRect;
    textRect.x = (640 - textWidth) / 2;
    textRect.y = (480 - textHeight) / 2;
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Créer une surface à partir de l'image
    SDL_Surface* imageSurface = IMG_Load("sprites/mbappe.jpeg");
    if (imageSurface == nullptr) {
        std::cerr << "Image surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Créer une texture à partir de la surface de l'image
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == nullptr) {
        std::cerr << "Image texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Obtenir les dimensions de la texture
    int imageWidth = imageSurface->w;
    int imageHeight = imageSurface->h;

    // Définir la position de l'image (sous le texte)
    SDL_Rect imageRect;
    imageRect.x = (640 - imageWidth) / 2;
    imageRect.y = (480 - textHeight) / 2 + textHeight + 10; // 10 pixels de marge
    imageRect.w = imageWidth;
    imageRect.h = imageHeight;

    // Rendre la texture d'image
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
    // Render the text
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);


    SDL_RenderPresent(renderer);

    // Wait for the user to close the window
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Clean up resources
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}