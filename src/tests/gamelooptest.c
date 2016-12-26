/*
 * Game actions test unit
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include <stdlib.h>
#include <stdio.h>
#include "../grid.h"
#include "../gameloop.h"

#define ROWS 10
#define COLS 10

int main()
{
    Cell testgrid[ROWS][COLS];
    Position move;
    prepareGrid(ROWS, COLS, testgrid);
    char result = startGame(ROWS, COLS, testgrid, 0, 0);
	switch(result)
	{
		case PLAYER_WON:
			printf("PLAYER_WON\n");
			break;
		case PLAYER_LOST:
			printf("PLAYER_LOST\n");
			break;
		case SAVE_AND_EXIT:
			printf("SAVE_AND_EXIT\n");
			break;
		case EXIT_NO_SAVE:
			printf("EXIT_NO_SAVE\n");
			break;
		default:
			printf("Unknown error code returned!\n");
	}

    return 0;
} 
