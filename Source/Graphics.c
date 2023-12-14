#include "cglm/types.h"
#include <GL/glew.h>
#include <Graphics.h>
#include <math.h>
#include <stdint.h>
void drawTriangle( int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2,
                   int32_t y2 ) {
	uint32_t buffer = 0;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, ( sizeof( float ) * 6 ),
	              ( float[6] ){ ( float )x0, ( float )y0, ( float )x1,
	                            ( float )y1, ( float )x2, ( float )y2 },
	              GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ),
	                       NULL );
	glEnableVertexAttribArray( 0 );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	glDeleteBuffers( 1, &buffer );
}

void drawRectangle( int32_t x, int32_t y, int32_t width, int32_t height ) {
	uint32_t buffer = 0;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData(
	    GL_ARRAY_BUFFER, ( sizeof( float ) * 12 ),
	    ( float[12] ){ ( float )x, ( float )y, ( float )( x + width ),
	                   ( float )y, ( float )x, ( float )( y + height ),
	                   ( float )x, ( float )( y + height ),
	                   ( float )( x + width ), ( float )( y + height ),
	                   ( float )( x + width ), ( float )y },
	    GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ),
	                       NULL );
	glEnableVertexAttribArray( 0 );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	glDeleteBuffers( 1, &buffer );
}

void drawPixel( int32_t x, int32_t y ) {
	uint32_t buffer = 0;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, ( sizeof( float ) * 2 ),
	              ( float[2] ){ ( float )x, ( float )y }, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ),
	                       NULL );
	glEnableVertexAttribArray( 0 );
	glDrawArrays( GL_POINTS, 0, 1 );
	glDeleteBuffers( 1, &buffer );
}

#define DEG2RAD( deg ) ( deg * ( 3.1415926F / 180.F ) )

void drawCircle( int32_t cx, int32_t cy, float radius ) {
	float points[720];
	for ( int32_t p = 0; p < 360; p++ ) {
		points[p] = ( float )cx + cosf( DEG2RAD( p ) );
		points[p + 1] = ( float )cy + sinf( DEG2RAD( p ) );
	}
}

/*
  for(int i = 0; i < 360; i++) {
    GLfloat x = radius * cos(degToRad(i));
    GLfloat y = radius * sin(degToRad(i));

    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);
  }
*/

/*
void drawFilledelipse(GLfloat x, GLfloat y, GLfloat xcenter,GLfloat ycenter) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + ((xcenter+1)* cos(i * twicePi / triangleAmount)),
            y + ((ycenter-1)* sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}
*/