#include "./game_object.hpp"

GameObjectUnion::GameObjectUnion(void) : generalGameObject(NULL) {}
GameObjectUnion::~GameObjectUnion(void) {}

GameObject::GameObject(GeneralGameObject *value)
{
    this->type = GENERAL_GAME_OBJECT;
    this->value.generalGameObject = value;
}
GameObject::GameObject(Rectangle *value)
{
    this->type = RECTANGLE;
    this->value.rectangle = value;
}
GameObject::GameObject(MovableRectangle *value)
{
    this->type = MOVABLE_RECTANGLE;
    this->value.movableRectangle = value;
}
GameObject::GameObject(TileMap *value)
{
    this->type = TILE_MAP;
    this->value.tileMap = value;
}
GameObject::GameObject(Player *value)
{
    this->type = PLAYER;
    this->value.player = value;
}

void GameObject::update(double deltaTime)
{
    switch (this->type)
    {
    case GENERAL_GAME_OBJECT:
        this->value.generalGameObject->update(deltaTime);
        break;
    case RECTANGLE:
        this->value.rectangle->update(deltaTime);
        break;
    case MOVABLE_RECTANGLE:
        this->value.movableRectangle->update(deltaTime);
        break;
    case TILE_MAP:
        this->value.tileMap->update(deltaTime);
        break;
    }
}
void GameObject::draw(void)
{
    switch (this->type)
    {
    case GENERAL_GAME_OBJECT:
        this->value.generalGameObject->draw();
        break;
    case RECTANGLE:
        this->value.rectangle->draw();
        break;
    case MOVABLE_RECTANGLE:
        this->value.movableRectangle->draw();
        break;
    case TILE_MAP:
        this->value.tileMap->draw();
        break;
    }
}
