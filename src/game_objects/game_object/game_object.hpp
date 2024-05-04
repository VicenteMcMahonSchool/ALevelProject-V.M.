#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../tile_map/tile_map.hpp"

enum GAME_OBJECT_TYPE
{
    RECTANGLE,
    MOVABLE_RECTANGLE,
    TILE_MAP
};

union GameObjectUnion
{
    Rectangle rectangle;
    MovableRectangle movableRectangle;
    TileMap tileMap;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value;
};