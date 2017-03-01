#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

char** initializeGameboard(int height, int width);
void printGameboard(char** gameboard, int height, int width);
int alternatePlayer(int player);
int playerMove(char** gameboard, int height, int width, int pos, int currentPlayer);
int checkWinHorizontal(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer);
int checkWinVertical(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer);
int checkWinDiag(char** gameboard, int height, int width, int required, int row, int col, int currentPlayer);
void convertForSave(char** gameboard, char* buffer, int height, int width);
char** initializeFromLoad(char* buffer, int buffsize, int height, int width);
int getFileHeight(char* buffer);
int getFileWidth(char* buffer);


#endif
