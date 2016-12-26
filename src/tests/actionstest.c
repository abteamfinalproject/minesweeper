/*
 * Game actions test unit
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include <stdlib.h>
#include <stdio.h>
#include "../grid.h"
#include "../actions.h"

#define ROWS 10
#define COLS 10

int main()
{
    char action;
    Cell testgrid[ROWS][COLS];
    Position move;

    prepareGrid(ROWS, COLS, testgrid);
    printGrid(ROWS, COLS, testgrid, "", 0);

    printf("First Move: ");
    scanf("%d%d", &move.x, &move.y);

    initGrid(move, ROWS, COLS, testgrid); // Populate grid with mines. Avoid first move position
    printGrid(ROWS, COLS, testgrid, "grid.txt", 1); // Log generated grid (for debugging)
    openCell(ROWS, COLS, testgrid, move);
    printGrid(ROWS, COLS, testgrid, "", 0); // Log generated grid

    while(1)
    {
        printf("\nPosition: ");
        scanf("%d%d", &move.x, &move.y);
        if(move.x < 0 || move.x >= ROWS || move.y < 0 || move.y >= COLS)
            break;
        printf("Action ([O]pen, [F]lag, [M]ark, [U]nmark): ");
        scanf(" %c", &action);
        if(action == 'O' || action == 'o')
            openCell(ROWS, COLS, testgrid, move);
        else if(action == 'F' || action == 'f')
            flagCell(ROWS, COLS, testgrid, move);
        else if(action == 'M' || action == 'm')
            markCell(ROWS, COLS, testgrid, move);
        else if(action == 'U' || action == 'u')
            unmarkCell(ROWS, COLS, testgrid, move);
        else
            break;
        printf("\n\nGrid:\n");
        printGrid(ROWS, COLS, testgrid, "", 0); // Log generated grid
    }

    return 0;
}
