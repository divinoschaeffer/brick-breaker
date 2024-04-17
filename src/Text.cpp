#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer* renderer, SDL_Color color, const std::string& text, TTF_Font* font)
    : renderer(renderer), color(color), text(text), font(font) {
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Text::render(SDL_Renderer* renderer, const int posX, const int posY) {
    const int titleWidth = surface->w;
    const int titleHeight = surface->h;
    rect.x = posX - (titleWidth / 2);
    rect.y = posY;
    rect.w = titleWidth;
    rect.h = titleHeight;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}