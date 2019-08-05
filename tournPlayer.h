#include "battleship.h"
#ifndef TOURNPLAYER_H
#define TOURNPLAYER_H

typedef struct cell
{
   int row, col, beenShot;
} Cell;

void usageExit();
void checkArgs(int *readFD, int *writeFD, int argNum, char *args[]);
int hasShip(int startRow, int startCol, int size, int direc, char board[SIZE][SIZE]);
void placePB(char board[SIZE][SIZE]);
void placeSub(char board[SIZE][SIZE]);
void placeDes(char board[SIZE][SIZE]);
void placeBatt(char board[SIZE][SIZE]);
void placeAC(char board[SIZE][SIZE]);
void buildGame(char board[SIZE][SIZE], int writeFD);
int hasCellsLeft(Cell *toShoot[50]);
void shootRemain(Shot *currShot, int writeFD, int checker[SIZE][SIZE]);
void sendRandShot(Shot *currShot, int writeFD, Cell *toShoot[50], int checker[SIZE][SIZE]);
void setBeenShot(int row, int col, Cell *toShoot[50]);
int targetShip(Shot *currShot, int writeFD, Cell *toShoot[50], int checker[SIZE][SIZE], int *direc);
void fillCheckArray(int checker[SIZE][SIZE]);
void fillCellArray(Cell *toShoot[50]);
void freeCellArray(Cell *toShoot[50]);
void setAdj(Shot *currShot, int checker[SIZE][SIZE]);

#endif