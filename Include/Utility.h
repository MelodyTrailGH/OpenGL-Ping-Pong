/*
MIT License

Copyright (c) 2023 Anthony Jackson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef UTILITY_H
#define UTILITY_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NORMALIZE( value ) ( 1.0F / 255.0F ) * value

/**
 * @brief Gets the size of a file.
 *
 * @param path The file path.
 * @return uint64_t The size of the file in bytes.
 * @note You will get a size 0 if an error occurs.
 */
extern uint64_t getFileSize( const char *path );

/**
 * @brief Gets the size of a file descriptor.
 *
 * @param fd The file descriptor.
 * @return uint64_t The size of the descriptor in bytes.
 * @note You will get a size 0 if an error occurs.
 * @note The file descriptor will be set to its original position (the one prior
 * to reading it) after getting the size.
 */
extern uint64_t getFileDescSize( FILE *fd );

/**
 * @brief Reads any UTF-8 text from a file.
 *
 * @param path The path to the UTF-8 file.
 * @return const char* The context of the file.
 * @note You will get NULL if an error occurs.
 */
extern const char *readTextFile( const char *path );

/**
 * @brief Reads any UTF-8 text from a file descriptor.
 *
 * @param fd The UTF-8 file descriptor.
 * @return const char* The context of the descriptor.
 * @note You will get NULL if an error occurs.
 * @note The file descriptor will be set to its original position (the one prior
 * to reading it) after getting the data.
 */
extern const char *readTextFileDesc( FILE *fd );

extern const char *getApplicationDirectory( );

extern uint64_t text_length( const char *src );
extern char *text_copy( const char *src );
extern char *text_copy_length( const char *src, uint64_t length );

extern char *text_replace_char( const char *src, const char find,
                                const char repl );

extern char *text_format( char *fmt, ... );

uint32_t createShader( const char *vertex_shader_source,
                       const char *fragment_shader_source );
#endif // UTILITY_H