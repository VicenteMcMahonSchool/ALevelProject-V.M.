#include "game_objects_class.hpp"
#include "../game_objects/game_object/game_object.hpp"

GETTER_CPP(size_t, GameObjects, capacity, Capacity)

GameObjects::GameObjects(void)
{
    gameObjects = new GameObject[INITIAL_NUMBER_OF_GAME_OBJECTS]{};
    capacity = INITIAL_NUMBER_OF_GAME_OBJECTS;
    index = 0;
}

GameObjects::~GameObjects()
{
    delete[] gameObjects;
}

// template <class... Arguments>
// void GameObjects::construct(size_t index, Arguments... arguments)
// {
// GAME_OBJECT_SWITCH_VALUES(gameObject = typeof(GameObject){arguments})
// }

void GameObjects::makeEmpty(void)
{
    index = 0;
    delete[] gameObjects;
    gameObjects = new GameObject[INITIAL_NUMBER_OF_GAME_OBJECTS]{};
}

GameObjectUnion *GameObjects::add(GAME_OBJECT_TYPE type)
{
    if (index >= capacity)
        return NULL;
    if (type == GENERAL_GAME_OBJECT)
        new (gameObjects + index) GameObject{GENERAL_GAME_OBJECT};
    else if (type == RECTANGLE)
        new (gameObjects + index) GameObject{RECTANGLE};
    else if (type == MOVABLE_RECTANGLE)
        new (gameObjects + index) GameObject{MOVABLE_RECTANGLE};
    else if (type == BUTTON)
        new (gameObjects + index) GameObject{BUTTON};
    else if (type == TILE_MAP)
        new (gameObjects + index) GameObject{TILE_MAP};
    else if (type == PLAYER)
        new (gameObjects + index) GameObject{PLAYER};
    else if (type == ENEMY)
        new (gameObjects + index) GameObject{ENEMY};
    return &gameObjects[index++].value;
}

GameObjectUnion *GameObjects::getGameObjectOfType(GAME_OBJECT_TYPE type)
{
    GameObjectUnion *output[1] = {NULL};
    getGameObjectsOfType(type, output, 1);
    return *output;
}
size_t GameObjects::getGameObjectsOfType(GAME_OBJECT_TYPE type, GameObjectUnion *output[], size_t lengthOfOutput)
{
    size_t nextSetIndex = 0;
    for (size_t i = 0; i < index; i++)
        if (gameObjects[i].type == type && nextSetIndex < lengthOfOutput)
            output[nextSetIndex++] = &gameObjects[i].value;
    return nextSetIndex;
}

void GameObjects::tick(void)
{
    for (size_t i = 0; i < index; i++)
        gameObjects[i].tick();
}

void GameObjects::update(double deltaTime)
{
    for (size_t i = 0; i < index; i++)
        gameObjects[i].update(deltaTime);
}

void GameObjects::draw(void)
{
    for (size_t i = 0; i < index; i++)
        gameObjects[i].draw();
}

void GameObjects::drawShadows(void)
{
    for (size_t i = 0; i < index; i++)
        gameObjects[i].drawShadows();
}
