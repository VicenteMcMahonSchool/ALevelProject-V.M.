#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../../input/input.hpp"

#define PLAYER_CONSTRUCTOR_ARGUMENTS Vector2 position
#define PLAYER_CONSTRUCTOR_ARGUMENTS_NAMES position
#define PLAYER_GRAVITY 0.002
#define PLAYER_SPEED 0.001

void playerHandleCollision(const /* TILE_TYPE */ unsigned char *tile, MovableRectangle *movableRectangle);
class Player : public MovableRectangle
{
public:
    Player(PLAYER_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
};