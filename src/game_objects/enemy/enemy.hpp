#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"

#define ENEMY_CONSTRUCTOR_ARGUMENTS Vector2 position
#define ENEMY_CONSTRUCTOR_ARGUMENTS_NAMES position
#define ENEMY_LOOKAHEAD 0.01

class Enemy : public MovableRectangle
{
public:
    Enemy(ENEMY_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
};