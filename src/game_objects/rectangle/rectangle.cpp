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
    SDL_SetRenderDrawColour(renderer, colour.r, colour.g, colour.b, colour.a); // Sets draw colour.
    rectangle.x -= cameraPosition.x - windowWidth / 2;
    rectangle.y -= cameraPosition.y - windowHeight / 2;
    SDL_RenderFillRect(renderer, &rectangle); // Fill rectangle.
    GeneralGameObject::draw();
    rectangle.x += cameraPosition.x - windowWidth / 2;
    rectangle.y += cameraPosition.y - windowHeight / 2;
}
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)