#include "./general_game_object.hpp"
#include <stdio.h>

GeneralGameObject::GeneralGameObject(GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS) : position(position) {}
void GeneralGameObject::tick(void) {}
void GeneralGameObject::update(double deltaTime) {}
void GeneralGameObject::draw(void) {}
void GeneralGameObject::drawShadows(void) {}
GETTER_AND_SETTER_CPP(Vector2, GeneralGameObject, position, Position)
