#include "game_objects_class.hpp"
#include "../game_objects/game_object/game_object.hpp"
#include <new>

GETTER_CPP(size_t, GameObjects, capacity, Capacity)
GETTER_CPP(size_t, GameObjects, staticCapacity, StaticCapacity)

GameObject GameObjects::staticGameObjects[NUMBER_OF_STATIC_GAME_OBJECTS] = {};
size_t GameObjects::staticIndex = 0;
size_t GameObjects::staticCapacity = NUMBER_OF_STATIC_GAME_OBJECTS;

GameObjects::GameObjects(void) {
    gameObjects = new GameObject[INITIAL_NUMBER_OF_GAME_OBJECTS]{};
    capacity = INITIAL_NUMBER_OF_GAME_OBJECTS;
    index = 0;
}

GameObjects::~GameObjects() { delete[] gameObjects; }

void GameObjects::makeEmpty(void) {
    index = 0;
    for (size_t i = 0; i < INITIAL_NUMBER_OF_GAME_OBJECTS; i++)
        gameObjects[i].~GameObject();
    delete[] gameObjects;
    gameObjects = new GameObject[INITIAL_NUMBER_OF_GAME_OBJECTS]{};
}

GameObjectUnion *GameObjects::add(GAME_OBJECT_TYPE type, bool isStatic) {
    GameObject *array = isStatic ? GameObjects::staticGameObjects : gameObjects;
    size_t &currentIndex = isStatic ? staticIndex : index;
    size_t &currentCapacity = isStatic ? staticCapacity : capacity;
    if (index >= currentCapacity)
        return NULL;
    if (type == GENERAL_GAME_OBJECT)
        new (array + currentIndex) GameObject{GENERAL_GAME_OBJECT};
    else if (type == RECTANGLE)
        new (array + currentIndex) GameObject{RECTANGLE};
    else if (type == MOVABLE_RECTANGLE)
        new (array + currentIndex) GameObject{MOVABLE_RECTANGLE};
    else if (type == BUTTON)
        new (array + currentIndex) GameObject{BUTTON};
    else if (type == TILE_MAP)
        new (array + currentIndex) GameObject{TILE_MAP};
    else if (type == PLAYER)
        new (array + currentIndex) GameObject{PLAYER};
    else if (type == ENEMY)
        new (array + currentIndex) GameObject{ENEMY};
    return &array[currentIndex++].value;
}
GameObjectUnion *GameObjects::add(GAME_OBJECT_TYPE type) {
    return add(type, false);
}

GameObjectUnion *GameObjects::getGameObjectOfType(GAME_OBJECT_TYPE type) {
    GameObjectUnion *output[1] = {NULL};
    getGameObjectsOfType(type, output, 1);
    return *output;
}
size_t GameObjects::getGameObjectsOfType(GAME_OBJECT_TYPE type,
                                         GameObjectUnion *output[],
                                         size_t lengthOfOutput) {
    size_t nextSetIndex = 0;
    for (size_t i = 0; i < index; i++)
        if (gameObjects[i].type == type && nextSetIndex < lengthOfOutput)
            output[nextSetIndex++] = &gameObjects[i].value;
    for (size_t i = 0; i < staticIndex; i++)
        if (staticGameObjects[i].type == type && nextSetIndex < lengthOfOutput)
            output[nextSetIndex++] = &GameObjects::staticGameObjects[i].value;
    return nextSetIndex;
}

void GameObjects::tick(void) {
    for (size_t i = 0; i < index; i++)
        gameObjects[i].tick();
    for (size_t i = 0; i < staticIndex; i++)
        staticGameObjects[i].tick();
}

void GameObjects::update(double deltaTime) {
    for (size_t i = 0; i < index; i++)
        gameObjects[i].update(deltaTime);
    for (size_t i = 0; i < staticIndex; i++)
        staticGameObjects[i].update(deltaTime);
}

void GameObjects::draw(void) {
    for (size_t i = 0; i < index; i++)
        gameObjects[i].draw();
    for (size_t i = 0; i < staticIndex; i++)
        staticGameObjects[i].draw();
}

void GameObjects::drawShadows(void) {
    for (size_t i = 0; i < index; i++)
        gameObjects[i].drawShadows();
    for (size_t i = 0; i < staticIndex; i++)
        staticGameObjects[i].drawShadows();
}
