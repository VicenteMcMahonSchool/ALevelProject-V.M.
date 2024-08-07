#include "enemy.hpp"
#include "../tile_map/tile_map.hpp"

Enemy::Enemy(ENEMY_CONSTRUCTOR_ARGUMENTS) : MovableRectangle(position, {0X33, 0X77, 0X33, 0XFF}, tileMap.getTileSize(), tileMap.getTileSize()) {}