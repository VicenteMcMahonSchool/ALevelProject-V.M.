#pragma once
#include "../rectangle/rectangle.hpp"

#define MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS Vector2 position, SDL_Colour colour, int width, int height
#define MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS_NAMES position, colour, width, height

struct TileCentres;
// typedef char TILE_TYPE;

class MovableRectangle : public Rectangle
{
private:
    void handleCollisionTop(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionBottom(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionLeft(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionRight(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);

protected:
    double gravity = 0;
    bool isOnGround = false;
    void (*onCollision)(const /* TILE_TYPE */ unsigned char *tile, MovableRectangle *movableRectangle) = NULL;

public:
    MovableRectangle(MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
    GETTER_AND_SETTER_HPP(Vector2, velocity, Velocity)
};