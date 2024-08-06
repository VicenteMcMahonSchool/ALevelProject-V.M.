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
    SDL_SetRenderDrawColour(renderer, 0X11, 0X11, 0X11, 0XFF);
    SDL_Rect shadowRectangle{(int)round(rectangle.x + SHADOW_DISTANCE_X), (int)round(rectangle.y + SHADOW_DISTANCE_Y), rectangle.w, rectangle.h};
    SDL_RenderFillRect(renderer, &shadowRectangle);                            // Fills the rectangle.
    SDL_SetRenderDrawColour(renderer, colour.r, colour.g, colour.b, colour.a); // Sets draw colour.
    SDL_RenderFillRect(renderer, &rectangle);                                  // Fills the rectangle.
    GeneralGameObject::draw();
}
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)