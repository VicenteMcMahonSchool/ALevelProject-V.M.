#include "./movable_rectangle.hpp"
#include "../tile_map/tile_map.hpp"

MovableRectangle::MovableRectangle(MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS) : Rectangle(position, colour, width, height), velocity({0, 0}) {}
void MovableRectangle::update(double deltaTime)
{
    double localGravity = isOnGround ? 0 : gravity;
    position += (velocity * deltaTime + (Vector2){0, localGravity} / 2 * deltaTime * deltaTime) * tileMap.getTileSize() / 120;
    velocity += (Vector2){0, localGravity} * deltaTime;
    isOnGround = false;
    Vector2 centrePosition = position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    unsigned int tileSize = tileMap.getTileSize();
    double averageWidth = (double)(tileSize + rectangle.w) / 2;
    double averageHeight = (double)(tileSize + rectangle.h) / 2;
    TilesAroundTile tiles = tileMap.getTilesAroundPosition(centrePosition);
    TileCentres tileCentres = tileMap.getTileCentresAroundPositionOfTile(tiles.centre);
    if (getTileAttributes(tiles.top).isCollidable && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.top, this);
    }
    else if (getTileAttributes(tiles.topLeft).isCollidable && (centrePosition - tileCentres.topLeft).isYBiggerThanX() && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topLeft, this);
    }
    else if (getTileAttributes(tiles.topRight).isCollidable && (tileCentres.topRight - centrePosition).isNegativeYBiggerThanX() && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topRight, this);
    }

    if (getTileAttributes(tiles.bottom).isCollidable && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottom, this);
    }
    else if (getTileAttributes(tiles.bottomLeft).isCollidable && (centrePosition - tileCentres.bottomLeft).isNegativeYBiggerThanX() && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomLeft, this);
    }
    else if (getTileAttributes(tiles.bottomRight).isCollidable && (tileCentres.bottomRight - centrePosition).isYBiggerThanX() && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomRight, this);
    }

    if (getTileAttributes(tiles.left).isCollidable && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.left, this);
    }
    else if (getTileAttributes(tiles.topLeft).isCollidable && (centrePosition - tileCentres.topLeft).isXBiggerThanY() && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topLeft, this);
    }
    else if (getTileAttributes(tiles.bottomLeft).isCollidable && (centrePosition - tileCentres.bottomLeft).isYBiggerThanNegativeX() && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomLeft, this);
    }

    if (getTileAttributes(tiles.right).isCollidable && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.right, this);
    }
    else if (getTileAttributes(tiles.topRight).isCollidable && (centrePosition - tileCentres.topRight).isNegativeYBiggerThanX() && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topRight, this);
    }
    else if (getTileAttributes(tiles.bottomRight).isCollidable && (centrePosition - tileCentres.bottomRight).isYBiggerThanX() && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomRight, this);
    }
    if (getTileAttributes(tiles.centre).isCollidable)
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.centre, this);
    position = centrePosition - (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    Rectangle::update(deltaTime);
}

void MovableRectangle::handleCollisionTop(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight)
{
    centrePosition.y = tileCentres.top.y + averageHeight;
    velocity.y = 0;
}
void MovableRectangle::handleCollisionBottom(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight)
{
    centrePosition.y = tileCentres.bottom.y - averageHeight;
    isOnGround = true;
    velocity.y = 0;
}
void MovableRectangle::handleCollisionLeft(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight)
{
    centrePosition.x = tileCentres.left.x + averageWidth;
    velocity.x = 0;
}
void MovableRectangle::handleCollisionRight(TileCentres &tileCentres, Vector2 &centrePosition, double averageWidth, double averageHeight)
{
    centrePosition.x = tileCentres.right.x - averageWidth;
    velocity.x = 0;
}

GETTER_AND_SETTER_CPP(Vector2, MovableRectangle, velocity, Velocity)