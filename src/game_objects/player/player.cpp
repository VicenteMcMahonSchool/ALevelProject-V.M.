#include "./player.hpp"

Player::Player(Vector2 position) : MovableRectangle(position, {0X33, 0X33, 0X77, 0XFF}, tileMap.getTileSize(), tileMap.getTileSize())
{
    gravity = PLAYER_GRAVITY;
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
    const TILE_TYPE *centreTile = tileMap.getTileAtPosition(position + (Vector2){(double)rectangle.w / 2, (double)rectangle.h / 2});
    if (centreTile != NULL)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        if ((getTileAttributes(centreTile).isCollidable || *centreTile == TILE_LOSE))
        {
            SDL_SetRenderDrawColour(renderer, 0XFF, 0X00, 0X00, 0X55);
            SDL_Rect rectangle{0, 0, windowWidth, windowHeight};
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            screen = SCREEN_MENU;
        }
        else if (*centreTile == TILE_WIN)
        {
            SDL_SetRenderDrawColour(renderer, 0X00, 0XFF, 0X00, 0X55);
            SDL_Rect rectangle{0, 0, windowWidth, windowHeight};
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            screen = SCREEN_MENU;
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
    double length = deltaVelocity.length();
    if (length != 0)
        velocity += deltaVelocity / length * PLAYER_SPEED;
    MovableRectangle::update(deltaTime);
}