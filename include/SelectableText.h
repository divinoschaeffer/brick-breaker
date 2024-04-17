//
// Created by Bryan on 17/04/2024.
//

#ifndef SELECTABLETEXT_H
#define SELECTABLETEXT_H
#include <Text.h>
#include <SDL_image.h>

class SelectableText : public Text {
private:
    SDL_Color selectedColor;
    SDL_Color defaultColor;
    TTF_Font* defaultFont;
    TTF_Font* selectedFont;
public:
    SelectableText(SDL_Renderer* renderer, SDL_Color color, SDL_Color selectedColor, const std::string& text, TTF_Font* defaultFont, TTF_Font* selectedFont)
        : Text(renderer, color, text, defaultFont), defaultColor(color), selectedColor(selectedColor), defaultFont(defaultFont), selectedFont(selectedFont) {
    }

    void render(SDL_Renderer* renderer, const int posX, const int posY, const bool isSelected);
};



#endif //SELECTABLETEXT_H
