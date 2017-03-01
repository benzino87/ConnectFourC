/**
 * Author: Jason Bensel
 *
 * Description: Main game loop, delegates incoming parameters to arg handler and
 *              main game logic to game handler.
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
  int currentPlayer;
  //Save buffer
  char* buffer = NULL;

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
    if(read_file(args.load_file, &buffer) == -1){
      printf("Error reading filename");
    }else{
      for(int i = 0; i < )
    }

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

    //Read user input
    fgets(input, 10, stdin);
    if(atoi(input) > args.width){
      printf("Too large, enter a number from 0 to %d..\n", args.width);
    }
    //Check for save
    if(strncmp(input, "save", 10) > 0){
      //Convert grid to to a save buffer
      convertForSave(gameboard, buffer, args.height, args.width);
      write_file("gamesave", buffer, buffsize);
      printf("GAME SAVED!\n");
      break;
    }
    //Check for valid move
    if((row = playerMove(gameboard, args.height, args.width, atoi(input), currentPlayer)) >= 0){
      int vertWin, horzWin, diagWin;

      //Check player win status
      vertWin = checkWinVertical(gameboard, args.height, args.width, args.connect,
                          row, atoi(input), currentPlayer);

      horzWin = checkWinHorizontal(gameboard, args.height, args.width, args.connect,
                            row, atoi(input), currentPlayer);


      diagWin = checkWinDiag(gameboard, args.height, args.width, args.connect,
                            row, atoi(input), currentPlayer);

      if(vertWin == currentPlayer || horzWin == currentPlayer || diagWin == currentPlayer){
          printGameboard(gameboard, args.height, args.width);
          printf("PLAYER %d WINS!!!\n\n", currentPlayer);
          break;
      }else{
        //Change player and continue playing
        currentPlayer = alternatePlayer(currentPlayer);
      }
    }
    printGameboard(gameboard, args.height, args.width);

  }
  return 0;
}
