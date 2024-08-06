#pragma once
#include <stdlib.h>
#include <stddef.h>
#include "../macros/macros.hpp"
#include "../global/global.hpp"

#define INITIAL_NUMBER_OF_GAME_OBJECTS 64

struct GameObject;

class GameObjects
{
public:
    GameObjects(void);
    ~GameObjects();
    void makeEmpty(void);
    // GameObject *add(GameObject gameObject);
    GameObject *add(GAME_OBJECT_TYPE type);
    void update(double deltaTime);
    void draw(void);

private:
    GameObject *gameObjects;
    size_t index;
    size_t capacity;
};