#include "./game_object.hpp"

GameObjectUnion::GameObjectUnion(void) : generalGameObject({0, 0}) {}
GameObjectUnion::~GameObjectUnion(void) {}

GameObject::GameObject(GeneralGameObject value)
{
    this->value.generalGameObject = value;
}
GameObject::GameObject(Rectangle value)
{
    this->value.rectangle = value;
}
GameObject::GameObject(MovableRectangle value)
{
    this->value.movableRectangle = value;
}
GameObject::GameObject(TileMap value)
{
    this->value.tileMap = value;
}

void GameObject::update(double deltaTime)
{
    switch (this->type)
    {
    case RECTANGLE:
        this->value.rectangle.update(deltaTime);
        break;
    case MOVABLE_RECTANGLE:
        this->value.movableRectangle.update(deltaTime);
        break;
    }
}
void GameObject::draw(void)
{
    switch (this->type)
    {
    case RECTANGLE:
        this->value.rectangle.draw();
        break;
    case MOVABLE_RECTANGLE:
        this->value.movableRectangle.draw();
        break;
    }
}
