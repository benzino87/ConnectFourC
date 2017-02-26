#include "game_handler.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define playerOne 1
#define playerTwo 2
#define TRUE 1
#define FALSE 0
#define EMPTY 'x'

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
void printGameboard(char** gameboard, int height, int width){
  for(int row = height-1; row >= 0; row--){
    for(int col = 0; col < width; col++){
      printf("%c", gameboard[row][col]);
    }
    printf("\n");
  }
}

int alternatePlayer(int currentPlayer){
  if(currentPlayer == playerOne){
    currentPlayer = playerTwo;
  }else{
    currentPlayer = playerOne;
  }

  return currentPlayer;
}

int playerMove(char** gameboard, int height, int pos, int currentPlayer){
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

int checkWin(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer){
  //Counter for vertical and horizontal wins
  int count = 0;

  //Counter for diagonal wins
  int countUpRight = 0;
  int countUpLeft = 0;

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

    //Reset count for horizontal check
    count = 0;

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



// void checkForWin(char** gameboard, int height, int width, int currentPlayer){
//    int verticalCount;
//    int previousVerticalRowIndex;
//    int previousVerticalColIndex;
//    int hasPreviousVertical = FALSE
//
//    int horizontalCount;
//    int previousHorizontalRowIndex;
//    int previousHorizontalColIndex;
//    int hasPreviousHorizontal = FALSE
//
//    int diagonalCount;
//    int previousDiagonalRowIndex;
//    int previousDiagonalColIndex;
//    int hasPreviousDiagonal = FALSE
//
//    for(int row = 0; row < height; row++){
//      for(int col = 0; col < width; col++){
//        if(gameboard[row][col] == currentPlayer+'0'){
//          verticalCount++;
//          horizontalCount++;
//          diagonalCount++;
//        }
//      }
//    }
// }
// void printGameboard(char** gameboard){
//
// }
//
// void playerOneMove(char** gameboard, int pos){
//
// }
//
// void plaeryTwoMove(char** gameboard){
//
// }
