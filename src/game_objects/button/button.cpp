#include "button.hpp"

Button::Button(Vector2 position, SDL_Colour colour, int width, int height, const char *text, void (*callBack)(void)) : Rectangle(position, colour, width, height), text(text), callBack(callBack) {}

void Button::drawText(const char *text)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, {0X00, 0X00, 0X00});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &rectangle);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Button::draw(void)
{
    Rectangle::draw();
    drawText(text);
}

void Button::onClick(void)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > rectangle.x && x < rectangle.x + rectangle.w && y > rectangle.y && y < rectangle.y + rectangle.h)
        callBack();
}