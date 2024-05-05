#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../tile_map/tile_map.hpp"

enum GAME_OBJECT_TYPE
{
    GENERAL_GAME_OBJECT,
    RECTANGLE,
    MOVABLE_RECTANGLE,
    TILE_MAP
};

union GameObjectUnion
{
    GameObjectUnion(void);
    ~GameObjectUnion(void);
    GeneralGameObject generalGameObject;
    Rectangle rectangle;
    MovableRectangle movableRectangle;
    TileMap tileMap;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value{};
    GameObject(GeneralGameObject value);
    GameObject(Rectangle value);
    GameObject(MovableRectangle value);
    GameObject(TileMap value);
    void update(double deltaTime);
    void draw(void);
};