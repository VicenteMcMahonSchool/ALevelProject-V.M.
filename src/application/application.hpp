#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "../global/global.hpp"
#include "../game_objects/rectangle/rectangle.hpp"
#include "../game_objects/movable_rectangle/movable_rectangle.hpp"
#include "../linked_list/linked_list.hpp"
#include "../keys_down/keys_down.hpp"
#include "../game_objects/player/player.hpp"
// This is a header file for application, only needed because of '#include' directives.

class Application
{
public:
    Application(void);
    ~Application();
    void run(void);

private:
    void drawText(const char *text, SDL_Rect *rectangle);
    void drawText(const char *text, SDL_Rect rectangle);
    void gameScreen(void);
    void menuScreen(void);
};