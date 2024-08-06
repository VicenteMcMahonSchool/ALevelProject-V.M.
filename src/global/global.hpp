#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../macros/macros.hpp"
// #include "../game_objects_class/game_objects_class.hpp"

enum __attribute__((__packed__)) SCREEN
{
    SCREEN_EXIT,
    SCREEN_GAME,
    SCREEN_MENU,
    SCREEN_EDIT,
    SCREEN_WIN,
    SCREEN_LOSE
};

#define SHADOW_DISTANCE_X 6
#define SHADOW_DISTANCE_Y 6

// Application Type is defined here because of circular dependencies issues. This occurs because 'global.hpp' requires 'application' of type 'Application', whilst 'application' needs access to the global variables.
struct Application;
struct GameObject;
struct GameObjects;
struct TileMap;
struct Vector2;

// Extern allows other files to know about global variables stored else where.
extern Application application; // In 'main.cpp'.
// These are stored in 'application.cpp'.
// extern SDL_DisplayMode displayMode;
extern int windowWidth, windowHeight;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern GameObjects gameObjects;
extern TileMap tileMap;
extern Vector2 cameraPosition;
extern TTF_Font *font;
extern SCREEN screen;
extern SDL_GameController *controller;

enum __attribute__((__packed__)) GAME_OBJECT_TYPE
{
    GENERAL_GAME_OBJECT,
    RECTANGLE,
    MOVABLE_RECTANGLE,
    BUTTON,
    TILE_MAP,
    PLAYER,
    ENEMY
};