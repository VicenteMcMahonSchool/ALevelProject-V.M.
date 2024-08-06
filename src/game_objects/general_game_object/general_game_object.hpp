#pragma once
#include "../../vector2/vector2.hpp"
#include "../../macros/macros.hpp"

#define GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS Vector2 position
#define GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS_NAMES position

class GeneralGameObject
{
public:
    GeneralGameObject(GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
    GETTER_AND_SETTER_HPP(Vector2, position, Position)
};