#pragma once
#include <SDL2/SDL.h>

/**This is a list of all the keys that are pressed.*/
extern unsigned char keysDown[64];
extern unsigned char controllerButtonsDown[32];

/**
 * @param scancode The scan code of the key.
 * @brief This returns true if a scan code has been pressed.
 */
bool isButtonDown(SDL_Scancode scancode);
/**
 * @param button The button pressed.
 * @brief This returns true if a scan code has been pressed.
 */
bool isButtonDown(Uint8 button);

/**
 * @param scancode The scan code of the key.
 * @brief This sets the key in the 'keysDown' array to true.
 */
void setButtonDown(SDL_Scancode scancode);
/**
 * @param button The button pressed.
 * @brief This sets the key in the 'keysDown' array to true.
 */
void setButtonDown(Uint8 button);

/**
 * @param scancode The scan code of the key.
 * @brief This sets the key in the 'keysDown' array to false.
 */
void unsetButtonDown(SDL_Scancode scancode);
/**
 * @param button The button pressed.
 * @brief This sets the key in the 'keysDown' array to false.
 */
void unsetButtonDown(Uint8 button);

/**
 * @brief This sets all keys in the 'keysDown' array to false.
 */
void unsetAllButtons(void);