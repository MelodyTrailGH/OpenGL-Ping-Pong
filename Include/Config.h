#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define OPENGL_MAJOR_VERSION 2
#define OPENGL_MINOR_VERSION 0

#if defined( _WIN32 )
const char RESOURCE_PATH[11] = "Resources";
#elif defined( __APPLE__ )
#include <TargetConditionals.h>
#if defined( TARGET_OS_MAC )
const char RESOURCE_PATH[14] = "../Resources";
#endif
#endif

#endif // GAME_CONFIG_H
