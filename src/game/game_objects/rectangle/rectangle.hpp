#pragma once
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"

#define RECTANGLE_CONSTRUCTOR_ARGUMENTS                                        \
    Vector2 position, SDL_Colour colour, int width, int height
#define RECTANGLE_CONSTRUCTOR_ARGUMENTS_NAMES position, colour, width, height

class Rectangle : public GeneralGameObject {
  private:
    SDL_Rect shadowRectangle;

  public:
    Rectangle(RECTANGLE_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime) override;
    void draw(void) override;
    void drawShadows(void) override;
    GETTER_AND_SETTER_HPP(SDL_Colour, colour, Colour)
    GETTER_HPP(SDL_Rect, rectangle, Rectangle)
};