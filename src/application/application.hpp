#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "../game_objects/game_object/game_object.hpp"
#include "../game_objects_class/game_objects_class.hpp"

#define DELAY 8

class Application
{
public:
    Application(void);
    ~Application();
    void run(void);

private:
    void gameScreen(void);
    void menuScreen(void);
    void editScreen(void);
};