#include "input.hpp"

unsigned char keysDown[SDL_NUM_SCANCODES / 8] = {0};
unsigned char controllerButtonsDown[32] = {0};

bool isButtonDown(SDL_Scancode scancode)
{
    return keysDown[scancode / 8] >> (scancode % 8) & 1;
}
bool isButtonDown(Uint8 button)
{
    return controllerButtonsDown[button / 8] >> (button % 8) & 1;
}

void setButtonDown(SDL_Scancode scancode)
{
    keysDown[scancode / 8] |= 1 << (scancode % 8);
}
void setButtonDown(Uint8 button)
{
    controllerButtonsDown[button / 8] |= 1 << (button % 8);
}

void unsetButtonDown(SDL_Scancode scancode)
{
    keysDown[scancode / 8] &= ~(1 << (scancode % 8));
}
void unsetButtonDown(Uint8 button)
{
    controllerButtonsDown[button / 8] &= ~(1 << (button % 8));
}

void unsetAllButtons(void)
{
    for (size_t i = 0; i < SDL_NUM_SCANCODES / 8; i++)
        keysDown[i] = 0;
    for (size_t i = 0; i < 32; i++)
        controllerButtonsDown[i] = 0;
}