#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../../input/input.hpp"

#define PLAYER_GRAVITY 0.002
#define PLAYER_SPEED 0.01
void playerHandleCollision(const TILE_TYPE *tile, MovableRectangle *movableRectangle);
class Player : public MovableRectangle
{
public:
    Player(Vector2 position);
    void update(double deltaTime);
};