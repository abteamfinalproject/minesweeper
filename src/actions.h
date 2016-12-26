/*
 * Game Actions
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_ACTIONS_H__
#define __ABTEAM_ACTIONS_H__

#include "grid.h"

// Error codes for opening a cell
#define ALREADY_OPEN 1
#define TOUCHED_MINE 2
#define CELL_IS_FLAGGED 3
#define CELL_IS_MARKED 4

// Error codes for flagging or marking a cell
// ALREADY_OPEN: 1
#define ALREADY_FLAGGED 2
#define ALREADY_MARKED 3

// Error codes for unmarking a cell
#define FLAG_REMOVED 1
#define MARK_REMOVED 2
#define NOT_FLAGGED_NOR_MARKED 3

// Opens an empty cell and all adjacent empty cells recursively
void openEmpty(int m, int n, Cell grid[m][n], Position cellPos);

// Opens the cell at (cellPos)
char openCell(int m, int n, Cell grid[m][n], Position cellPos);

// Flags the cell at (cellPos)
char flagCell(int m, int n, Cell grid[m][n], Position cellPos);

// Marks the cell at (cellPos) with a question mark.
char markCell(int m, int n, Cell grid[m][n], Position cellPos);

// Unmarks the cell at (cellPos)
char unmarkCell(int m, int n, Cell grid[m][n], Position cellPos);

#endif
