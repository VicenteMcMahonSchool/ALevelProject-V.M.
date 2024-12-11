#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define DELAY 8

class Application {
  public:
    Application(void);
    ~Application();
    void run(void);

  private:
    void winScreen(void);
    void loseScreen(void);
    void gameScreen(void);
    void menuScreen(void);
    void editScreen(void);
};