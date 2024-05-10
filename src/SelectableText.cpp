//
// Created by Bryan on 17/04/2024.
//

#include "SelectableText.h"
#include <iostream>

void SelectableText::render(const int& posX, const int& posY, const bool &isSelected) {
    // Utiliser les membres de la classe mère Text
    Text::color = isSelected ? selectedColor : defaultColor;
    Text::font = isSelected ? selectedFont : defaultFont;
    
    // Vérifier si font et renderer sont valides
    if (!Text::font || !Text::renderer) {
        std::cerr << "Renderer or font is null!" << std::endl;
        exit(1);
    }

    // Créer une nouvelle surface et une nouvelle texture
    surface.reset(TTF_RenderText_Blended(Text::font.get(), Text::text.c_str(), Text::color), SDL_FreeSurface);
    if (!surface) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    
    texture.reset(SDL_CreateTextureFromSurface(Text::renderer.get(), surface.get()), SDL_DestroyTexture);
    if (!texture) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    // Appeler la fonction render de la classe mère Text
    Text::render(posX, posY);
}

