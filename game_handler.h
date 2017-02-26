#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

char** initializeGameboard(int height, int width);
void printGameboard(char** gameboard, int height, int width);
int alternatePlayer(int player);
int playerMove(char** gameboard, int height, int pos, int currentPlayer);
int checkWin(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer);
//void printGameboard(char** gameboard);
//void playerOneMove(char** gameboard);
//void plaeryTwoMove(char** gameboard);

#endif
