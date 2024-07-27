#include "./movable_rectangle.hpp"

MovableRectangle::MovableRectangle(Vector2 position, SDL_Colour colour, int width, int height) : Rectangle(position, colour, width, height) {}
void MovableRectangle::update(double deltaTime)
{
    double localGravity = isOnGround ? 0 : gravity;
    position += velocity * deltaTime + (Vector2){0, localGravity} / 2 * deltaTime * deltaTime;
    velocity += (Vector2){0, localGravity} * deltaTime;
    isOnGround = false;
    Vector2 centrePosition = position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2};
    unsigned int tileSize = tileMap.getTileSize();
    double averageWidth = (tileSize + rectangle.w) / 2;
    double averageHeight = (tileSize + rectangle.h) / 2;
    TilesAroundPosition tiles = tileMap.getTilesAroundPosition(centrePosition);
    TileCentres tileCentres = tileMap.getTileCentresAroundPositionOfTile(tiles.centre);
    if ((tiles.top != NULL && *tiles.top == TILE_PLATFORM) || (tiles.topLeft != NULL && *tiles.topLeft == TILE_PLATFORM && (centrePosition - tileCentres.topLeft).isYBiggerThanX()) || (tiles.topRight != NULL && *tiles.topRight == TILE_PLATFORM && (tileCentres.topRight - centrePosition).isNegativeYBiggerThanX()))
    {
        if (centrePosition.y < tileCentres.top.y + averageHeight)
        {
            centrePosition.y = tileCentres.top.y + averageHeight;
            velocity.y = 0;
        }
    }
    if (tiles.bottom != NULL && *tiles.bottom == TILE_PLATFORM || (tiles.bottomLeft != NULL && *tiles.bottomLeft == TILE_PLATFORM && (centrePosition - tileCentres.bottomLeft).isNegativeYBiggerThanX()) || (tiles.bottomRight != NULL && *tiles.bottomRight == TILE_PLATFORM && (tileCentres.bottomRight - centrePosition).isYBiggerThanX()))
    {
        if (centrePosition.y > tileCentres.bottom.y - averageHeight)
        {
            centrePosition.y = tileCentres.bottom.y - averageHeight;
            isOnGround = true;
            velocity.y = 0;
        }
    }
    if (tiles.left != NULL && *tiles.left == TILE_PLATFORM || (tiles.topLeft != NULL && *tiles.topLeft == TILE_PLATFORM && (centrePosition - tileCentres.topLeft).isXBiggerThanY()) || (tiles.bottomLeft != NULL && *tiles.bottomLeft == TILE_PLATFORM && (centrePosition - tileCentres.bottomLeft).isYBiggerThanNegativeX()))
    {
        if (centrePosition.x < tileCentres.left.x + averageWidth)
        {
            centrePosition.x = tileCentres.left.x + averageWidth;
            velocity.x = 0;
        }
    }
    if (tiles.right != NULL && *tiles.right == TILE_PLATFORM || (tiles.topRight != NULL && *tiles.topRight == TILE_PLATFORM && (centrePosition - tileCentres.topRight).isNegativeYBiggerThanX()) || (tiles.bottomRight != NULL && *tiles.bottomRight == TILE_PLATFORM && (centrePosition - tileCentres.bottomRight).isYBiggerThanX()))
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