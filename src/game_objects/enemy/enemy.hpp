#define ENEMY_INCLUDED 1
#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"

class Enemy : public MovableRectangle
{
public:
    Enemy(void);
    Enemy(Vector2 position);
};