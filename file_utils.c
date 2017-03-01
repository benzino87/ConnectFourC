/**
 *
 * AUTHOR: Jason Bensel
 * DESCRIPTION: CIS 343 Structure of Programming languages Project 1
 * DATE: 1/29/2017
 *
 * FILE_UTILS.C
 *
 * Implementation of read and write file function signatures
 *
 */
#include "file_utils.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>


/**
 *
 * Reads file into memory with given file name and buffer size
 *
 * @param *filename: pointer to desired file to be loaded
 *
 * @param *buffer: pointer to char in buffer
 *
 * @return: returns an int value indicating size of file
 *
 */
int read_file( char* filename, char **buffer){
  //printf("filename: %s\n buffer: %p\n", filename, buffer);

  struct stat st;
  char *mode = "r";
  FILE *fptr;
  int fileSize;

  //Check for a valid file name and get file size
  if(stat(filename, &st) < 0){
    perror("Error");
    return -1;
  }

  //Open the file stream
  if((fptr = fopen(filename, mode)) == NULL){
    perror("Error opening file");
    return -1;
  }

  fileSize = st.st_size;
  //Allocate space for the incoming buffer
  *buffer = malloc(fileSize * sizeof(char));

  //Load file stream into file buffer
  if((fread(*buffer, fileSize, 1, fptr)) != 1){
    perror("Error filling buffer");
    return -1;
  }

  //Close the file stream
  fclose(fptr);

  return fileSize;
}

/**
 *
 * Writes file to given file name
 *
 * @param *filename: pointer to desired name of file
 *
 * @param *buffer: pointer to start of characters in buffer
 *
 * @param size: size of file
 *
 * @return: returns an int value indicating size of file
 *
 */
int write_file( char* filename, char *buffer, int size){

  FILE *fptr;
  char *mode = "w";

  //Open a file stream
  if((fptr = fopen(filename, mode)) == NULL){
    perror("Error opening file");
    return -1;
  }

  //Iterate through the buffer in reverse and write file
  int i;
  for(i = size; i >= 0; i--){
    fprintf(fptr, "%c", buffer[i]);
  }

  //Close the file stream
  fclose(fptr);

  return 0;
}
