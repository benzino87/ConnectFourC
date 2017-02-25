#include "game_handler.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void initializeGameboard(char*** gameboard, int height, int width){
  gameboard = malloc(sizeof(char*)*height);
  for(int i = 0; i < height; i++){
    gameboard[i] = malloc(sizeof(char)*width);
  }
  printf("Game board initialized...\n");

  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      gameboard[row][col] = "x";
    }
  }

  printGameboard(gameboard, height, width);


}
void printGameboard(char*** gameboard, int height, int width){
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      printf("%s", gameboard[row][col]);
    }
    printf("\n");
  }
}
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
