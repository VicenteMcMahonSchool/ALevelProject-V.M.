#include "enemy.hpp"

Enemy::Enemy(Vector2 position) : MovableRectangle(position, {0X33, 0X77, 0X33, 0XFF}, tileMap.getTileSize(), tileMap.getTileSize()) {}