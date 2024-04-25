#include "./rectangle.hpp"

GETTER_AND_SETTER_CPP(Vector2, Rectangle, position, Position)
GETTER_AND_SETTER_CPP(SDL_Color, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)
Rectangle::Rectangle(Vector2 position, SDL_Color colour) : position(position), colour(colour) {}
void Rectangle::draw(void)
{
    SDL_SetRenderDrawColor(renderer, 0XFF, 0XFF, 0XFF, 0XFF); // Sets draw colour.
    SDL_RenderFillRect(renderer, &this->rectangle);           // Fill rectangle.
}