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
private:
    GameObject *gameObjects;
    size_t index;
    GETTER_HPP(size_t, capacity, Capacity)

public:
    GameObjects(void);
    ~GameObjects();
    void makeEmpty(void);
    GameObjectUnion *add(GAME_OBJECT_TYPE type);
    GameObjectUnion *getGameObjectOfType(GAME_OBJECT_TYPE type);
    void getGameObjectsOfType(GAME_OBJECT_TYPE type, GameObjectUnion *output[], size_t lengthOfOutput);
    void tick(void);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
};