#include "./player.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../../input/input.hpp"
#include "../game_object/game_object.hpp"

Player::Player(PLAYER_CONSTRUCTOR_ARGUMENTS)
    : MovableRectangle(
          position, {0X22, 0X22, 0X44, 0XFF},
          gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize(),
          gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize()) {
    coins = 0;
    onCollision = &playerHandleCollision;
    onCollisionData = this;
    gravity = PLAYER_GRAVITY;
}
void playerHandleCollision(const unsigned char *tile, void *data) {
    TileMap &tileMap =
        gameObjects.getGameObjectOfType(TILE_MAP)
            ->tileMap; // Made it a reference to avoid copying the tile map.
    if (data == NULL)
        return;
    Player *player = (Player *)data;
    if (!tileMap.getTileAttributes((TILE_TYPE *)tile).isCollidable) {
        if (tile != NULL && *tile == TILE_COIN) {
            TileMap &tileMap =
                gameObjects.getGameObjectOfType(TILE_MAP)->tileMap;
            tileMap.setTileAtIndex(tileMap.getTileIndex((TILE_TYPE *)tile),
                                   TILE_COIN_DELETED);
            player->setCoins(player->getCoins() + 1);
        }
        return;
    }
    const TILE_TYPE *centreTile = tileMap.getTileAtPosition(
        player->getPosition() +
        (Vector2){(double)player->getRectangle().w / 2,
                  (double)player->getRectangle().h / 2});
    if (*tile == TILE_LOSE ||
        ((const TILE_TYPE *)tile == centreTile &&
         tileMap.getTileAttributes((const TILE_TYPE *)tile).isCollidable))
        screen = SCREEN_LOSE;
    else if (*tile == TILE_WIN)
        screen = SCREEN_WIN;
}

void Player::update(double deltaTime) {
    if (isButtonDown(SDL_SCANCODE_A) ||
        isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
        velocity.x -= PLAYER_SPEED * deltaTime;
    if (isButtonDown(SDL_SCANCODE_D) ||
        isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
        velocity.x += PLAYER_SPEED * deltaTime;
    if ((isButtonDown(SDL_SCANCODE_SPACE) ||
         isButtonDown(SDL_CONTROLLER_BUTTON_A)) &&
        isOnGround) {
        isOnGround = false;
        velocity.y -=
            PLAYER_JUMP_SPEED; // Probably doesn't need to be multiplied by
                               // delta time as it should only be for one frame
                               // no matter the framerate.
    }
    MovableRectangle::update(deltaTime);
    GameObjectUnion *enemies[gameObjects.getCapacity()];
    size_t numberOfEnemies = gameObjects.getGameObjectsOfType(
        ENEMY, enemies, sizeof(enemies) / sizeof(GameObjectUnion *));
    for (size_t i = 0; i < numberOfEnemies; i++) {
        if (enemies[i] == NULL)
            continue; // Avoids dereferencing a null pointer.
        const Vector2 &enemiesPosition = enemies[i]->enemy.getPosition();
        const SDL_Rect &enemiesRectangle = enemies[i]->enemy.getRectangle();
        if (position.x > enemiesPosition.x - rectangle.w &&
            position.x < enemiesPosition.x + enemiesRectangle.w &&
            position.y > enemiesPosition.y - rectangle.h &&
            position.y < enemiesPosition.y + enemiesRectangle.h)
            screen = SCREEN_LOSE;
    }
    if (screen == SCREEN_GAME_TIME_SCALE) {
        double velocityLengthSquared = velocity.lengthSquared();
        timeScale = TIME_SCALE_EQUATION(velocityLengthSquared);
    }
}
GETTER_AND_SETTER_CPP(unsigned int, Player, coins, Coins)
