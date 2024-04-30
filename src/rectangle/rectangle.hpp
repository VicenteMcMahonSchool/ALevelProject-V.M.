#pragma once
#include "../vector2/vector2.hpp"
#include "../global/global.hpp"

#define TESTING(value) value

class Rectangle
{
public:
    Rectangle(Vector2 position, SDL_Colour colour, int width, int height);
    void draw(void);
    GETTER_AND_SETTER_HPP(Vector2, position, Position)
    GETTER_AND_SETTER_HPP(SDL_Colour, colour, Colour)
    GETTER_HPP(SDL_Rect, rectangle, Rectangle)
};