#include "./general_game_object.hpp"

GeneralGameObject::GeneralGameObject(GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS) : position(position) {}
void GeneralGameObject::update(double deltaTime) {}
void GeneralGameObject::draw(void) {}
GETTER_AND_SETTER_CPP(Vector2, GeneralGameObject, position, Position)