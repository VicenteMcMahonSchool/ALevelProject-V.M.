#pragma once
#include <SDL2/SDL.h>
#include <stdexcept>
#include "../global/global.hpp"
#include "../game_objects/rectangle/rectangle.hpp"
#include "../game_objects/movable_rectangle/movable_rectangle.hpp"

// This is a header file for application, only needed because of '#include' directives.
struct Application
{
    Application();
    ~Application();
    void updateGameObject(GameObject *gameObject, double deltaTime);
    void drawGameObject(GameObject *gameObject);
    void run(void);
};