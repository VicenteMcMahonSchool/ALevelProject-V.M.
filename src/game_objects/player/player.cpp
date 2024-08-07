#include "./player.hpp"
#include "../../game_objects_class/game_objects_class.hpp"
#include "../game_object/game_object.hpp"

Player::Player(PLAYER_CONSTRUCTOR_ARGUMENTS) : MovableRectangle(position, {0X33, 0X33, 0X77, 0XFF}, gameObjects.getGameObject(TILE_MAP)->value.tileMap.getTileSize(), gameObjects.getGameObject(TILE_MAP)->value.tileMap.getTileSize())
{
    onCollision = &playerHandleCollision;
    gravity = PLAYER_GRAVITY;
}
void playerHandleCollision(const unsigned char *tile, MovableRectangle *movableRectangle)
{
    TileMap *tileMap = &gameObjects.getGameObject(TILE_MAP)->value.tileMap; // Made it a pointer to avoid copying the tile map.
    const TILE_TYPE *centreTile = tileMap->getTileAtPosition(movableRectangle->getPosition() + (Vector2){(double)movableRectangle->getRectangle().w / 2, (double)movableRectangle->getRectangle().h / 2});
    if (*tile == TILE_LOSE || ((const TILE_TYPE *)tile == centreTile && getTileAttributes((const TILE_TYPE *)tile).isCollidable))
        screen = SCREEN_LOSE;
    else if (*tile == TILE_WIN)
        screen = SCREEN_WIN;
}

void Player::update(double deltaTime)
{
    Vector2 deltaVelocity{0, 0};
    if (isButtonDown(SDL_SCANCODE_A) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
        deltaVelocity.x -= 1;
    if (isButtonDown(SDL_SCANCODE_D) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
        deltaVelocity.x += 1;
    if ((isButtonDown(SDL_SCANCODE_SPACE) || isButtonDown(SDL_CONTROLLER_BUTTON_A)) && isOnGround)
    {
        isOnGround = false;
        velocity.y -= 1;
    }
    double length = deltaVelocity.length();
    if (length != 0)
        velocity += deltaVelocity / length * PLAYER_SPEED;
    MovableRectangle::update(deltaTime);
}