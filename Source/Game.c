#include "SDL_scancode.h"
#include "SDL_video.h"
#include "Utility.h"
#include <Config.h>
#include <Graphics.h>
#define SDL_MAIN_HANDLED
#include <GL/glew.h>
#include <Keyboard.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cglm/call.h>
#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NORMALIZE( value ) ( 1.0F / 255.0F ) * value

SDL_Window *window;
SDL_GLContext *context;

void initialize( );

int main( void ) {

	initialize( );

	uint32_t camera_shader = createShader(
	    readTextFile( text_format(
	        "%s/%s/default.vs", getApplicationDirectory( ), RESOURCE_PATH ) ),
	    readTextFile( text_format(
	        "%s/%s/default.fs", getApplicationDirectory( ), RESOURCE_PATH ) ) );

	bool should_close = false;

	initializeKeyboard( );
	while ( !should_close ) {
		SDL_Event event;
		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_QUIT ) {
				should_close = true;
			}
		}
		updateKeyboard( );
		if ( isKeyPressed( SDL_SCANCODE_ESCAPE ) ) {
			should_close = true;
		}

		glClear( GL_COLOR_BUFFER_BIT );
		drawRectangle( 0, 0, 32, 32 );
		glUseProgram( camera_shader );

		mat4 projection_matrix = GLM_MAT4_IDENTITY_INIT;
		glmc_ortho( 0.0f, ( float )WINDOW_WIDTH, ( float )WINDOW_HEIGHT, 0.0f,
		            0.0f, 1.0f, projection_matrix );
		glUniform4f( glGetUniformLocation( camera_shader, "color" ), 1.0f, 0.0f,
		             0.0f, 1.0 );
		glUniformMatrix4fv( glGetUniformLocation( camera_shader, "projection" ),
		                    1, GL_FALSE, projection_matrix[0] );

		SDL_GL_SwapWindow( window );
		SDL_Delay( 16 );
	}
	SDL_GL_DeleteContext( context );
	SDL_DestroyWindow( window );
	SDL_Quit( );
}

void initialize( ) {
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) != 0 ) {
		fprintf( stderr, "SDL failed to initialize.\nError: %s\n",
		         SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	window = SDL_CreateWindow( "Ping Pong", SDL_WINDOWPOS_CENTERED,
	                           SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
	                           WINDOW_HEIGHT, SDL_WINDOW_OPENGL );
	if ( window == NULL ) {
		fprintf( stderr, "SDL failed to create a window.\nError: %s\n",
		         SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION );
	context = SDL_GL_CreateContext( window );
	if ( context == NULL ) {
		fprintf( stderr, "SDL failed to create a OpenGL Context.\nError %s\n",
		         SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	SDL_GL_MakeCurrent( window, context );

	GLenum glew_err = glewInit( );
	if ( glew_err != GLEW_OK ) {
		fprintf( stdout, "GLEW failed to initialize.\n%s\n",
		         glewGetErrorString( glew_err ) );
		exit( EXIT_FAILURE );
	}
}