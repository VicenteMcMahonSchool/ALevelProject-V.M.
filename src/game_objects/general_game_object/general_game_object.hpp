#pragma once
#include "../../vector2/vector2.hpp"
#include "../../macros/macros.hpp"

class GeneralGameObject
{
public:
    GeneralGameObject(Vector2 position);
    void update(double deltaTime);
    void draw(void);
    GETTER_AND_SETTER_HPP(Vector2, position, Position)
};