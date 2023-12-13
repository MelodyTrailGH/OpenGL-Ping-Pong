#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>
extern void drawTriangle( int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                          int32_t x2, int32_t y2 );
extern void drawRectangle( int32_t x, int32_t y, int32_t width,
                           int32_t height );
extern void drawPixel( int32_t x, int32_t y );
typedef struct Color {
	uint8_t r;
	uint8_t b;
	uint8_t g;
	uint8_t a;
} Color;
#endif // GRAPHICS_H