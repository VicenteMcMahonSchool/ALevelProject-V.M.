#include <SDL2/SDL.h>
#include "../application/application.hpp"
#include "global.hpp"
#include "../game_objects_class/game_objects_class.hpp"
#include "../vector2/vector2.hpp"

Application application{};
int windowWidth, windowHeight;
SDL_Window *window;
SDL_Renderer *renderer;
GameObjects gameObjects{};
Vector2 cameraPosition{0, 0};
TTF_Font *font = NULL;
SCREEN screen = SCREEN_MENU;
SDL_GameController *controller = NULL;
unsigned int numberOfTicks = 0;
double timePassed = 0;
double timeScale = 1;

void drawText(const char *text, const SDL_Rect *rectangle)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, {0X00, 0X00, 0X00});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, rectangle);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
