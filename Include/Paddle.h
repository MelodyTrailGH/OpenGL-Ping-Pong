#ifndef PADDLE_H
#define PADDLE_H

#include "SDL_keycode.h"
#include <Graphics.h>
#include <stdint.h>

typedef struct Ball {
	int32_t x;
	int32_t y;
} Ball;

extern void update_ball( Ball *ball, float delta, SDL_KeyCode up,
                         SDL_KeyCode down );
extern void draw_ball( Ball *ball, Color *color );

#endif // PADDLE_H