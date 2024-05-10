#ifndef TEXT_H
#define TEXT_H

#include <memory>
#include <SDL_ttf.h>
#include <string>

class Text {
protected:
    std::shared_ptr<SDL_Renderer> renderer;
    SDL_Color color;
    std::string text;
    std::shared_ptr<TTF_Font> font;
    std::shared_ptr<SDL_Surface> surface;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect rect;

public:
    Text(const std::shared_ptr<SDL_Renderer>& renderer, const SDL_Color &color, const std::string& text, const std::shared_ptr<TTF_Font>& font);

    void render(const int posX, const int posY);
};

#endif //TEXT_H
