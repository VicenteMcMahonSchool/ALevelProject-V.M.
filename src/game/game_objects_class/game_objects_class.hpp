#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <any>
#include "../macros/macros.hpp"
#include "../global/global.hpp"

#define GAME_OBJECT_SWITCH_VALUES(expression)                        \
    {                                                                \
        switch (type)                                                \
        {                                                            \
        case GENERAL_GAME_OBJECT:                                    \
        {                                                            \
            GeneralGameObject &gameObject = value.generalGameObject; \
            break;                                                   \
        }                                                            \
        case RECTANGLE:                                              \
        {                                                            \
            Rectangle &gameObject = value.rectangle;                 \
            expression;                                              \
            break;                                                   \
        }                                                            \
        case MOVABLE_RECTANGLE:                                      \
        {                                                            \
            MovableRectangle &gameObject = value.movableRectangle;   \
            expression;                                              \
            break;                                                   \
        }                                                            \
        case TILE_MAP:                                               \
        {                                                            \
            TileMap &gameObject = value.tileMap;                     \
            expression;                                              \
            break;                                                   \
        }                                                            \
        case PLAYER:                                                 \
        {                                                            \
            Player &gameObject = value.player;                       \
            expression;                                              \
            break;                                                   \
        }                                                            \
        case BUTTON:                                                 \
        {                                                            \
            Button &gameObject = value.button;                       \
            expression;                                              \
            break;                                                   \
        }                                                            \
        case ENEMY:                                                  \
        {                                                            \
            Enemy &gameObject = value.enemy;                         \
            expression;                                              \
            break;                                                   \
        }                                                            \
        }                                                            \
    }
// #define GAME_OBJECT_SWITCH_VALUES(expression)   \
//     {                                           \
//         switch (type)                           \
//         {                                       \
//         case GENERAL_GAME_OBJECT:               \
//             value.generalGameObject.expression; \
//             break;                              \
//         case RECTANGLE:                         \
//             value.rectangle.expression;         \
//             break;                              \
//         case MOVABLE_RECTANGLE:                 \
//             value.movableRectangle.expression;  \
//             break;                              \
//         case TILE_MAP:                          \
//             value.tileMap.expression;           \
//             break;                              \
//         case PLAYER:                            \
//             value.player.expression;            \
//             break;                              \
//         case BUTTON:                            \
//             value.button.expression;            \
//             break;                              \
//         case ENEMY:                             \
//             value.enemy.expression;             \
//             break;                              \
//         }                                       \
//     }

#define INITIAL_NUMBER_OF_GAME_OBJECTS 64

struct GameObject;
union GameObjectUnion;

class GameObjects
{
private:
    GameObject *gameObjects;
    size_t index;
    GETTER_HPP(size_t, capacity, Capacity)

public:
    GameObjects(void);
    ~GameObjects();
    template <class... Arguments>
    void construct(Arguments... arguments);
    void makeEmpty(void);
    GameObjectUnion *add(GAME_OBJECT_TYPE type);
    GameObjectUnion *getGameObjectOfType(GAME_OBJECT_TYPE type);
    size_t getGameObjectsOfType(GAME_OBJECT_TYPE type, GameObjectUnion *output[], size_t lengthOfOutput);
    void tick(void);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
};