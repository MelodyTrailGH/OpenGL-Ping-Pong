#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL_scancode.h"
#include <SDL2/SDL_keyboard.h>
#include <stdbool.h>
#include <stdint.h>

extern void initializeKeyboard( );
extern void updateKeyboard( );
extern bool isKeyDown( SDL_Scancode key );
extern bool isKeyPressed( SDL_Scancode key );
extern bool isKeyReleased( SDL_Scancode key );

#endif // KEYBOARD_H
