#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>

class Window {
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> defaultFont;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> selectedFont;
    int width;
    int height;

public:
    Window(const char* title, int width, int height);
    ~Window();

    void clear();
    void present();
    int getWidth() const;
    int getHeight() const;
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    TTF_Font* getDefaultFont();
    TTF_Font* getSelectedFont();
};

#endif // WINDOW_H
