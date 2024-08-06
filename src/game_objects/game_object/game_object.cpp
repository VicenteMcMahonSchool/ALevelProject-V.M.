#include "./game_object.hpp"

GameObjectUnion::GameObjectUnion(void) : generalGameObject(GeneralGameObject((Vector2){0, 0})) {}
GameObjectUnion::~GameObjectUnion(void) {}

// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(GeneralGameObject, GENERAL_GAME_OBJECT, generalGameObject)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(Rectangle, RECTANGLE, rectangle)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(MovableRectangle, MOVABLE_RECTANGLE, movableRectangle)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(Button, BUTTON, button)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(TileMap, TILE_MAP, tileMap)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(Player, PLAYER, player)
// GAME_OBJECT_CONSTRUCTOR_FUNCTION_CPP(Enemy, ENEMY, enemy)

GameObject::GameObject(GAME_OBJECT_TYPE type)
{
    this->type = type;
}

void GameObject::update(double deltaTime)
{
    switch (type)
    {
    case GENERAL_GAME_OBJECT:
        value.generalGameObject.update(deltaTime);
        break;
    case RECTANGLE:
        value.rectangle.update(deltaTime);
        break;
    case MOVABLE_RECTANGLE:
        value.movableRectangle.update(deltaTime);
        break;
    case TILE_MAP:
        value.tileMap.update(deltaTime);
        break;
    case PLAYER:
        value.player.update(deltaTime);
        break;
    case BUTTON:
        value.button.update(deltaTime);
        break;
    case ENEMY:
        value.enemy.update(deltaTime);
    }
}
void GameObject::draw(void)
{
    switch (type)
    {
    case GENERAL_GAME_OBJECT:
        value.generalGameObject.draw();
        break;
    case RECTANGLE:
        value.rectangle.draw();
        break;
    case MOVABLE_RECTANGLE:
        value.movableRectangle.draw();
        break;
    case TILE_MAP:
        value.tileMap.draw();
        break;
    case PLAYER:
        value.player.draw();
        break;
    case BUTTON:
        value.button.draw();
        break;
    case ENEMY:
        value.enemy.draw();
    }
}
