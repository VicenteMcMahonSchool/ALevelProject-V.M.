#include "button.hpp"

Button::Button(BUTTON_CONSTRUCTOR_ARGUMENTS) : Rectangle(position, colour, width, height), text(text), callBack(callBack) {}

void Button::draw(void)
{
    Rectangle::draw();
    drawText(text, &rectangle);
}

void Button::onAction(bool checkMousePosition)
{
    if (checkMousePosition)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > rectangle.x && x < rectangle.x + rectangle.w && y > rectangle.y && y < rectangle.y + rectangle.h)
            callBack();
    }
    else
        callBack();
}