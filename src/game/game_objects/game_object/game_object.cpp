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

void GameObject::tick(void)
{
    SWITCH_VALUES(tick())
}

void GameObject::update(double deltaTime)
{
    SWITCH_VALUES(update(deltaTime))
}
void GameObject::draw(void)
{
    SWITCH_VALUES(draw())
}

void GameObject::drawShadows(void)
{
    SWITCH_VALUES(drawShadows())
}
