/**
 * AUTHOR: Jason Bensel
 * DESCRIPTION: CIS 343 Structure of Programming languages Project 3
 * DATE: 3/3/2017
 *
 * Main game loop, delegates incoming parameters to arg handler and main game
 * logic to game handler.
 */

#include "handle_arguments.h"
#include "game_handler.h"
#include "file_utils.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Player one
#define playerOne 1
//Player two
#define playerTwo 2

int main(int argc, char** argv){

  //Create our arguments structure
  struct arguments args;
  //User input
  char* input = malloc(sizeof(char)*10);
  //Current player
  int currentPlayer = 1;
  //Save buffer
  char* buffer = NULL;
  //Gameboard
  char** gameboard;
  //Buffer size of loaded file
  int buffsize;


  printf("\n\n444444  444444  4     4   4     4  444444  444444  444444\n");
  printf("4       4    4  4 4   4   4 4   4  4       4          4\n");
  printf("4       4    4  4  4  4   4  4  4  444444  4          4\n");
  printf("4       4    4  4   4 4   4   4 4  4       4          4\n");
  printf("444444  444444  4    44   4    44  444444  444444     4\n\n");
  printf("                           4\n");
  printf("                          44\n");
  printf("                         4 4\n");
  printf("                        4  4\n");
  printf("                       4444444\n");
  printf("                           4\n");


  //If no arguments have default setup 7x7, 4 to win
  if(argc == 1){
    args.height = 7;
    args.width = 7;
    args.connect = 4;
    args.load_file = NULL;
  }else{
    //Handle arguments and place in our structure
    setup(argc, argv, &args);
  }
  //Handle each argument individually and prevent user from entering something
  //irrational
  if(args.height < 1){
    args.height = 7;
  }
  if(args.width < 1){
    args.width = 7;
  }
  if(args.connect < 1){
    args.connect = 4;
  }
  if(args.connect > args.height || args.connect > args.width){
    printf("Connections can't be greater than the dimensions of the board\n");
    exit(1);
  }

  //Check for valid file name
  if(args.load_file != NULL){
    if(read_file(args.load_file, &buffer) == -1){
      printf("Error reading filename\n");
      exit(1);
    }else{
      //Get file parameters
      args.height = getFileHeight(buffer);
      args.width = getFileWidth(buffer);
      buffsize = args.height*args.width-2;

      initializeFromLoad(&gameboard, buffer, buffsize, args.height, args.width);

      printGameboard(gameboard, args.height, args.width);

    }

  }

  //Create new gameboard if no prior game save requested
  if(args.load_file == NULL){
    //Allocate space for the save buffer
    buffsize = args.height*args.width+args.height-2;
    buffer = malloc(sizeof(char)*buffsize);

    //Initialize Gameboard
    initializeGameboard(&gameboard, args.height, args.width);
    printGameboard(gameboard, args.height, args.width);

    printf("                    READY TO PLAY!!\n\n");
  }

  //Start game loop
  while(strncmp(input, "quit", 10) < 0 ){
    printf("CURRENT PLAYER: %d\n", currentPlayer);
    printf("Enter column:");

    //Read user input
    fgets(input, 10, stdin);

    //Check for valid user input
    if(atoi(input) > args.width-1 || atoi(input) < 0){
      printf("*****Number entered is either too small or too large.******\n");
      printf("             Enter a number from 0 to %d..\n", args.width-1);

    }else{

      //Check for save
      if(strncmp(input, "save", 10) > 0){
        //Convert grid to to a save buffer
        convertForSave(gameboard, buffer, args.height, args.width);
        write_file("gamesave", buffer, buffsize);
        printf("*****GAME SAVED!*****\n");
        break;
      }

      //Play game as normal
      if(playGame(gameboard, args.height, args.width, args.connect, atoi(input), currentPlayer) == -1){
        currentPlayer = alternatePlayer(currentPlayer);
      }else{
        //Win found
        break;
      }

      //Prints gameboard for status update after every move
      printGameboard(gameboard, args.height, args.width);
    }

  }
  //Release memory
  free(buffer);
  free(gameboard);
  free(input);
  return 0;
}
