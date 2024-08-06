#include "./rectangle.hpp"

Rectangle::Rectangle(RECTANGLE_CONSTRUCTOR_ARGUMENTS) : GeneralGameObject(position), colour(colour), rectangle{(int)round(position.x), (int)round(position.y), width, height} {}
void Rectangle::update(double deltaTime)
{
    rectangle.x = (int)round(position.x);
    rectangle.y = (int)round(position.y);
    GeneralGameObject::update(deltaTime);
}
void Rectangle::draw(void)
{
    rectangle.x = round(position.x - (cameraPosition.x - windowWidth / 2));
    rectangle.y = round(position.y - (cameraPosition.y - windowHeight / 2));
    // Fills the rectangle.
    SDL_SetRenderDrawColour(renderer, colour.r, colour.g, colour.b, colour.a); // Sets draw colour.
    SDL_RenderFillRect(renderer, &rectangle);                                  // Fills the rectangle.
    GeneralGameObject::draw();
}
void Rectangle::drawShadows(void)
{
    shadowRectangle.x = round(position.x - (cameraPosition.x - windowWidth / 2)) + SHADOW_DISTANCE_X;
    shadowRectangle.y = round(position.y - (cameraPosition.y - windowHeight / 2)) + SHADOW_DISTANCE_Y;
    SDL_SetRenderDrawColour(renderer, 0X11, 0X11, 0X11, 0XFF);
    SDL_RenderFillRect(renderer, &shadowRectangle);
}
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)