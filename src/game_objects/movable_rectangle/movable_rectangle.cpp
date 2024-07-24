#include "./movable_rectangle.hpp"

MovableRectangle::MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height) : Rectangle(position, colour, width, height) {}
void MovableRectangle::update(double deltaTime)
{
    position += velocity * deltaTime + (Vector2){0, gravity} / 2 * deltaTime * deltaTime;
    velocity += (Vector2){0, gravity} * deltaTime;
    TilesAroundPosition tiles = tileMap.getTilesAroundPosition(position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2});
    if (tiles.topLeft != NULL && *tiles.topLeft == TILE_PLATFORM)
    {
        puts("Top Left");
    }
    if (tiles.top != NULL && *tiles.top == TILE_PLATFORM)
    {
        puts("Top");
    }
    if (tiles.topRight != NULL && *tiles.topRight == TILE_PLATFORM)
    {
        puts("Top Right");
    }
    if (tiles.bottomLeft != NULL && *tiles.bottomLeft == TILE_PLATFORM)
    {
        puts("Bottom Left");
    }
    if (tiles.bottom != NULL && *tiles.bottom == TILE_PLATFORM)
    {
        puts("Bottom");
    }
    if (tiles.bottomRight != NULL && *tiles.bottomRight == TILE_PLATFORM)
    {
        puts("Bottom Right");
    }
    if (tiles.left != NULL && *tiles.left == TILE_PLATFORM)
    {
        puts("Left");
    }
    if (tiles.centre != NULL && *tiles.centre == TILE_PLATFORM)
    {
        puts("Centre");
    }
    if (tiles.right != NULL && *tiles.right == TILE_PLATFORM)
    {
        puts("Right");
    }
    Rectangle::update(deltaTime);
}
GETTER_AND_SETTER_CPP(Vector2, MovableRectangle, velocity, Velocity)