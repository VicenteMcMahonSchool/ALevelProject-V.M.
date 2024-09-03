#pragma once
#include "../../vector2/vector2.hpp"
#include "../../macros/macros.hpp"

#define GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS Vector2 position
#define GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS_NAMES position

class GeneralGameObject
{
public:
    GeneralGameObject(GENERAL_GAME_OBJECT_CONSTRUCTOR_ARGUMENTS);
    virtual ~GeneralGameObject() = default;
    virtual void tick(void);
    virtual void update(double deltaTime);
    virtual void draw(void);
    virtual void drawShadows(void);
    GETTER_AND_SETTER_HPP(Vector2, position, Position)
};