#include "handle_arguments.h"
#include "game_handler.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define playerOne 1
#define playerTwo 2

int main(int argc, char** argv){

  if(argc < 2){
    perror("No arguments supplied");
    exit(1);
  }

  //Create our arguments structure
  struct arguments args;
  //User input
  char* input = malloc(sizeof(char)*10);
  //Current player
  int currentPlayer;
  //Handle arguments and place in our structure
  setup(argc, argv, &args);


  //Initialize gameboard
  char** gameboard;
  initializeGameboard(&gameboard, args.height, args.width);


  currentPlayer = playerOne;
  printf("READY TO PLAY\n\n");
  //Start game
  while(strncmp(input, "quit", 10) < 0 ){

    printf("CURRENT PLAYER: %d\n", currentPlayer);
    fgets(input, 10, stdin);
    if(atoi(input) > args.width){
      perror("Number is too large");
    }
    printf("%s", input);
    printf("%d", currentPlayer);

    //Alternate players
    if(currentPlayer == playerOne){
      currentPlayer = playerTwo;
    }else{
      currentPlayer = playerOne;
    }
  }

  printf("height:%d\n", args.height);
  printf("width:%d\n", args.width);
  printf("file:%s\n", args.load_file);
  return 0;
}
