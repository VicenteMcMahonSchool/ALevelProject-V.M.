#include "keys_down.hpp"

unsigned char keysDown[SDL_NUM_SCANCODES / 8] = {0};

bool isKeyDown(SDL_Scancode scancode)
{
    return keysDown[scancode / 8] >> (scancode % 8) & 1;
}

void setKeyDown(SDL_Scancode scancode)
{
    keysDown[scancode / 8] |= 1 << (scancode % 8);
}

void unsetKeyDown(SDL_Scancode scancode)
{
    keysDown[scancode / 8] &= ~(1 << (scancode % 8));
}

void unsetAllKeys(void)
{
    for (size_t i = 0; i < SDL_NUM_SCANCODES / 8; i++)
        keysDown[i] = 0;
}