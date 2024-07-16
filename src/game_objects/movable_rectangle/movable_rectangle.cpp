#include "./movable_rectangle.hpp"

MovableRectangle::MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height) : Rectangle(position, colour, width, height) {}
void MovableRectangle::update(double deltaTime)
{
    position += velocity * deltaTime + (Vector2){0, gravity} / 2 * deltaTime * deltaTime;
    velocity += (Vector2){0, gravity} * deltaTime;
    Rectangle::update(deltaTime);
}
GETTER_AND_SETTER_CPP(Vector2, MovableRectangle, velocity, Velocity)