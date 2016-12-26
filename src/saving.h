/*
 * Saving Game
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_SAVING_H__
#define __ABTEAM_SAVING_H__

#include "grid.h"

#define GRID_FILE "grid.txt"

// Saves the status and grid of the current game to a file
char saveGame(int m, int n, Cell grid[m][n], int timePassed, int movesDone, char *fileName);

// Loads the status of a previously saved game from a file into the variables pointed to by (m), (n), (timePassed), (movesDone).
char loadGame_info(int *m, int *n, int *timePassed, int *movesDone, char *fileName);

// Loads the grid of a previously saved game from a file, given that its dimensions are (m X n).
char loadGame_grid(int m, int n, Cell grid[m][n], char *fileName);



#endif
