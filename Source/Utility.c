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
#include <sys/_types/_va_list.h>

uint64_t getFileSize( const char *path ) {
	FILE *file = fopen( path, "rb" );
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
	FILE *file = fopen( path, "r" );
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
	char *dir = calloc( dir_len, sizeof( char ) );
	strlcpy( dir, path, dir_len + 1 );
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