#include "handle_arguments.h"
#include "game_handler.h"
#include "file_utils.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define playerOne 1
#define playerTwo 2

int main(int argc, char** argv){

  //Create our arguments structure
  struct arguments args;
  //User input
  char* input = malloc(sizeof(char)*10);
  //Current player
  int currentPlayer;
  //Save buffer
  char* buffer;

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


  if(args.load_file != NULL){
    load_file(args.load_file, buffer);

  }
  int buffsize = args.height*args.width+args.height-2;
  buffer = malloc(sizeof(char)*buffsize);
  //Initialize gameboard
  char** gameboard;
  gameboard = initializeGameboard(args.height, args.width);
  printGameboard(gameboard, args.height, args.width);


  currentPlayer = 1;
  int row;
  printf("READY TO PLAY!!\n\n");
  //Start game
  while(strncmp(input, "quit", 10) < 0 ){
    printf("CURRENT PLAYER: %d\n", currentPlayer);
    printf("Enter column:");

    fgets(input, 10, stdin);
    if(atoi(input) > args.width){
      printf("Too large, enter a number from 0 to %d..\n", args.width);
    }
    if(strncmp(input, "save", 10) > 0){
      convertForSave(gameboard, buffer, args.height, args.width);
      write_file("gamesave", buffer, buffsize);
      printf("GAME SAVED!\n");
      break;
    }
    if((row = playerMove(gameboard, args.height, atoi(input), currentPlayer)) >= 0){
      if(checkWin(gameboard, args.height, args.width, args.connect,
                          row, atoi(input), currentPlayer) == -1){
        currentPlayer = alternatePlayer(currentPlayer);
      }else{
        printGameboard(gameboard, args.height, args.width);
        printf("PLAYER %d WINS!!!\n\n", currentPlayer);
        break;
      }
    }
    printGameboard(gameboard, args.height, args.width);

  }
  return 0;
}
