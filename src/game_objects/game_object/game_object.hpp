#pragma once
#include "../player/player.hpp"
#include "../tile_map/tile_map.hpp"

enum GAME_OBJECT_TYPE
{
    GENERAL_GAME_OBJECT,
    RECTANGLE,
    MOVABLE_RECTANGLE,
    TILE_MAP,
    PLAYER
};

union GameObjectUnion
{
    GameObjectUnion(void);
    ~GameObjectUnion();
    GeneralGameObject *generalGameObject;
    Rectangle *rectangle;
    MovableRectangle *movableRectangle;
    TileMap *tileMap;
    Player *player;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value{};
    GameObject(GeneralGameObject *value);
    GameObject(Rectangle *value);
    GameObject(MovableRectangle *value);
    GameObject(TileMap *value);
    GameObject(Player *value);
    void update(double deltaTime);
    void draw(void);
};