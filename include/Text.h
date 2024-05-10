#ifndef TEXT_H
#define TEXT_H
#include <SDL_ttf.h>
#include <string>

class Text {
protected:
    SDL_Renderer* renderer;
    SDL_Color color;
    std::string text;
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;

public:
    Text(SDL_Renderer* renderer, const SDL_Color &color, const std::string& text, TTF_Font* font);
    virtual void render(SDL_Renderer* renderer, const int posX, const int posY);
};

#endif //TEXT_H