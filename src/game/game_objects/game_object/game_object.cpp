#include "./game_object.hpp"

GameObjectUnion::GameObjectUnion(void) : generalGameObject(GeneralGameObject((Vector2){0, 0})) {}
GameObjectUnion::~GameObjectUnion(void) {}

GameObject::GameObject(void)
{
    this->type = GENERAL_GAME_OBJECT;
}

GameObject::GameObject(GAME_OBJECT_TYPE type)
{
    this->type = type;
}

GameObject::~GameObject()
{
    GAME_OBJECT_SWITCH_VALUES(((GeneralGameObject *)&gameObject)->~GeneralGameObject())
}

void GameObject::tick(void)
{
    GAME_OBJECT_SWITCH_VALUES(gameObject.tick())
}

void GameObject::update(double deltaTime)
{
    GAME_OBJECT_SWITCH_VALUES(gameObject.update(deltaTime))
}
void GameObject::draw(void)
{
    GAME_OBJECT_SWITCH_VALUES(gameObject.draw())
}

void GameObject::drawShadows(void)
{
    GAME_OBJECT_SWITCH_VALUES(gameObject.drawShadows())
}
