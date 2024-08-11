#include "./player.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../game_object/game_object.hpp"

Player::Player(PLAYER_CONSTRUCTOR_ARGUMENTS) : MovableRectangle(position, {0X22, 0X22, 0X44, 0XFF}, gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize(), gameObjects.getGameObjectOfType(TILE_MAP)->tileMap.getTileSize())
{
    onCollision = &playerHandleCollision;
    gravity = PLAYER_GRAVITY;
}
void playerHandleCollision(const unsigned char *tile, MovableRectangle *movableRectangle)
{
    TileMap *tileMap = &gameObjects.getGameObjectOfType(TILE_MAP)->tileMap; // Made it a pointer to avoid copying the tile map.
    const TILE_TYPE *centreTile = tileMap->getTileAtPosition(movableRectangle->getPosition() + (Vector2){(double)movableRectangle->getRectangle().w / 2, (double)movableRectangle->getRectangle().h / 2});
    if (*tile == TILE_LOSE || ((const TILE_TYPE *)tile == centreTile && getTileAttributes((const TILE_TYPE *)tile).isCollidable))
        screen = SCREEN_LOSE;
    else if (*tile == TILE_WIN)
        screen = SCREEN_WIN;
}

void Player::update(double deltaTime)
{
    if (isButtonDown(SDL_SCANCODE_A) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
        velocity.x -= PLAYER_SPEED * deltaTime;
    if (isButtonDown(SDL_SCANCODE_D) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
        velocity.x += PLAYER_SPEED * deltaTime;
    if ((isButtonDown(SDL_SCANCODE_SPACE) || isButtonDown(SDL_CONTROLLER_BUTTON_A)) && isOnGround)
    {
        isOnGround = false;
        velocity.y -= PLAYER_JUMP_SPEED; // Probably doesn't need to be multiplied by delta time as it should only be for one frame no matter the framerate.
    }
    MovableRectangle::update(deltaTime);
}