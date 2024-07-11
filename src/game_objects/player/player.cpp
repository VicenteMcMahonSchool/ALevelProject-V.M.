#include "./player.hpp"

Player::Player(Vector2 position) : MovableRectangle(position, {0X33, 0X33, 0X77, 0XFF}, 120, 120) {}
void Player::update(double deltaTime)
{
    *(tileMap.getTileAtPosition(position)) = TILE_PLATFORM;
    this->velocity /= 1.05;
    Vector2 deltaVelocity{0, 0};
    if (isKeyDown(SDL_SCANCODE_A))
        deltaVelocity.x -= 1;
    if (isKeyDown(SDL_SCANCODE_D))
        deltaVelocity.x += 1;
    if (isKeyDown(SDL_SCANCODE_W))
        deltaVelocity.y -= 1;
    if (isKeyDown(SDL_SCANCODE_S))
        deltaVelocity.y += 1;
    double length = deltaVelocity.length();
    if (length != 0)
        this->velocity += deltaVelocity / length * PLAYER_SPEED;
    this->velocity.y += PLAYER_GRAVITY * deltaTime;
    MovableRectangle::update(deltaTime);
}