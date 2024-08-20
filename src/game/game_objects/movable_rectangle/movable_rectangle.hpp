#pragma once
#include "../rectangle/rectangle.hpp"

#define MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS Vector2 position, SDL_Colour colour, int width, int height
#define MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS_NAMES position, colour, width, height
#define MOVABLE_RECTANGLE_DAMPENING_EVERY_1000TH_OF_SECOND .9995

struct TileCentres;

class MovableRectangle : public Rectangle
{
private:
    void handleCollisionTop(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionBottom(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionLeft(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);
    void handleCollisionRight(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight);

protected:
    double gravity = 0.002;
    bool isOnGround = false;
    void (*onCollision)(const unsigned char *tile, void *data) = NULL;
    void *onCollisionData = NULL;

public:
    MovableRectangle(MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
    GETTER_AND_SETTER_HPP(Vector2, velocity, Velocity)
};