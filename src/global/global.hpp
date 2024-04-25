#pragma once
#include <SDL2/SDL.h>

struct Application;
// Extern allows other files to know about global variables stored else where.
extern Application application;
extern SDL_Rect testRectangle;
extern SDL_DisplayMode displayMode;