#pragma once
#include "../player/player.hpp"
#include "../enemy/enemy.hpp"
#include "../button/button.hpp"
#include "../tile_map/tile_map.hpp"

union GameObjectUnion
{
    GameObjectUnion(void);
    ~GameObjectUnion();
    GeneralGameObject generalGameObject;
    Rectangle rectangle;
    MovableRectangle movableRectangle;
    Button button;
    TileMap tileMap;
    Player player;
    Enemy enemy;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value{};
    GameObject(void);
    GameObject(GAME_OBJECT_TYPE type);
    void tick(void);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
};