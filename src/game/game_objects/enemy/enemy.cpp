#include "enemy.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../game_object/game_object.hpp"
#include "../tile_map/tile_map.hpp"

Enemy::Enemy(ENEMY_CONSTRUCTOR_ARGUMENTS)
    : MovableRectangle(
          position, {0X33, 0X77, 0X33, 0XFF},
          gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize(),
          gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize()) {}

void Enemy::update(double deltaTime) {
    Player &player = gameObjects.getGameObjectOfType(PLAYER)->player;
    TileMap &tileMap = gameObjects.getGameObjectOfType(TILE_MAP)->tileMap;
    double deltaPositionX = position.x - player.getPosition().x;
    if (deltaPositionX > 0)
        velocity.x -= PLAYER_SPEED * deltaTime;
    else if (deltaPositionX < 0)
        velocity.x += PLAYER_SPEED * deltaTime;
    if (isOnGround) {
        Vector2 lookaheadPosition;
        if (velocity.x < PLAYER_SPEED * deltaTime && velocity.x > 0)
            lookaheadPosition = position + velocity * ENEMY_LOOKAHEAD;
        else if (velocity.x > PLAYER_SPEED * deltaTime && velocity.y < 0)
            lookaheadPosition =
                position + velocity * ENEMY_LOOKAHEAD + rectangle.w;
        else
            lookaheadPosition =
                position + (velocity / abs(velocity.length())) * rectangle.w;
        TilesAroundTile tiles =
            tileMap.getTilesAroundPosition(lookaheadPosition);
        if (tileMap.getTileAttributes(tiles.centre).isCollidable ||
            !tileMap.getTileAttributes(tiles.bottom).isCollidable)
            velocity.y -= PLAYER_JUMP_SPEED;
    }
    MovableRectangle::update(deltaTime);
}