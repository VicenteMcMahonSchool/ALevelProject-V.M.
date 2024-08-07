#pragma once
#include <stdlib.h>
#include <stddef.h>
#include "../macros/macros.hpp"
#include "../global/global.hpp"

#define INITIAL_NUMBER_OF_GAME_OBJECTS 64

struct GameObject;
union GameObjectUnion;

class GameObjects
{
public:
    GameObjects(void);
    ~GameObjects();
    void makeEmpty(void);
    GameObjectUnion *add(GAME_OBJECT_TYPE type);
    GameObjectUnion *getGameObject(GAME_OBJECT_TYPE type);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);

private:
    GameObject *gameObjects;
    size_t index;
    size_t capacity;
};