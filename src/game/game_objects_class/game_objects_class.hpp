#pragma once
#include "../global/global.hpp"
#include "../macros/macros.hpp"
#include <stddef.h>
#include <stdlib.h>

#define GAME_OBJECT_SWITCH_VALUES(expression)                                  \
    {                                                                          \
        switch (type) {                                                        \
        case GENERAL_GAME_OBJECT: {                                            \
            GeneralGameObject &gameObject = value.generalGameObject;           \
            break;                                                             \
        }                                                                      \
        case RECTANGLE: {                                                      \
            Rectangle &gameObject = value.rectangle;                           \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        case MOVABLE_RECTANGLE: {                                              \
            MovableRectangle &gameObject = value.movableRectangle;             \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        case TILE_MAP: {                                                       \
            TileMap &gameObject = value.tileMap;                               \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        case PLAYER: {                                                         \
            Player &gameObject = value.player;                                 \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        case BUTTON: {                                                         \
            Button &gameObject = value.button;                                 \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        case ENEMY: {                                                          \
            Enemy &gameObject = value.enemy;                                   \
            expression;                                                        \
            break;                                                             \
        }                                                                      \
        }                                                                      \
    }

#define INITIAL_NUMBER_OF_GAME_OBJECTS 64
#define NUMBER_OF_STATIC_GAME_OBJECTS 16

struct GameObject;
union GameObjectUnion;

class GameObjects {
  private:
    static GameObject staticGameObjects[NUMBER_OF_STATIC_GAME_OBJECTS];
    static size_t staticIndex;
    GETTER_HPP(static size_t, staticCapacity, StaticCapacity)
    GameObject *gameObjects;
    size_t index;
    GETTER_HPP(size_t, capacity, Capacity)

  public:
    GameObjects(void);
    ~GameObjects();
    void makeEmpty(void);
    GameObjectUnion *add(GAME_OBJECT_TYPE type, bool isStatic);
    GameObjectUnion *add(GAME_OBJECT_TYPE type);
    GameObjectUnion *getGameObjectOfType(GAME_OBJECT_TYPE type);
    size_t getGameObjectsOfType(GAME_OBJECT_TYPE type,
                                GameObjectUnion *output[],
                                size_t lengthOfOutput);
    void tick(void);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
};