/**
 * Author: Jason Bensel
 *
 * Description: Handles all game logic including creation of grid, printing
 *              grid, valid player moves, win status, conversions for file saves
 *              and loads.
 */

#include "game_handler.h"
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
//Boolean value
#define TRUE 1
//Boolean value
#define FALSE 0
//Grid status
#define EMPTY 'x'


/**
 * Takes arguments given by command line arguments and generates a gameboard
 *
 * @param (height): number of rows in the connect 4 grid
 *
 * @param (width): number of columns in the connect 4 grid
 *
 * @return: returns a newly created gameboard with given heighth and width
 */
char** initializeGameboard(int height, int width){
  char** gameboard;
  gameboard = malloc(sizeof(char*)*height);
  for(int i = 0; i < height; i++){
    gameboard[i] = malloc(sizeof(char)*width);
  }
  printf("Game board initialized...\n");

  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      gameboard[row][col] = 'x';
    }
  }
  return gameboard;

}

/**
 * Iterates through the game board and prints its current status for players
 * after every moves
 *
 * @param (gameboard): current game board
 *
 * @param (height): height of gameboard for iterations
 *
 * @param (width): width of gameboard for iterations
 */
void printGameboard(char** gameboard, int height, int width){
  for(int row = height-1; row >= 0; row--){
    for(int col = 0; col < width; col++){
      printf("%c", gameboard[row][col]);
    }
    printf("\n");
  }
}

/**
 * Changes player
 *
 * @param (currentPlayer): player who just completed a moves
 *
 * @return: value of next player
 */
int alternatePlayer(int currentPlayer){
  if(currentPlayer == playerOne){
    currentPlayer = playerTwo;
  }else{
    currentPlayer = playerOne;
  }

  return currentPlayer;
}

/**
 * Checks for a valid player move and returns the value of the row it was placed
 * into.
 *
 * @param (gameboard): Current gameboard
 *
 * @param (height): height of gameboard for row placement
 *
 * @param (width): width of gameboard for valid player move
 *
 * @param (pos): position entered by current player
 *
 * @param (currentPlayer): player who entered move
 *
 * @return: value of row the number was placed in
 */
int playerMove(char** gameboard, int height, int width, int pos, int currentPlayer){
  int rowPlaced = -1;
  for(int row = 0; row < height; row++){
    if(gameboard[row][pos] == EMPTY){
      gameboard[row][pos] = currentPlayer + '0';
      rowPlaced = row;
      break;
    }
    if(row == height-1 && gameboard[row][height] != EMPTY){
      printf("This row is filled\n");
      return -1;
    }
  }
  return rowPlaced;
}

/**
 * Checks for win if requirement for win status is met after players last move
 *
 * @param (gameboard): current gameboard
 *
 * @param (height): height of gameboard
 *
 * @param (width): width of gameboard
 *
 * @param (required): required number to win the game
 *
 * @param (row): value last row placed
 *
 * @param (col): value last col placed
 *
 * @param (currentPlayer): player who just played last move
 *
 * @return: returns current player if win requirement is met, otherwise returns
 *          -1 if no win is found
 */
int checkWinVertical(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer){
  //Counter for vertical and horizontal wins
  int count = 0;

  //Check for vertical win
  for(int pos = 0; pos < height; pos++){
    if(gameboard[pos][col] == currentPlayer+'0'){
      count++;
    }else{
      count = 0;
      }
      if(count == required){
        return currentPlayer;
      }
    }
  return -1;
}

/**
 * Checks for win if requirement for win status is met after players last move
 *
 * @param (gameboard): current gameboard
 *
 * @param (height): height of gameboard
 *
 * @param (width): width of gameboard
 *
 * @param (required): required number to win the game
 *
 * @param (row): value last row placed
 *
 * @param (col): value last col placed
 *
 * @param (currentPlayer): player who just played last move
 *
 * @return: returns current player if win requirement is met, otherwise returns
 *          -1 if no win is found
 */
int checkWinHorizontal(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer){
  //Reset count for horizontal check
  int count = 0;

  //Check for horizontal win
  for(int pos = 0; pos < width; pos++){
    if(gameboard[row][pos] == currentPlayer+'0'){
      count++;
    }else{
      count = 0;
    }
    if(count == required){
      return currentPlayer;
    }
  }
  return -1;
}

/**
 * Checks for win if requirement for win status is met after players last move
 *
 * @param (gameboard): current gameboard
 *
 * @param (height): height of gameboard
 *
 * @param (width): width of gameboard
 *
 * @param (required): required number to win the game
 *
 * @param (row): value last row placed
 *
 * @param (col): value last col placed
 *
 * @param (currentPlayer): player who just played last move
 *
 * @return: returns current player if win requirement is met, otherwise returns
 *          -1 if no win is found
 */
int checkWinDiag(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer){
  int countUpRight = 0;
  int countUpLeft = 0;

  //Check for up-right diagonal wins
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      for(int pos = 0; pos < required; pos++){
        //bounds checks up-right
        if(row+pos < height){
          if(col+pos < width){
            //perform up-right win search
            if(gameboard[row+pos][col+pos] == currentPlayer+'0'){
              countUpRight++;
            }else{
              countUpRight = 0;
            }
            if(countUpRight == required){
              return currentPlayer;
            }
          }
          if(col-pos > 0){
            //perform up-left win search
            if(gameboard[row+pos][col-pos] == currentPlayer+'0'){
              countUpLeft++;
            }else{
              countUpLeft = 0;
            }
            if(countUpLeft == required){
              return currentPlayer;
            }
          }
        }
      }
    }
  }
  return -1;
}

/**
 * Converts incoming gameboard to a single buffer pointer for file save
 *
 * @param (gameboard): current gameboard
 *
 * @param (buffer): buffer for gameboard to be saved to
 *
 * @param (height): height of gameboard
 *
 * @param (width): width of gameboard
 */
void convertForSave(char** gameboard, char* buffer, int height, int width){
   int count = 0;
   for(int row = 0; row < height; row++){
     for(int col = 0; col < width; col++){
       buffer[count] = gameboard[row][col];
       count++;
     }
     buffer[count] = '\n';
     count++;
   }
}
int getFileHeight(char* buffer){
  int pos = 0;
  int row = 0;

  while(buffer[pos] != '\0'){
    if(buffer[pos] == '\n'){
      row++;
    }
    pos++;
  }
  return row+1;
}
int getFileWidth(char* buffer){
  int pos = 0;
  int col = 0;

  while(buffer[pos] != '\n'){
    // if(buffer[pos] == '\0'){
    //   return col+1;
    // }
        col = pos;
        col++;
        pos++;
  }
  return col;
}
char** initializeFromLoad(char* buffer, int buffsize, int height, int width){
  char** gameboard;
  gameboard = malloc(sizeof(char*)*height);
  for(int i = 0; i < height; i++){
    gameboard[i] = malloc(sizeof(char)*width);
  }
  printf("Game board initialized...\n");
  printf("Loading gameboard...\n");
  int row = 0;

  for(int i = 0; i < buffsize; i++){
    if(buffer[i] == '\n'){
      row++;
    }
    gameboard[row][i] = buffer[i];
  }

  return gameboard;
}
