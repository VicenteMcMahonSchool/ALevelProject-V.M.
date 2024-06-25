#include "./player.hpp"

Player::Player(Vector2 position) : MovableRectangle(position, {0X33, 0X33, 0X77, 0XFF}, 128, 128) {}
void Player::update(double deltaTime)
{
    Vector2 deltaVelocity{0, 0};
    if (isKeyDown(SDL_SCANCODE_A))
        deltaVelocity.x -= 1;
    else if (isKeyDown(SDL_SCANCODE_D))
        deltaVelocity.x += 1;
    else if (isKeyDown(SDL_SCANCODE_W))
        deltaVelocity.y -= 1;
    else if (isKeyDown(SDL_SCANCODE_S))
        deltaVelocity.y += 1;
    double length = deltaVelocity.length();
    if (length != 0)
        this->velocity += deltaVelocity / length * PLAYER_SPEED;
    MovableRectangle::update(deltaTime);
}