#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>

class Window {
private:
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<TTF_Font> defaultFont;
    std::shared_ptr<TTF_Font> selectedFont;
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
