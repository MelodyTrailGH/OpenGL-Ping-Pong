#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <SDL2/SDL_scancode.h>
#include <Utility.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define OPENGL_MAJOR_VERSION 2
#define OPENGL_MINOR_VERSION 0

#define CLEAR_COLOR_R NORMALIZE( 66 )
#define CLEAR_COLOR_G NORMALIZE( 66 )
#define CLEAR_COLOR_B NORMALIZE( 66 )
#define CLEAR_COLOR_A NORMALIZE( 255 )

#if defined( _WIN32 )
const char RESOURCE_PATH[11] = "Resources";
#elif defined( __APPLE__ )
#include <TargetConditionals.h>
#if defined( TARGET_OS_MAC )
#if defined( PACKAGED )
const char RESOURCE_PATH[14] = "../Resources";
#else
const char RESOURCE_PATH[11] = "Resources";
#endif
#endif
#endif

#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 84
#define PADDLE_MIN_Y 0
#define PADDLE_MAX_Y WINDOW_HEIGHT
#define PADDLE_SPEED 8

#define PADDLE_1_UP SDL_SCANCODE_W
#define PADDLE_1_DOWN SDL_SCANCODE_S
#define PADDLE_2_UP SDL_SCANCODE_UP
#define PADDLE_2_DOWN SDL_SCANCODE_DOWN

#define PADDLE_OFFSET 32

#define PADDLE_1_X PADDLE_OFFSET
#define PADDLE_2_X ( WINDOW_WIDTH - PADDLE_OFFSET ) - PADDLE_WIDTH

#define PADDLE_START_Y ( WINDOW_HEIGHT / 2 ) - ( PADDLE_HEIGHT / 2 )

#endif // GAME_CONFIG_H
