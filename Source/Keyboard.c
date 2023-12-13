#include "SDL_keyboard.h"
#include "SDL_scancode.h"
#include <Keyboard.h>
#include <string.h>
struct {
	uint8_t currentInput[SDL_NUM_SCANCODES];
	uint8_t previousInput[SDL_NUM_SCANCODES];
} Keyboard;

void initializeKeyboard( ) {
	memset( Keyboard.previousInput, 0, sizeof( uint8_t ) * SDL_NUM_SCANCODES );
	memcpy( Keyboard.currentInput, SDL_GetKeyboardState( NULL ),
	        sizeof( uint8_t ) * SDL_NUM_SCANCODES );
}
void updateKeyboard( ) {
	memcpy( Keyboard.previousInput, Keyboard.currentInput,
	        sizeof( uint8_t ) * SDL_NUM_SCANCODES );
	memcpy( Keyboard.currentInput, SDL_GetKeyboardState( NULL ),
	        sizeof( uint8_t ) * SDL_NUM_SCANCODES );
}

bool isKeyDown( SDL_Scancode key ) {
	return ( Keyboard.currentInput[key] );
}
bool isKeyPressed( SDL_Scancode key ) {
	return ( Keyboard.currentInput[key] && !Keyboard.previousInput[key] );
}
bool isKeyReleased( SDL_Scancode key ) {
	return ( !Keyboard.currentInput[key] && Keyboard.previousInput[key] );
}