#pragma once
#include "../rectangle/rectangle.hpp"
#include "../movable_rectangle/movable_rectangle.hpp"

enum GAME_OBJECT_TYPE
{
    RECTANGLE,
    MOVABLE_RECTANGLE
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    union game_object
    {
        Rectangle rectangle;
        MovableRectangle movableRectangle;
    };
};