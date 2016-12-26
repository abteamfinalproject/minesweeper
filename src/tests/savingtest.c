/*
 * Saving test unit
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include <stdlib.h>
#include <stdio.h>
#include "../grid.h"
#include "../saving.h"

#define ROWS 10
#define COLS 10
#define FIRSTMOVE_X 0
#define FIRSTMOVE_Y 0
#define TIME_PASSED 120
#define MOVES_DONE 5
#define FILENAME "savedgame.dat"

int main()
{
	Cell grid[ROWS][COLS];
	Position move = {FIRSTMOVE_X, FIRSTMOVE_Y};
	int rows, cols, timepassed, movesdone;

	printf("Preparing and initializing grid...\n");
	prepareGrid(ROWS, COLS, grid);
	initGrid(move, ROWS, COLS, grid);

	printf("Saving game status with the following conditions:\n");
	printf("Rows: %d\tColumns: %d\nTime Passed: %d\tMoves Done: %d\n", ROWS, COLS, TIME_PASSED, MOVES_DONE);
	printf("Grid:\n");
	printGrid(ROWS, COLS, grid, "", 1);
	printf("\n");
	saveGame(ROWS, COLS, grid, TIME_PASSED, MOVES_DONE, FILENAME);

	printf("Loading game status (info)...\n");
	loadGame_info(&rows, &cols, &timepassed, &movesdone, FILENAME);
	printf("Loaded game status (info):\n");
	printf("Rows: %d\tColumns: %d\nTime Passed: %d\tMoves Done: %d\n", rows, cols, timepassed, movesdone);

	printf("Loading game status (grid)...\n");
	Cell loadedgrid[rows][cols];
	loadGame_grid(rows, cols, loadedgrid, FILENAME);
	printf("Loaded game status (grid):\n");
	printGrid(rows, cols, loadedgrid, "", 1);
	printf("\nThat's it...\nI hope it works! :D\n");

	return 0;
}
