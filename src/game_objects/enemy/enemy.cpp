#include "enemy.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../game_object/game_object.hpp"

Enemy::Enemy(ENEMY_CONSTRUCTOR_ARGUMENTS) : MovableRectangle(position, {0X33, 0X77, 0X33, 0XFF}, gameObjects.getGameObject(TILE_MAP)->value.tileMap.getTileSize(), gameObjects.getGameObject(TILE_MAP)->value.tileMap.getTileSize()) {}