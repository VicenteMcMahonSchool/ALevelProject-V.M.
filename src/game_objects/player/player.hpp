#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"

class Player : public MovableRectangle
{
public:
    Player(Vector2 position);
};