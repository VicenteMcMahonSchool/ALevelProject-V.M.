#pragma once
#include "../rectangle/rectangle.hpp"
#include "../movable_rectangle/movable_rectangle.hpp"

enum GAME_OBJECT_TYPE
{
    RECTANGLE,
    MOVABLE_RECTANGLE
};

union GameObjectUnion
{
    Rectangle rectangle;
    MovableRectangle movableRectangle;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value;
};