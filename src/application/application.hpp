#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "../global/global.hpp"
#include "../game_objects/rectangle/rectangle.hpp"
#include "../game_objects/movable_rectangle/movable_rectangle.hpp"
#include "../linked_list/linked_list.hpp"
#include "../input/input.hpp"
#include "../game_objects/player/player.hpp"
#include "../game_objects/button/button.hpp"
#include "../game_objects/tile_map/tile_map.hpp"

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