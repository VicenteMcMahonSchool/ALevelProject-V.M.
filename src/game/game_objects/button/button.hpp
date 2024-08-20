#pragma once
#include "../rectangle/rectangle.hpp"

#define BUTTON_CONSTRUCTOR_ARGUMENTS Vector2 position, SDL_Colour colour, int width, int height, const char *text, void (*callBack)(void)
#define BUTTON_CONSTRUCTOR_ARGUMENTS_NAMES position, colour, width, height, text, callBack

class Button : public Rectangle
{
public:
    Button(BUTTON_CONSTRUCTOR_ARGUMENTS);
    void onAction(bool checkMousePosition);
    void draw(void);

private:
    const char *text;
    void (*callBack)(void);
};