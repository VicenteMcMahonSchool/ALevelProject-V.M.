#pragma once
#include "../movable_rectangle/movable_rectangle.hpp"
#include "../../keys_down/keys_down.hpp"
#include "../tile_map/tile_map.hpp"

#define PLAYER_GRAVITY 0.0001
#define PLAYER_SPEED 0.01
class Player : public MovableRectangle
{
public:
    Player(Vector2 position);
    void update(double deltaTime);
};