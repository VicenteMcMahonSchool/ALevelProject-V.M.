#include <SDL2/SDL.h>
#pragma once

// This is a header file for application, only needed because of '#include' directives.
struct Application
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Application(unsigned int windowWidth, unsigned int windowHeight);
    ~Application();
    void run(void);
};