//
// Created by Bryan on 17/04/2024.
//

#include "SelectableText.h"
#include <iostream>

void SelectableText::render(SDL_Renderer* renderer, const int posX, const int posY, const bool isSelected) {
    color = isSelected ? selectedColor : defaultColor;
    font = isSelected ? selectedFont : defaultFont;
    surface = TTF_RenderText_Blended(font, Text::text.c_str(), color);
    if (surface == nullptr) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    Text::render(renderer, posX, posY);
}
