#include "./rectangle.hpp"

Rectangle::Rectangle(Vector2 position, SDL_Colour colour, int width, int height) : GeneralGameObject(position), colour(colour), rectangle{(int)position.x, (int)position.y, width, height} {}
void Rectangle::update(double deltaTime)
{
    this->rectangle.x = this->position.x;
    this->rectangle.y = this->position.y;
    GeneralGameObject::update(deltaTime);
}
void Rectangle::draw(void)
{
    SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    SDL_RenderFillRect(renderer, &this->rectangle);                                                    // Fill rectangle.
    GeneralGameObject::draw();
}
GETTER_AND_SETTER_CPP(SDL_Colour, Rectangle, colour, Colour)
GETTER_CPP(SDL_Rect, Rectangle, rectangle, Rectangle)