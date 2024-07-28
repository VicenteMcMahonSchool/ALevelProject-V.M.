#pragma once
#include "../rectangle/rectangle.hpp"

class Button : public Rectangle
{
public:
    Button(Vector2 position, SDL_Colour colour, int width, int height, const char *text, void (*callBack)(void));
    void onClick(void);
    void draw(void);

private:
    const char *text;
    void (*callBack)(void);
    void drawText(const char *text);
};