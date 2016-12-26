/*
 * Grid initialization test unit
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "../grid.h"

#define ROWS 10
#define COLS 10
#define FIRSTMOVE_X 2
#define FIRSTMOVE_Y 1

int main()
{
	Cell testgrid[ROWS][COLS];
	Position firstmove = {FIRSTMOVE_X, FIRSTMOVE_Y}; // First move made by user
	printf("Preparing grid...\n");
	prepareGrid(ROWS, COLS, testgrid);
	printf("Initializing grid with (%d, %d) as the first move...\n", FIRSTMOVE_X, FIRSTMOVE_Y);
	initGrid(firstmove, ROWS, COLS, testgrid); // Populate grid with mines. Avoid first move position.
	printf("Printing grid in debugging mode...\n");
	printGrid(ROWS, COLS, testgrid, "", 1); // Log generated grid
	printf("Printing grid in normal mode...\n");
	printGrid(ROWS, COLS, testgrid, "", 0);
	printf("\n");

	return 0;
}
