#include "SDL_events.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "Utility.h"
#include <Config.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NORMALIZE( value ) ( 1.0F / 255.0F ) * value

int main( int argc, char **argv ) {
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) != 0 ) {
		fprintf( stderr, "SDL failed to initialize.\nError: %s\n",
		         SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	SDL_Window *window = SDL_CreateWindow( "Ping Pong", SDL_WINDOWPOS_CENTERED,
	                                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
	                                       WINDOW_HEIGHT, SDL_WINDOW_OPENGL );
	if ( window == NULL ) {
		fprintf( stderr, "SDL failed to create a window.\nError: %s\n",
		         SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION );
	SDL_GLContext *context = SDL_GL_CreateContext( window );

	const char *vshader = readTextFile( text_format(
	    "%s/%s/default.fs", getApplicationDirectory( ), RESOURCE_PATH ) );

	fprintf( stdout, "%s\n", vshader );

	bool should_close = false;
	while ( !should_close ) {
		SDL_Event event;
		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_QUIT ) {
				should_close = true;
			}
		}
		glClear( GL_COLOR_BUFFER_BIT );
		SDL_GL_SwapWindow( window );
		SDL_Delay( 16 );
	}

	SDL_Quit( );
}