#include "./player.hpp"

Player::Player(Vector2 position) : MovableRectangle(position, {0X33, 0X33, 0X77, 0XFF}, 120, 120)
{
    gravity = PLAYER_GRAVITY;
}
void Player::update(double deltaTime)
{
    Vector2 deltaVelocity{0, 0};
    if (isKeyDown(SDL_SCANCODE_A) || isKeyDown(SDL_SCANCODE_LEFT))
        deltaVelocity.x -= 1;
    if (isKeyDown(SDL_SCANCODE_D) || isKeyDown(SDL_SCANCODE_RIGHT))
        deltaVelocity.x += 1;
    if ((isKeyDown(SDL_SCANCODE_SPACE) || isKeyDown(SDL_SCANCODE_UP)) && isOnGround)
    {
        isOnGround = false;
        velocity.y -= 1;
    }
    const TILE_TYPE *centreTile = tileMap.getTileAtPosition(position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2});
    if (centreTile != NULL && (*centreTile == TILE_WIN || *centreTile == TILE_LOSE))
    {
        screen = SCREEN_MENU;
    }
    double length = deltaVelocity.length();
    if (length != 0)
        velocity += deltaVelocity / length * PLAYER_SPEED;
    MovableRectangle::update(deltaTime);
}