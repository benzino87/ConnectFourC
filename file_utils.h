/**
 *
 * AUTHOR: Jason Bensel
 * DESCRIPTION: CIS 343 Structure of Programming languages Project 1
 * DATE: 1/29/2017
 *
 * FILE_UTILS.H
 *
 * Header file that includes function signatures for reading and writing files.
 *
 */
#ifndef file_utils_h_
#define file_utils_h_
#endif

/**
 *
 * Reads file with given file name and buffer size
 *
 * @param *filename: pointer to desired file to be loaded
 *
 * @param **buffer: pointer to character in buffer
 *
 */
int read_file( char* filename, char **buffer );

/**
 *
 * Writes a file with given file name
 *
 * @param *filename: pointer to desired name of file
 *
 * @param *bufer: pointer to start of characters in buffer
 *
 * @param *size: size of file
 *
 */
int write_file( char* filename, char *buffer, int size);
