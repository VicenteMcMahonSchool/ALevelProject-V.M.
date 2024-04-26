#include "./rectangle.hpp"

GETTER_AND_SETTER_CPP(Vector2, Rectangle, position, Position)
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)
Rectangle::Rectangle(Vector2 position, SDL_Colour colour) : position(position), colour(colour) {}
void Rectangle::draw(void)
{
    SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    SDL_RenderFillRect(renderer, &this->rectangle);                                                    // Fill rectangle.
}