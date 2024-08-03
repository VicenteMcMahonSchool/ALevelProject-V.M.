#pragma once
#include "../rectangle/rectangle.hpp"
#include "../tile_map/tile_map.hpp"

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
    void (*onCollision)(const TILE_TYPE *tile, MovableRectangle *movableRectangle) = NULL;

public:
    MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height);
    void update(double deltaTime);
    GETTER_AND_SETTER_HPP(Vector2, velocity, Velocity)
};