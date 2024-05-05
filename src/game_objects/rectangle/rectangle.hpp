#pragma once
#include "../general_game_object/general_game_object.hpp"
#include "../../global/global.hpp"

class Rectangle : public GeneralGameObject
{
public:
    Rectangle(Vector2 position, SDL_Colour colour, int width, int height);
    void update(double deltaTime);
    void draw(void);
    GETTER_AND_SETTER_HPP(SDL_Colour, colour, Colour)
    GETTER_HPP(SDL_Rect, rectangle, Rectangle)
};