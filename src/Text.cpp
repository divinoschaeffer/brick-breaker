#include "Text.h"
#include <iostream>

Text::Text(const std::shared_ptr<SDL_Renderer>& renderer, const SDL_Color &color, const std::string& text, const std::shared_ptr<TTF_Font>& font)
    : renderer(renderer), color(color), text(text), font(font) {
    surface.reset(TTF_RenderText_Solid(font.get(), text.c_str(), color), SDL_FreeSurface);
    if (surface == nullptr) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    texture.reset(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Text::render(const int posX, const int posY) {
    const int titleWidth = surface->w;
    const int titleHeight = surface->h;
    rect.x = posX - (titleWidth / 2);
    rect.y = posY;
    rect.w = titleWidth;
    rect.h = titleHeight;

    SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &rect);
}
