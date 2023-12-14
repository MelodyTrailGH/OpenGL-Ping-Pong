#include <Config.h>
#include <Graphics.h>
#include <Utility.h>
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

SDL_Window *window = NULL;
SDL_GLContext *context = NULL;

void initialize( );

void update( float delta );
void draw( );

void updatePaddles( float delta );
void drawPaddles( );

float paddle1YPosition = ( float )PADDLE_START_Y;
float paddle2YPosition = ( float )PADDLE_START_Y;

uint32_t defaultShader;

bool shouldClose = false;

int main( void ) {

	initialize( );

	defaultShader = createShader(
	    readTextFile( text_format(
	        "%s/%s/default.vs", getApplicationDirectory( ), RESOURCE_PATH ) ),
	    readTextFile( text_format(
	        "%s/%s/default.fs", getApplicationDirectory( ), RESOURCE_PATH ) ) );

	initializeKeyboard( );

	uint64_t currentTime = 0;
	uint64_t previousTime = 0;
	float delta = 0.0f;
	while ( !shouldClose ) {
		SDL_Event event;
		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_QUIT ) {
				shouldClose = true;
			}
		}
		previousTime = currentTime;
		currentTime = SDL_GetTicks64( );
		delta = ( ( ( float )currentTime - ( float )previousTime ) / 16.6f );
		update( delta );
		draw( );

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

void update( float delta ) {
	updateKeyboard( );
	if ( isKeyPressed( SDL_SCANCODE_ESCAPE ) ) {
		shouldClose = true;
	}
	updatePaddles( delta );
}

void updatePaddles( float delta ) {
	if ( isKeyDown( PADDLE_1_UP ) ) {
		paddle1YPosition -= ( float )PADDLE_SPEED * delta;
	}

	if ( isKeyDown( PADDLE_1_DOWN ) ) {
		paddle1YPosition += ( float )PADDLE_SPEED * delta;
	}

	if ( isKeyDown( PADDLE_2_UP ) ) {
		paddle2YPosition -= ( float )PADDLE_SPEED * delta;
	}

	if ( isKeyDown( PADDLE_2_DOWN ) ) {
		paddle2YPosition += ( float )PADDLE_SPEED * delta;
	}

	if ( ( paddle1YPosition + ( float )PADDLE_HEIGHT ) <= 0.0 ) {
		paddle1YPosition = ( float )WINDOW_HEIGHT;
	} else if ( paddle1YPosition >= ( float )WINDOW_HEIGHT ) {
		paddle1YPosition = -( float )PADDLE_HEIGHT;
	}

	if ( ( paddle2YPosition + ( float )PADDLE_HEIGHT ) <= 0.0 ) {
		paddle2YPosition = ( float )WINDOW_HEIGHT;
	} else if ( paddle2YPosition >= ( float )WINDOW_HEIGHT ) {
		paddle2YPosition = -( float )PADDLE_HEIGHT;
	}
}
void draw( ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glUseProgram( defaultShader );

	mat4 projection_matrix = GLM_MAT4_IDENTITY_INIT;
	glmc_ortho( 0.0f, ( float )WINDOW_WIDTH, ( float )WINDOW_HEIGHT, 0.0f, 0.0f,
	            1.0f, projection_matrix );

	glUniformMatrix4fv( glGetUniformLocation( defaultShader, "projection" ), 1,
	                    GL_FALSE, projection_matrix[0] );

	glUniform4f( glGetUniformLocation( defaultShader, "color" ), CLEAR_COLOR_R,
	             CLEAR_COLOR_G, CLEAR_COLOR_B, CLEAR_COLOR_A );

	drawRectangle( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

	glUniform4f( glGetUniformLocation( defaultShader, "color" ), 1.0f, 0.0f,
	             0.0f, 1.0 );
	drawCircle( 0, 0, 32 );

	drawPaddles( );
}

void drawPaddles( ) {
	glUniform4f( glGetUniformLocation( defaultShader, "color" ), 1.0f, 0.0f,
	             0.0f, 1.0 );
	drawRectangle( PADDLE_1_X, ( int32_t )paddle1YPosition, PADDLE_WIDTH,
	               PADDLE_HEIGHT );

	glUniform4f( glGetUniformLocation( defaultShader, "color" ), 0.0f, 1.0f,
	             0.0f, 1.0 );
	drawRectangle( PADDLE_2_X, ( int32_t )paddle2YPosition, PADDLE_WIDTH,
	               PADDLE_HEIGHT );
}