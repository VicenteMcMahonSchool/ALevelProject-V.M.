#pragma once
#include "../rectangle/rectangle.hpp"

class MovableRectangle : public Rectangle
{
    MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height);
    GETTER_AND_SETTER_HPP(Vector2, velocity, Velocity)
};