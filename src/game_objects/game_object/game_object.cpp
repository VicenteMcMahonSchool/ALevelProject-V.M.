#include "./game_object.hpp"

GameObjectUnion::GameObjectUnion(void) : generalGameObject(NULL) {}
GameObjectUnion::~GameObjectUnion(void) {}

GameObject::GameObject(GeneralGameObject *value)
{
    type = GENERAL_GAME_OBJECT;
    this->value.generalGameObject = value;
}
GameObject::GameObject(Rectangle *value)
{
    type = RECTANGLE;
    this->value.rectangle = value;
}
GameObject::GameObject(MovableRectangle *value)
{
    type = MOVABLE_RECTANGLE;
    this->value.movableRectangle = value;
}
GameObject::GameObject(Button *value)
{
    type = BUTTON;
    this->value.button = value;
}
GameObject::GameObject(TileMap *value)
{
    type = TILE_MAP;
    this->value.tileMap = value;
}
GameObject::GameObject(Player *value)
{
    type = PLAYER;
    this->value.player = value;
}

void GameObject::update(double deltaTime)
{
    switch (type)
    {
    case GENERAL_GAME_OBJECT:
        value.generalGameObject->update(deltaTime);
        break;
    case RECTANGLE:
        value.rectangle->update(deltaTime);
        break;
    case MOVABLE_RECTANGLE:
        value.movableRectangle->update(deltaTime);
        break;
    case TILE_MAP:
        value.tileMap->update(deltaTime);
        break;
    case PLAYER:
        value.player->update(deltaTime);
    case BUTTON:
        value.button->update(deltaTime);
    }
}
void GameObject::draw(void)
{
    switch (type)
    {
    case GENERAL_GAME_OBJECT:
        value.generalGameObject->draw();
        break;
    case RECTANGLE:
        value.rectangle->draw();
        break;
    case MOVABLE_RECTANGLE:
        value.movableRectangle->draw();
        break;
    case TILE_MAP:
        value.tileMap->draw();
        break;
    case PLAYER:
        value.player->draw();
        break;
    case BUTTON:
        value.button->draw();
        break;
    }
}
