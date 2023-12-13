/*
Copyright (c) 2023 Anthony I. Jackson

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#include "whereami.h"
#include <Utility.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

uint64_t getFileSize( const char *path ) {
	const char *_path = text_copy( path );
#ifdef _WIN32
	_path = text_replace_char( _path, '/', '\\' );
#endif
	FILE *file = fopen( _path, "rb" );
	if ( NULL == file ) {
		return 0;
	}
	fseek( file, 0, SEEK_END );
	uint64_t size = ftell( file );
	fclose( file );
	return size;
}

uint64_t getFileDescSize( FILE *fd ) {
	if ( NULL == fd ) {
		return 0;
	}
	uint64_t start_pos = ftell( fd );
	fseek( fd, 0, SEEK_END );
	uint64_t size = ftell( fd );
	fseek( fd, start_pos, SEEK_SET );
	return size;
}

const char *readTextFile( const char *path ) {
	const char *_path = text_copy( path );
#ifdef _WIN32
	_path = text_replace_char( _path, '/', '\\' );
#endif
	FILE *file = fopen( _path, "r" );
	if ( NULL == file ) {
		return NULL;
	}
	uint64_t size = getFileDescSize( file );
	char *buffer = calloc( size, sizeof( char ) );
	fread( buffer, size, 1, file );
	return buffer;
}

const char *readTextFileDesc( FILE *fd ) {
	if ( NULL == fd ) {
		return NULL;
	}
	char *buffer = calloc( getFileDescSize( fd ), sizeof( char ) );
	fread( buffer, sizeof( *buffer ), 1, fd );
	return buffer;
}

const char *getApplicationDirectory( ) {
	int32_t path_len = wai_getExecutablePath( NULL, 0, NULL );
	char *path = calloc( path_len + 1, sizeof( char ) );
	int32_t dir_len = 0;
	wai_getExecutablePath( path, path_len, &dir_len );
	path[path_len] = '\0';
	char *dir = text_copy_length( path, dir_len );
	free( path );
	return dir;
}

char *text_format( char *fmt, ... ) {
	va_list va;
	va_start( va, fmt );
	uint64_t len = vsnprintf( NULL, 0, fmt, va ) + 1;
	char *out = calloc( len, sizeof( char ) );
	if ( out == NULL ) {
		return NULL;
	}
	va_start( va, fmt );
	vsnprintf( out, len, fmt, va );
	va_end( va );
	return out;
}

uint64_t text_length( const char *src ) {
	uint64_t length = 0;
	uint64_t index = 0;
	while ( 1 ) {
		if ( src[index] == '\0' ) {
			break;
		}
		length++;
		index++;
	}
	return length;
}

char *text_copy( const char *src ) {
	uint64_t source_length = text_length( src );
	char *copy = calloc( source_length + 1, sizeof( char ) );
	for ( uint64_t i = 0; i < source_length; i++ ) {
		copy[i] = src[i];
	}
	copy[source_length + 1] = '\0';
	return copy;
}

char *text_replace_char( const char *src, const char find, const char repl ) {
	uint64_t source_length = text_length( src );
	char *copy = text_copy( src );
	for ( uint64_t i = 0; i < source_length; i++ ) {
		if ( copy[i] == find ) {
			copy[i] = repl;
		}
	}
	return copy;
}

char *text_copy_length( const char *src, uint64_t length ) {
	char *copy = calloc( length + 1, sizeof( char ) );
	for ( uint64_t i = 0; i < length; i++ ) {
		copy[i] = src[i];
	}
	copy[length + 1] = '\0';
	return copy;
}

uint32_t createShader( const char *vertex_shader_source,
                       const char *fragment_shader_source ) {
	int error = 0;

	// Prevent morons from using uninitialized or dead strings.
	if ( vertex_shader_source == NULL ) {
		fprintf( stderr, "Vertex shader is null.\n" );
		error = 1;
	}

	if ( fragment_shader_source == NULL ) {
		fprintf( stderr, "Fragment shader is null.\n" );
		error = 1;
	}

	if ( error ) {
		return 0;
	}

	error = 0;

	// Another safety check because why not?
	if ( strlen( vertex_shader_source ) == 0 ) {
		fprintf( stderr, "Vertex shader is empty.\n" );
		error = 1;
	}

	if ( strlen( fragment_shader_source ) == 0 ) {
		fprintf( stderr, "Fragment shader is empty.\n" );
		error = 1;
	}

	if ( error ) {
		return 0;
	}

	// Now we have to make sure the runtime doesn't mess us up too.
	// Goddamn I hate this.
	if ( glCreateShader == NULL ) {
		fprintf( stderr, "\"glCreateShader\" doesn't exist.\n" );
		return 0;
	}

	if ( glShaderSource == NULL ) {
		fprintf( stderr, "\"glShaderSource\" doesn't exist.\n" );
		return 0;
	}

	if ( glCompileShader == NULL ) {
		fprintf( stderr, "\"glCompileShader\" doesn't exist.\n" );
		return 0;
	}

	if ( glGetShaderiv == NULL ) {
		fprintf( stderr, "\"glGetShaderiv\" doesn't exist.\n" );
		return 0;
	}

	if ( glGetShaderInfoLog == NULL ) {
		fprintf( stderr, "\"glGetShaderInfoLog\" doesn't exist.\n" );
		return 0;
	}

	if ( glDeleteShader == NULL ) {
		fprintf( stderr, "\"glDeleteShader\" doesn't exist.\n" );
		return 0;
	}

	// Now we get on to the real stuff.
	int success =
	    0; // This is both used for shader compilation and shader linkage.
	int shader_log_length = 0;
	char *shader_log = NULL;

	uint32_t vertex_shader = glCreateShader( GL_VERTEX_SHADER );

	// Don't question why OpenGL would ever fail this.
	if ( vertex_shader == 0 ) {
		fprintf( stderr, "OpenGL failed to create a vertex shader.\n" );
		return 0;
	}

	glShaderSource( vertex_shader, 1, &vertex_shader_source, NULL );
	glCompileShader( vertex_shader );
	glGetShaderiv( vertex_shader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		fprintf( stderr, "Vertex shader failed to compile.\n" );
		glGetShaderiv( vertex_shader, GL_INFO_LOG_LENGTH, &shader_log_length );
		shader_log = calloc( shader_log_length, sizeof( char ) );
		if ( shader_log == NULL ) {
			fprintf(
			    stderr,
			    "An error log couldn't be formed due to a memory error.\n" );
		} else {
			glGetShaderInfoLog( vertex_shader, shader_log_length, NULL,
			                    shader_log );
			fprintf( stderr, "%s\n", shader_log );
			free( shader_log );
		}
		glDeleteShader( vertex_shader );
		return 0;
	}

	// Quick reset.
	success = 0;
	shader_log_length = 0;

	// And we repeat the same process. Should really make a seperate function
	// for this...
	uint32_t fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );

	if ( fragment_shader == 0 ) {
		fprintf( stderr, "OpenGL failed to create a fragment shader.\n" );
		return 0;
	}

	glShaderSource( fragment_shader, 1, &fragment_shader_source, NULL );
	glCompileShader( fragment_shader );
	glGetShaderiv( fragment_shader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		fprintf( stderr, "Fragment shader failed to compile.\n" );
		glGetShaderiv( fragment_shader, GL_INFO_LOG_LENGTH,
		               &shader_log_length );
		shader_log = calloc( shader_log_length, sizeof( char ) );
		if ( shader_log == NULL ) {
			fprintf(
			    stderr,
			    "An error log couldn't be formed due to a memory error.\n" );
		} else {
			glGetShaderInfoLog( fragment_shader, shader_log_length, NULL,
			                    shader_log );
			fprintf( stderr, "%s\n", shader_log );
			free( shader_log );
		}
		glDeleteShader( vertex_shader );
		glDeleteShader( fragment_shader );
		return 0;
	}

	uint32_t shader_program = glCreateProgram( );
	if ( shader_program == 0 ) {
		fprintf( stderr, "OpenGL failed to create a shader program.\n" );
		return 0;
	}

	glAttachShader( shader_program, vertex_shader );
	glAttachShader( shader_program, fragment_shader );
	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );

	glLinkProgram( shader_program );
	glGetProgramiv( shader_program, GL_LINK_STATUS, &success );
	if ( !success ) {
		fprintf( stderr, "Shader program failed to link.\n" );
		glGetProgramiv( shader_program, GL_INFO_LOG_LENGTH,
		                &shader_log_length );
		shader_log = calloc( shader_log_length, sizeof( char ) );
		if ( shader_log == NULL ) {
			fprintf(
			    stderr,
			    "An error log couldn't be formed due to a memory error.\n" );
		} else {
			glGetProgramInfoLog( shader_program, shader_log_length, NULL,
			                     shader_log );
			fprintf( stderr, "%s\n", shader_log );
			free( shader_log );
		}
		return 0;
	}

	return shader_program;
}