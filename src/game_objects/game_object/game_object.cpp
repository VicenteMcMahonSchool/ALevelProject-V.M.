#include "./game_object.hpp"

#define SWITCH_VALUES(expression)           \
    switch (type)                           \
    {                                       \
    case GENERAL_GAME_OBJECT:               \
        value.generalGameObject.expression; \
        break;                              \
    case RECTANGLE:                         \
        value.rectangle.expression;         \
        break;                              \
    case MOVABLE_RECTANGLE:                 \
        value.movableRectangle.expression;  \
        break;                              \
    case TILE_MAP:                          \
        value.tileMap.expression;           \
        break;                              \
    case PLAYER:                            \
        value.player.expression;            \
        break;                              \
    case BUTTON:                            \
        value.button.expression;            \
        break;                              \
    case ENEMY:                             \
        value.enemy.expression;             \
    }

GameObjectUnion::GameObjectUnion(void) : generalGameObject(GeneralGameObject((Vector2){0, 0})) {}
GameObjectUnion::~GameObjectUnion(void) {}

GameObject::GameObject(GAME_OBJECT_TYPE type)
{
    this->type = type;
}

void GameObject::update(double deltaTime)
{
    // switch (type)
    // {
    // case GENERAL_GAME_OBJECT:
    //     value.generalGameObject.update(deltaTime);
    //     break;
    // case RECTANGLE:
    //     value.rectangle.update(deltaTime);
    //     break;
    // case MOVABLE_RECTANGLE:
    //     value.movableRectangle.update(deltaTime);
    //     break;
    // case TILE_MAP:
    //     value.tileMap.update(deltaTime);
    //     break;
    // case PLAYER:
    //     value.player.update(deltaTime);
    //     break;
    // case BUTTON:
    //     value.button.update(deltaTime);
    //     break;
    // case ENEMY:
    //     value.enemy.update(deltaTime);
    // }
    SWITCH_VALUES(update(deltaTime))
}
void GameObject::draw(void)
{
    // switch (type)
    // {
    // case GENERAL_GAME_OBJECT:
    //     value.generalGameObject.draw();
    //     break;
    // case RECTANGLE:
    //     value.rectangle.draw();
    //     break;
    // case MOVABLE_RECTANGLE:
    //     value.movableRectangle.draw();
    //     break;
    // case TILE_MAP:
    //     value.tileMap.draw();
    //     break;
    // case PLAYER:
    //     value.player.draw();
    //     break;
    // case BUTTON:
    //     value.button.draw();
    //     break;
    // case ENEMY:
    //     value.enemy.draw();
    // }
    SWITCH_VALUES(draw())
}

void GameObject::drawShadows(void)
{
    SWITCH_VALUES(drawShadows())
}
