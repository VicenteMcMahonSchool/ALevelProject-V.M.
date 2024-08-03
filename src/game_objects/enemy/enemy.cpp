#include "enemy.hpp"
#include "../tile_map/tile_map.hpp"

Enemy::Enemy(Vector2 position) : MovableRectangle(position, {0X33, 0X77, 0X33, 0XFF}, tileMap.getTileSize(), tileMap.getTileSize()) {}
Enemy::Enemy(void) : Enemy({0, 0}) {}