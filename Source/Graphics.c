#include <GL/glew.h>
#include <stdint.h>
void drawTriangle( int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2,
                   int32_t y2 ) {
	const float verts[9] = { ( float )x0, ( float )y0, 0.0f,
	                         ( float )x1, ( float )y1, 0.0f,
	                         ( float )x2, ( float )y2, 0.0f };
	uint32_t buffer = 0;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ),
	                       NULL );
	glEnableVertexAttribArray( 0 );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	glDeleteBuffers( 1, &buffer );
}

void drawRectangle( int32_t x, int32_t y, int32_t width, int32_t height ) {
	drawTriangle( x, y, x + width, y, x, y + height );
	drawTriangle( x, y + height, x + width, y + height, x + width, y );
}

void drawPixel( int32_t x, int32_t y ) {
	drawRectangle( x, y, 1, 1 );
}