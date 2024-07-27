#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../macros/macros.hpp"

enum __attribute__((__packed__)) SCREEN
{
    SCREEN_EXIT,
    SCREEN_GAME,
    SCREEN_MENU
};

// Application Type is defined here because of circular dependencies issues. This occurs because 'global.hpp' requires 'application' of type 'Application', whilst 'application' needs access to the global variables.
struct Application;
struct GameObject;
struct TileMap;
struct Vector2;
// template <typename>
// struct LinkedList;
struct LinkedList;
// Extern allows other files to know about global variables stored else where.
extern Application application; // In 'main.cpp'.
// These are stored in 'application.cpp'.
// extern SDL_DisplayMode displayMode;
extern int windowWidth, windowHeight;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern LinkedList /* <GameObject> */ gameObjects;
extern TileMap tileMap;
extern Vector2 cameraPosition;
extern TTF_Font *font;
extern SCREEN screen;