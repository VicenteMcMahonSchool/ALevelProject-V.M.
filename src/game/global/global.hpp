#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum __attribute__((__packed__)) SCREEN {
    SCREEN_EXIT,
    SCREEN_GAME_TIME_SCALE,
    SCREEN_GAME_NORMAL,
    SCREEN_MENU,
    SCREEN_EDIT,
    SCREEN_WIN,
    SCREEN_LOSE
};

#define SHADOW_DISTANCE_X 6
#define SHADOW_DISTANCE_Y 6

// Application Type is defined here because of circular dependencies issues.
// This occurs because 'global.hpp' requires 'application' of type
// 'Application', whilst 'application' needs access to the global variables.
struct Application;
struct GameObject;
struct GameObjects;
struct TileMap;
struct Vector2;

// Extern allows other files to know about global variables stored else where.
extern Application application;
// extern SDL_DisplayMode displayMode;
extern int windowWidth, windowHeight;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern GameObjects gameObjects;
extern Vector2 cameraPosition;
extern TTF_Font *font;
extern SCREEN screen;
extern SDL_GameController *controller;
extern unsigned int numberOfTicks;
extern double timePassed;
extern double timeScale;
void drawText(const char *text, const SDL_Rect *rectangle);

enum __attribute__((__packed__)) GAME_OBJECT_TYPE {
    GENERAL_GAME_OBJECT,
    RECTANGLE,
    MOVABLE_RECTANGLE,
    BUTTON,
    TILE_MAP,
    PLAYER,
    ENEMY
};
