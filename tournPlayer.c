#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tournPlayer.h"
#include "battleship.h"

#define HORIZ 0
#define VERT 1

#define RAND 2
#define TARGET 3

#define UP 4
#define DOWN 5
#define LEFT 6
#define RIGHT 7

#define UNSHOT 8
#define LIKELY 9
#define SHOT 10

void usageExit()
{
   fprintf(stderr, "Usage: player readFD writeFD\n");
   exit(EXIT_FAILURE);
}
void checkArgs(int *readFD, int *writeFD, int argNum, char *args[])
{
   if(argNum != 3)
      usageExit();
   else
   {
      if(sscanf(args[1], "%d", readFD) != 1 || 
         sscanf(args[2], "%d", writeFD) != 1)
         usageExit();
   }
}
int hasShip(int startRow, int startCol, int size, int direc, 
   char board[SIZE][SIZE])
{
   int i;
   /* Based on direction, check all cells of desired placement for a conflicting ship */
   if(direc == HORIZ)
   {
      for(i = 0; i < size; i++)
      {
         if(board[startRow][startCol+i] != OPEN_WATER)
            return 1;
      }
   }
   else if(direc == VERT)
   {
      for(i = 0; i < size; i++)
      {
         if(board[startRow+i][startCol] != OPEN_WATER)
            return 1;
      }
   }
   return 0;
}
void placePB(char board[SIZE][SIZE])
{
   int startRow, startCol, i, direc;
   /* Pick a random direction, horizontal or vertical */
   direc = rand() % 2;
   if(direc == HORIZ)
   {
      /* Pick a random row and column */
      startRow = rand() % 10;
      startCol = rand() % 9;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_PATROL_BOAT, direc, board))
      {
         for(i = 0; i < SIZE_PATROL_BOAT; i++)
            board[startRow][startCol+i] = PATROL_BOAT;
      }
      /* Otherwise, try to place again */
      else
         placePB(board);
   }
   else if(direc == VERT)
   {
      /* Pick a random row and column */
      startRow = rand() % 9;
      startCol = rand() % 10;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_PATROL_BOAT, direc, board))
      {
         for(i = 0; i < SIZE_PATROL_BOAT; i++)
            board[startRow+i][startCol] = PATROL_BOAT;
      }
      /* Otherwise, try to place again */
      else
         placePB(board);
   }
}
void placeSub(char board[SIZE][SIZE])
{
   int startRow, startCol, i, direc;
   /* Pick a random direction, horizontal or vertical */
   direc = rand() % 2;
   if(direc == HORIZ)
   {
      /* Pick a random row and column */
      startRow = rand() % 10;
      startCol = rand() % 8;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_SUBMARINE, direc, board))
      {
         for(i = 0; i < SIZE_SUBMARINE; i++)
            board[startRow][startCol+i] = SUBMARINE;
      }
      /* Otherwise, try to place again */
      else
         placeSub(board);
   }
   else if(direc == VERT)
   {
      /* Pick a random row and column */
      startRow = rand() % 8;
      startCol = rand() % 10;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_SUBMARINE, direc, board))
      {
         for(i = 0; i < SIZE_SUBMARINE; i++)
            board[startRow+i][startCol] = SUBMARINE;
      }
      /* Otherwise, try to place again */
      else
         placeSub(board);
   }
}
void placeDes(char board[SIZE][SIZE])
{
   int startRow, startCol, i, direc;
   /* Pick a random direction, horizontal or vertical */
   direc = rand() % 2;
   if(direc == HORIZ)
   {
      /* Pick a random row and column */
      startRow = rand() % 10;
      startCol = rand() % 8;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_DESTROYER, direc, board))
      {
         for(i = 0; i < SIZE_DESTROYER; i++)
            board[startRow][startCol+i] = DESTROYER;
      }
      /* Otherwise, try to place again */
      else
         placeDes(board);
   }
   else if(direc == VERT)
   {
      /* Pick a random row and column */
      startRow = rand() % 8;
      startCol = rand() % 10;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_DESTROYER, direc, board))
      {
         for(i = 0; i < SIZE_DESTROYER; i++)
            board[startRow+i][startCol] = DESTROYER;
      }
      /* Otherwise, try to place again */
      else
         placeDes(board);
   }
}
void placeBatt(char board[SIZE][SIZE])
{
   int startRow, startCol, i, direc;
   /* Pick a random direction, horizontal or vertical */
   direc = rand() % 2;
   if(direc == HORIZ)
   {
      /* Pick a random row and column */
      startRow = rand() % 10;
      startCol = rand() % 7;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_BATTLESHIP, direc, board))
      {
         for(i = 0; i < SIZE_BATTLESHIP; i++)
            board[startRow][startCol+i] = BATTLESHIP;
      }
      /* Otherwise, try to place again */
      else
         placeBatt(board);
   }
   else if(direc == VERT)
   {
      /* Pick a random row and column */
      startRow = rand() % 7;
      startCol = rand() % 10;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_BATTLESHIP, direc, board))
      {
         for(i = 0; i < SIZE_BATTLESHIP; i++)
            board[startRow+i][startCol] = BATTLESHIP;
      }
      /* Otherwise, try to place again */
      else
         placeBatt(board);
   }
}
void placeAC(char board[SIZE][SIZE])
{
   int startRow, startCol, i, direc;
   /* Pick a random direction, horizontal or vertical */
   direc = rand() % 2;
   if(direc == HORIZ)
   {
      /* Pick a random row and column */
      startRow = rand() % 10;
      startCol = rand() % 6;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_AIRCRAFT_CARRIER, direc, board))
      {
         for(i = 0; i < SIZE_AIRCRAFT_CARRIER; i++)
            board[startRow][startCol+i] = AIRCRAFT_CARRIER;
      }
      /* Otherwise, try to place again */
      else
         placeAC(board);
   }
   else if(direc == VERT)
   {
      /* Pick a random row and column */
      startRow = rand() % 6;
      startCol = rand() % 10;
      /* If there isn't a conflicting boat, place it on the board */
      if(!hasShip(startRow, startCol, SIZE_AIRCRAFT_CARRIER, direc, board))
      {
         for(i = 0; i < SIZE_AIRCRAFT_CARRIER; i++)
            board[startRow+i][startCol] = AIRCRAFT_CARRIER;
      }
      /* Otherwise, try to place again */
      else
         placeAC(board);
   }
}
void buildGame(char board[SIZE][SIZE], int writeFD)
{
   int i, j;
   /* Set every cell on the board to open water */
   for(i = 0; i < SIZE; i++)
   {
      for(j = 0; j < SIZE; j++)
         board[i][j] = OPEN_WATER;
   }
   /* Place all player ships on the board and send to opponent */
   placePB(board);
   placeSub(board);
   placeDes(board);
   placeBatt(board);
   placeAC(board);
   write(writeFD, board, SIZE*SIZE);
}
int hasCellsLeft(Cell *toShoot[50])
{
   int i;
   /* Loop to see if there are random cells left to shoot */
   for(i = 0; i < 50; i++)
   {
      if(toShoot[i]->beenShot == UNSHOT)
         return 1;
   }
   return 0;
}
void shootRemain(Shot *currShot, int writeFD, int checker[SIZE][SIZE])
{
   int i, j;
   for(i = 0;i<SIZE;i++)
   {
      for(j=0;j<SIZE;j++)
      {
         /* Look for a cell marked as a likely target and shoot it*/
         if(checker[i][j] == LIKELY)
         {
            currShot->row = i;
            currShot->col = j;
            checker[i][j] = 1;
            write(writeFD, currShot, sizeof(*currShot));
            return;
         }
      }
   }
}
void sendRandShot(Shot *currShot, int writeFD, Cell *toShoot[50], 
   int checker[SIZE][SIZE])
{
   /* Choose a random shot from the chosen cells to shoot (checkered pattern) */
   int index = rand() % 50;
   /* If the chosen cell hasn't been shot */
   if(toShoot[index]->beenShot == UNSHOT)
   {
      /* Set the current shot and update cell information */
      currShot->row = toShoot[index]->row;
      currShot->col = toShoot[index]->col;
      toShoot[index]->beenShot = SHOT;
      checker[toShoot[index]->row][toShoot[index]->col] = SHOT;
      /* Send move to the opponent */
      write(writeFD, currShot, sizeof(*currShot));
   }
   /* If there are random cells left to shoot, send another random shot */
   else if(hasCellsLeft(toShoot) == SHOT)
      sendRandShot(currShot, writeFD, toShoot, checker);
   /* Otherwise, cells marked as possible targets */
   else
      shootRemain(currShot, writeFD, checker);
}
void setBeenShot(int row, int col, Cell *toShoot[50])
{
   int i;
   for(i = 0; i < 50; i++)
   {
      if(toShoot[i]->row == row && toShoot[i]->col == col)
      {
         toShoot[i]->beenShot = SHOT;
         break;
      }
   }
}
int targetShip(Shot *currShot, int writeFD, Cell *toShoot[50], 
   int checker[SIZE][SIZE], int *direc)
{
   int lastRow = currShot->row, lastCol = currShot->col;
   /* Based on direction, check the next adjacent cell and shoot it if it hasn't been yet */
   if(*direc == UP)
   {
      if(lastRow != 0)
      {
         (currShot->row)--;
         if(checker[currShot->row][currShot->col] != SHOT)
         {
            checker[currShot->row][currShot->col] = SHOT;
            setBeenShot(currShot->row, currShot->col, (Cell **)toShoot);
            write(writeFD, currShot, sizeof(*currShot));
            return 0;
         }
         else
            return 1;
      }
      else
         return 1;
   }
   if(*direc == DOWN)
   {
      if(lastRow != 9)
      {
         (currShot->row)++;
         if(checker[currShot->row][currShot->col] != SHOT)
         {
            checker[currShot->row][currShot->col] = SHOT;
            setBeenShot(currShot->row, currShot->col, (Cell **)toShoot);
            write(writeFD, currShot, sizeof(*currShot));
            return 0;
         }
         else
            return 1;
      }
      else
         return 1;
   }
   if(*direc == LEFT)
   {
      if(lastCol != 0)
      {
         (currShot->col)--;
         if(checker[currShot->row][currShot->col] != SHOT)
         {
            checker[currShot->row][currShot->col] = SHOT;
            setBeenShot(currShot->row, currShot->col, (Cell **)toShoot);
            write(writeFD, currShot, sizeof(*currShot));
            return 0;
         }
         else
            return 1;
      }
      else
         return 1;
   }
   if(*direc == RIGHT)
   {
      if(lastCol != 9)
      {
         (currShot->col)++;
         if(checker[currShot->row][currShot->col] != SHOT)
         {
            checker[currShot->row][currShot->col] = SHOT;
            setBeenShot(currShot->row, currShot->col, (Cell **)toShoot);
            write(writeFD, currShot, sizeof(*currShot));
            return 0;
         }
         else
            return 1;
      }
      else
         return 1;
   }
   return 0;
}
void fillCheckArray(int checker[SIZE][SIZE])
{
   int i, j;
   for(i = 0; i < SIZE; i++)
   {
      for(j = 0; j < SIZE; j++)
         checker[i][j] = -1;
   }
}
void fillCellArray(Cell *toShoot[50])
{
   int i, currRow = 0, currCol = 0;
   for(i = 0; i < 50; i++)
   {
      toShoot[i] = malloc(sizeof(Cell));
      toShoot[i]->beenShot = UNSHOT;
      toShoot[i]->row = currRow;
      toShoot[i]->col = currCol;
      /* Place every other cell into array like a checkers board */
      currCol = currCol + 2;
      if(currCol > 9)
      {
         currRow++;
         if(currRow % 2 == 0)
            currCol = 0;
         else
            currCol = 1;
      }
   }
}
void freeCellArray(Cell *toShoot[50])
{
   int i;
   for(i = 0;i<50;i++)
      free(toShoot[i]);
}
void setAdj(Shot *currShot, int checker[SIZE][SIZE])
{
   /* set adjacent cells as likely targets following a hit or sink */
   if(currShot->row != 0)
   {
      if(checker[currShot->row-1][currShot->col] == -1)
         checker[currShot->row-1][currShot->col] = LIKELY;
   }
   if(currShot->row != 9)
   {
      if(checker[currShot->row+1][currShot->col] == -1)
         checker[currShot->row+1][currShot->col] = LIKELY;
   }
   if(currShot->col != 0)
   {
      if(checker[currShot->row][currShot->col-1] == -1)
         checker[currShot->row][currShot->col-1] = LIKELY;
   }
   if(currShot->col != 9)
   {
      if(checker[currShot->row][currShot->col+1] == -1)
         checker[currShot->row][currShot->col+1] = LIKELY;
   }
}
int main(int argc, char *argv[])
{
   int nextMove, readFD, writeFD, res, shotRes, firstHitRow, 
      firstHitCol, direc = UP, mode = RAND, checker[SIZE][SIZE];
   /* Game Board Array */
   char board[SIZE][SIZE];
   Shot currShot, oppShot;
   /* Array of spots to shoot at */
   Cell toShoot[50];
   if(toShoot == NULL)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   /* Set up checker array with all -1 */
   fillCheckArray(checker);
   /* Set up toShoot array with row and column of every other spot */
   fillCellArray((Cell **)&toShoot);
   /* Confirm that the program inputs are valid */
   checkArgs(&readFD, &writeFD, argc, argv);
   while(1)
   {
      /* Read in the opponent's next move */
      res = read(readFD, &nextMove, sizeof(nextMove));
      if(res == 0)
         break;
      /* Set up the game again if a new game is requested */
      if(nextMove == NEW_GAME)
      {
         /* mode starts as random */
         mode = RAND;
         freeCellArray((Cell **)&toShoot);
         fillCheckArray(checker);
         fillCellArray((Cell **)&toShoot);
         /* Place player's ships on the board and send the board to the opponent */
         buildGame(board, writeFD);
      }
      /* When the opponent requests the next move */
      else if(nextMove == SHOT_REQUEST)
      {
         /* Shoot at a random cell in checkered pattern if in random mode */
         if(mode == RAND)
            sendRandShot(&currShot, writeFD, (Cell **)&toShoot, checker);
         /* Shoot at adjacent cells if in target mode */
         else if(mode == TARGET)
         {
            /* Reset direction if all options have been done */
            if(direc > RIGHT)
               direc = UP;
            /* Target a specific ship by shooting at adjacent cells following a hit */
            while(targetShip(&currShot, writeFD, 
               (Cell **)&toShoot, checker, &direc) != 0)
            {
               currShot.row = firstHitRow;
               currShot.col = firstHitCol;
               direc++;
               /* If all directions have been tried */
               if(direc > RIGHT)
               {
                  /* Shoot at a random cell if any remain */
                  if(hasCellsLeft((Cell **)&toShoot) == 1)
                     sendRandShot(&currShot, writeFD, 
                        (Cell **)&toShoot, checker);
                  /* Otherwise, shoot at cells marked as likely targets */
                  else
                     shootRemain(&currShot, writeFD, checker);
               }
            }
         }
      }
      /* When the opponent sends back the results of a shot */
      else if(nextMove == SHOT_RESULT)
      {
         /* Read in the results */
         res = read(readFD, &shotRes, sizeof(shotRes));
         /* If the shot was a hit, set adjacent cells as likely targets and switch to target mode */
         if(shotRes == HIT)
         {
            setAdj(&currShot, checker);
            if(mode == RAND)
            {
               firstHitRow = currShot.row;
               firstHitCol = currShot.col;
               mode = TARGET;
               direc = UP;
            }
         }
         /* If the shot sunk a ship, set adjacent cells as likely targets and switch to random mode */
         else if(shotRes == SINK)
         {
            setAdj(&currShot, checker);
            mode = RAND;
         }
         /* If the shot was a miss, reset the current shot to the first cell that was a hit */
         else if(shotRes == MISS)
         {
            if(mode == TARGET)
            {
               currShot.row = firstHitRow;
               currShot.col = firstHitCol;
               direc++;
            }
         }
      }
      /* If the next move is an opponent's shot, read in the shot */
      else if(nextMove == OPPONENTS_SHOT)
         res = read(readFD, &oppShot, sizeof(oppShot));
   }
   return EXIT_SUCCESS;
}