#include "./rectangle.hpp"

Rectangle::Rectangle(Vector2 position, SDL_Colour colour, int width, int height) : GeneralGameObject(position), colour(colour), rectangle{(int)position.x, (int)position.y, width, height} {}
void Rectangle::update(double deltaTime)
{
    rectangle.x = position.x;
    rectangle.y = position.y;
    GeneralGameObject::update(deltaTime);
}
void Rectangle::draw(void)
{
    rectangle.x = position.x - (cameraPosition.x - windowWidth / 2);
    rectangle.y = position.y - (cameraPosition.y - windowHeight / 2);
    SDL_SetRenderDrawColour(renderer, 0X11, 0X11, 0X11, 0XFF);
    SDL_Rect shadowRectangle{rectangle.x + SHADOW_DISTANCE_X, rectangle.y + SHADOW_DISTANCE_Y, rectangle.w, rectangle.h};
    SDL_RenderFillRect(renderer, &shadowRectangle);                            // Fills the rectangle.
    SDL_SetRenderDrawColour(renderer, colour.r, colour.g, colour.b, colour.a); // Sets draw colour.
    SDL_RenderFillRect(renderer, &rectangle);                                  // Fills the rectangle.
    GeneralGameObject::draw();
}
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)