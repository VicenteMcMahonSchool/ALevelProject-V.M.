#pragma once
#include <SDL2/SDL.h>

/**This is a list of all the keys that are pressed.*/
extern unsigned char keysDown[64];

/**
 * @param scancode The scan code of the key.
 * @brief This returns true if a scan code has been pressed.
 */
bool isKeyDown(SDL_Scancode scancode);

/**
 * @param scancode The scan code of the key.
 * @brief This sets the key in the 'keysDown' array to true.
 */
void setKeyDown(SDL_Scancode scancode);

/**
 * @param scancode The scan code of the key.
 * @brief This sets the key in the 'keysDown' array to false.
 */
void unsetKeyDown(SDL_Scancode scancode);

/**
 * @brief This sets all keys in the 'keysDown' array to false.
 */
void unsetAllKeys(void);