#include "game_objects_class.hpp"
#include "../game_objects/game_object/game_object.hpp"

GETTER_CPP(size_t, GameObjects, capacity, Capacity)

GameObjects::GameObjects(void)
{
    gameObjects = (GameObject *)malloc(sizeof(GameObject) * INITIAL_NUMBER_OF_GAME_OBJECTS);
    capacity = INITIAL_NUMBER_OF_GAME_OBJECTS;
    index = 0;
}

GameObjects::~GameObjects()
{
    free(gameObjects);
}

void GameObjects::makeEmpty(void)
{
    index = 0;
}

GameObjectUnion *GameObjects::add(GAME_OBJECT_TYPE type)
{
    GameObject gameObject{GENERAL_GAME_OBJECT};
    if (type == GENERAL_GAME_OBJECT)
        gameObject = GameObject(GENERAL_GAME_OBJECT);
    else if (type == RECTANGLE)
        gameObject = GameObject(RECTANGLE);
    else if (type == RECTANGLE)
        gameObject = GameObject(RECTANGLE);
    else if (type == MOVABLE_RECTANGLE)
        gameObject = GameObject(MOVABLE_RECTANGLE);
    else if (type == BUTTON)
        gameObject = GameObject(BUTTON);
    else if (type == TILE_MAP)
        gameObject = GameObject(TILE_MAP);
    else if (type == PLAYER)
        gameObject = GameObject(PLAYER);
    else if (type == ENEMY)
        gameObject = GameObject(ENEMY);

    if (index < capacity)
        goto addToArray;
    else
    {
        void *newArray = realloc(gameObjects, capacity * 2);
        if (newArray == NULL)
            return NULL;
        gameObjects = (GameObject *)newArray;
    }
addToArray:
    gameObjects[index] = gameObject;
    return &gameObjects[index++].value;
}

GameObjectUnion *GameObjects::getGameObjectOfType(GAME_OBJECT_TYPE type)
{
    GameObjectUnion *output[1] = {NULL};
    getGameObjectsOfType(type, output, 1);
    return *output;
}
void GameObjects::getGameObjectsOfType(GAME_OBJECT_TYPE type, GameObjectUnion *output[], size_t lengthOfOutput)
{
    size_t nextSetIndex = 0;
    for (size_t i = 0; i < index; i++)
        if (gameObjects[i].type == type && nextSetIndex < lengthOfOutput)
            output[nextSetIndex++] = &gameObjects[i].value;
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
