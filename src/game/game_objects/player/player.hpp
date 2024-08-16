#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../../input/input.hpp"

#define PLAYER_CONSTRUCTOR_ARGUMENTS Vector2 position
#define PLAYER_CONSTRUCTOR_ARGUMENTS_NAMES position
#define PLAYER_GRAVITY 0.002
#define PLAYER_SPEED 0.001
#define PLAYER_JUMP_SPEED 1
#define TIME_SCALE_EQUATION(value) exp(-pow(16 * value, log(log(2)) / log(2))) + 0.05

void playerHandleCollision(const /* TILE_TYPE */ unsigned char *tile, MovableRectangle *movableRectangle);
class Player : public MovableRectangle
{
public:
    Player(PLAYER_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
};