#include "./movable_rectangle.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../game_object/game_object.hpp"

MovableRectangle::MovableRectangle(MOVABLE_RECTANGLE_CONSTRUCTOR_ARGUMENTS) : Rectangle(position, colour, width, height), velocity({0, 0}) {}
void MovableRectangle::update(double deltaTime)
{
    TileMap *tileMap = &gameObjects.getGameObjectOfType(TILE_MAP)->tileMap; // Made it a pointer to avoid copying the tile map.
    double localGravity = isOnGround ? 0 : gravity;
    position.y += (velocity.y * deltaTime + localGravity / 2 * deltaTime * deltaTime) * tileMap->getTileSize() / 120;
    velocity.y += localGravity * deltaTime;
    double newVelocityX = velocity.x * pow(MOVABLE_RECTANGLE_DAMPENING_EVERY_1000TH_OF_SECOND, deltaTime);
    position.x += ((newVelocityX - velocity.x) / log(MOVABLE_RECTANGLE_DAMPENING_EVERY_1000TH_OF_SECOND)) * tileMap->getTileSize() / 120;
    velocity.x = newVelocityX;
    isOnGround = false;
    Vector2 centrePosition = position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    unsigned int tileSize = tileMap->getTileSize();
    double averageWidth = (double)(tileSize + rectangle.w) / 2;
    double averageHeight = (double)(tileSize + rectangle.h) / 2;
    TilesAroundTile tiles = tileMap->getTilesAroundPosition(centrePosition);
    TileCentres tileCentres = tileMap->getTileCentresAroundPositionOfTile(tiles.centre);
    if (getTileAttributes(tiles.top).isCollisionDetectable && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        if (getTileAttributes(tiles.top).isCollidable)
            handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.top, this);
    }
    else if (getTileAttributes(tiles.topLeft).isCollisionDetectable && (centrePosition - tileCentres.topLeft).isYBiggerThanX() && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        if (getTileAttributes(tiles.topLeft).isCollidable)
            handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topLeft, this);
    }
    else if (getTileAttributes(tiles.topRight).isCollisionDetectable && (tileCentres.topRight - centrePosition).isNegativeYBiggerThanX() && centrePosition.y < tileCentres.top.y + averageHeight)
    {
        if (getTileAttributes(tiles.topRight).isCollidable)
            handleCollisionTop(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topRight, this);
    }

    if (getTileAttributes(tiles.bottom).isCollisionDetectable && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        if (getTileAttributes(tiles.bottom).isCollidable)
            handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottom, this);
    }
    else if (getTileAttributes(tiles.bottomLeft).isCollisionDetectable && (centrePosition - tileCentres.bottomLeft).isNegativeYBiggerThanX() && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        if (getTileAttributes(tiles.bottomLeft).isCollidable)
            handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomLeft, this);
    }
    else if (getTileAttributes(tiles.bottomRight).isCollisionDetectable && (tileCentres.bottomRight - centrePosition).isYBiggerThanX() && centrePosition.y > tileCentres.bottom.y - averageHeight)
    {
        if (getTileAttributes(tiles.bottomRight).isCollidable)
            handleCollisionBottom(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomRight, this);
    }

    if (getTileAttributes(tiles.left).isCollisionDetectable && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        if (getTileAttributes(tiles.left).isCollidable)
            handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.left, this);
    }
    else if (getTileAttributes(tiles.topLeft).isCollisionDetectable && (centrePosition - tileCentres.topLeft).isXBiggerThanY() && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        if (getTileAttributes(tiles.topLeft).isCollidable)
            handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topLeft, this);
    }
    else if (getTileAttributes(tiles.bottomLeft).isCollisionDetectable && (centrePosition - tileCentres.bottomLeft).isYBiggerThanNegativeX() && centrePosition.x < tileCentres.left.x + averageWidth)
    {
        if (getTileAttributes(tiles.bottomLeft).isCollidable)
            handleCollisionLeft(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomLeft, this);
    }

    if (getTileAttributes(tiles.right).isCollisionDetectable && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        if (getTileAttributes(tiles.right).isCollidable)
            handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.right, this);
    }
    else if (getTileAttributes(tiles.topRight).isCollisionDetectable && (centrePosition - tileCentres.topRight).isNegativeYBiggerThanX() && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        if (getTileAttributes(tiles.topRight).isCollidable)
            handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.topRight, this);
    }
    else if (getTileAttributes(tiles.bottomRight).isCollisionDetectable && (centrePosition - tileCentres.bottomRight).isYBiggerThanX() && centrePosition.x > tileCentres.right.x - averageWidth)
    {
        if (getTileAttributes(tiles.bottomRight).isCollidable)
            handleCollisionRight(tileCentres, centrePosition, averageWidth, averageHeight);
        if (onCollision != NULL)
            onCollision((const unsigned char *)tiles.bottomRight, this);
    }
    if (getTileAttributes(tiles.centre).isCollisionDetectable)
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