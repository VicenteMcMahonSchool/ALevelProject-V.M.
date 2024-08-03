#pragma once
#include "../player/player.hpp"
#include "../enemy/enemy.hpp"
#include "../button/button.hpp"

#define GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(typeName, capitalisedName, name) \
    GameObject::GameObject(typeName *value)                                   \
    {                                                                         \
        this->type = capitalisedName;                                         \
        this->value.name = value;                                             \
    }
#define GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(typeName, name) \
    GameObject(typeName *value);

enum GAME_OBJECT_TYPE
{
    GENERAL_GAME_OBJECT,
    RECTANGLE,
    MOVABLE_RECTANGLE,
    BUTTON,
    TILE_MAP,
    PLAYER,
    ENEMY
};

union GameObjectUnion
{
    GameObjectUnion(void);
    ~GameObjectUnion();
    GeneralGameObject *generalGameObject;
    Rectangle *rectangle;
    MovableRectangle *movableRectangle;
    Button *button;
    TileMap *tileMap;
    Player *player;
    Enemy *enemy;
};

class GameObject
{
public:
    GAME_OBJECT_TYPE type;
    GameObjectUnion value{};
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(GeneralGameObject, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(Rectangle, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(MovableRectangle, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(Button, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(TileMap, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(Player, value);
    GAME_OBJECT_CONSTRUCTOR_FUNCTION_HPP(Enemy, value);
    void update(double deltaTime);
    void draw(void);
};