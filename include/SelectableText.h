#ifndef SELECTABLETEXT_H
#define SELECTABLETEXT_H

#include <Text.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

class SelectableText : public Text {
private:
    SDL_Color selectedColor;
    SDL_Color defaultColor;
    std::shared_ptr<TTF_Font> defaultFont;
    std::shared_ptr<TTF_Font> selectedFont;
public:
    SelectableText(std::shared_ptr<SDL_Renderer> renderer, const SDL_Color& color, const SDL_Color& selectedColor, const std::string& text, std::shared_ptr<TTF_Font> defaultFont, std::shared_ptr<TTF_Font> selectedFont)
        : Text(renderer, color, text, defaultFont), defaultColor(color), selectedColor(selectedColor), defaultFont(defaultFont), selectedFont(selectedFont) {
    }

    void render(const int& posX, const int& posY, const bool& isSelected);
};

#endif //SELECTABLETEXT_H
