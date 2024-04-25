#pragma once
#include <SDL2/SDL.h>
#include <stdexcept>
#include "../global/global.hpp"

// This is a header file for application, only needed because of '#include' directives.
struct Application
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Application(unsigned int windowWidth, unsigned int windowHeight);
    ~Application();
    void run(void);
};