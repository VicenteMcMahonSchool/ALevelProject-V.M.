#pragma once
#include <SDL2/SDL.h>
#include "../macros/macros.hpp"

// Application Type is defined here because of circular dependencies issues. This occurs because 'global.hpp' requires 'application' of type 'Application', whilst 'application' needs access to the global variables.
struct Application;
struct GameObject;
template <typename>
struct LinkedList;
// Extern allows other files to know about global variables stored else where.
extern Application application; // In 'main.cpp'.
// These are stored in 'application.cpp'.
// extern SDL_DisplayMode displayMode;
extern unsigned int windowWidth, windowHeight;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern LinkedList<GameObject> gameObjects;