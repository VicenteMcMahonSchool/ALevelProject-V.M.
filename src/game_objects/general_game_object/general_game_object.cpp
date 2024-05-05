#include "./general_game_object.hpp"

GeneralGameObject::GeneralGameObject(Vector2 position) : position(position) {}
void GeneralGameObject::update(double deltaTime) {}
void GeneralGameObject::draw(void) {}
GETTER_AND_SETTER_CPP(Vector2, GeneralGameObject, position, Position)