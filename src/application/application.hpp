#pragma once
#include <SDL2/SDL.h>
#include <stdexcept>
#include "../global/global.hpp"

// This is a header file for application, only needed because of '#include' directives.
struct Application
{
    Application();
    ~Application();
    void run(void);
};