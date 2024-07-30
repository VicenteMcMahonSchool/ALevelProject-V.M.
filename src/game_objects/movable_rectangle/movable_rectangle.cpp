#include "./movable_rectangle.hpp"

MovableRectangle::MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height) : Rectangle(position, colour, width, height), velocity({0, 0}) {}
void MovableRectangle::update(double deltaTime)
{
    double localGravity = isOnGround ? 0 : gravity;
    position += velocity * deltaTime + (Vector2){0, localGravity} / 2 * deltaTime * deltaTime;
    velocity += (Vector2){0, localGravity} * deltaTime;
    isOnGround = false;
    Vector2 centrePosition = position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    unsigned int tileSize = tileMap.getTileSize();
    double averageWidth = (double)(tileSize + rectangle.w) / 2;
    double averageHeight = (double)(tileSize + rectangle.h) / 2;
    TilesAroundTile tiles = tileMap.getTilesAroundPosition(centrePosition);
    TileCentres tileCentres = tileMap.getTileCentresAroundPositionOfTile(tiles.centre);
    if (getTileAttributes(tiles.top).isCollidable || (getTileAttributes(tiles.topLeft).isCollidable && (centrePosition - tileCentres.topLeft).isYBiggerThanX()) || (getTileAttributes(tiles.topRight).isCollidable && (tileCentres.topRight - centrePosition).isNegativeYBiggerThanX()))
    {
        if (centrePosition.y < tileCentres.top.y + averageHeight)
        {
            centrePosition.y = tileCentres.top.y + averageHeight;
            velocity.y = 0;
        }
    }
    if (getTileAttributes(tiles.bottom).isCollidable || (getTileAttributes(tiles.bottomLeft).isCollidable && (centrePosition - tileCentres.bottomLeft).isNegativeYBiggerThanX()) || (getTileAttributes(tiles.bottomRight).isCollidable && (tileCentres.bottomRight - centrePosition).isYBiggerThanX()))
    {
        if (centrePosition.y > tileCentres.bottom.y - averageHeight)
        {
            centrePosition.y = tileCentres.bottom.y - averageHeight;
            isOnGround = true;
            velocity.y = 0;
        }
    }
    if (getTileAttributes(tiles.left).isCollidable || (getTileAttributes(tiles.topLeft).isCollidable && (centrePosition - tileCentres.topLeft).isXBiggerThanY()) || (getTileAttributes(tiles.bottomLeft).isCollidable && (centrePosition - tileCentres.bottomLeft).isYBiggerThanNegativeX()))
    {
        if (centrePosition.x < tileCentres.left.x + averageWidth)
        {
            centrePosition.x = tileCentres.left.x + averageWidth;
            velocity.x = 0;
        }
    }
    if (getTileAttributes(tiles.right).isCollidable || (getTileAttributes(tiles.topRight).isCollidable && (centrePosition - tileCentres.topRight).isNegativeYBiggerThanX()) || (getTileAttributes(tiles.bottomRight).isCollidable && (centrePosition - tileCentres.bottomRight).isYBiggerThanX()))
    {
        if (centrePosition.x > tileCentres.right.x - averageWidth)
        {
            centrePosition.x = tileCentres.right.x - averageWidth;
            velocity.x = 0;
        }
    }

    position = centrePosition - (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    Rectangle::update(deltaTime);
}
GETTER_AND_SETTER_CPP(Vector2, MovableRectangle, velocity, Velocity)