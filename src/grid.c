/*
 * Grid Initialization
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

Position getRandomPos(int m, int n)
{
    Position pos = {rand()%m, rand()%n}; // Position = {random(0 to m-1), random(0 to n-1)}
    return pos;
}

char positionsEqual(Position a, Position b)
{
    return (a.x == b.x && a.y == b.y) ? 1 : 0;
}

char arrayContains(Position *arr, int arrsize, Position key)
{
    for(int i=0; i<arrsize; ++i)
    {
        if(positionsEqual(arr[i], key))
            return 1;
    }

    return 0;
}

void prepareGrid(int m, int n, Cell grid[m][n])
{
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            grid[i][j].status = CELL_CLOSED;
            grid[i][j].type = EMPTY_CELL;
        }
    }
}

void initGrid(Position firstPos, int m, int n, Cell grid[m][n])
{
    srand(time(NULL));
    int numMines = 1 + (m*n)/10;
    int usedPositionCount = 0; // Number of positions already filled with mines
    Position usedPositions[numMines]; // Coordinates of positions already filled with mines
    Position current; // Current random position
    char alreadyUsed; // Flag

    // Populate grid with mines as long as we haven't reached the target number of mines yet
    while(usedPositionCount < numMines)
    {
        // Get a random unused position
        do
        {
            current = getRandomPos(m, n);
            alreadyUsed = 0;

            // Avoid filling the first cell the user chooses with a mine
            if(positionsEqual(firstPos, current))
                alreadyUsed = 1;
            else // Make sure position isn't already filled with a mine
            {
                alreadyUsed = arrayContains(usedPositions, usedPositionCount, current);
            }
        }
        while(alreadyUsed);

        // Fill chosen position with mine
        grid[current.x][current.y].type = MINE_CELL;

        // Mark position as used (by adding it to usedPositions)
        usedPositions[usedPositionCount++] = current;

        // Increment adjacent cell values
        Position topLeft = {current.x-1, current.y-1};
        Position bottomRight = {current.x+1, current.y+1};

        for(int i=topLeft.x; i<=bottomRight.x; ++i)
        {
            for(int j=topLeft.y; j<=bottomRight.y; ++j)
            {
                // (i) and (j) within grid boundaries?
                if(i>=0 && i<m && j>=0 && j<n)
                {
                    if(grid[i][j].type != MINE_CELL)
                    {
                        ++grid[i][j].type;
                    }
                }
            }
        }
    }
}

void printGrid(int m, int n, Cell grid[m][n], char *filename, char debug)
{
    FILE *gridFile;

    if(strlen(filename))
    {
        gridFile = fopen(filename, "w");
    }
    else
    {
        gridFile = stdout;
    }

    if(gridFile != NULL) // Successfully opened file
    {
        // Header with column numbers
        fprintf(gridFile, "   ");
        for(int i=0; i<n; ++i)
            fprintf(gridFile, " %02d", i);
        fprintf(gridFile, "\n    ");
        for(int i=0; i<n; ++i)
            fprintf(gridFile, "-- ");
        fprintf(gridFile, "\n");

        if(debug) // Debugging mode? Print all cells open
        {
            for(int i=0; i<m; ++i)
            {
                fprintf(gridFile, "%02d  ", i); // Row number
                for(int j=0; j<n; ++j)
                {
                    fprintf(gridFile, " %c ", grid[i][j].type);
                }
                fprintf(gridFile, "\n");
            }
        }
        else
        {
            char cellVal; // Value to be printed for cell
            for(int i=0; i<m; ++i)
            {
                fprintf(gridFile, "%02d  ", i); // Row number
                for(int j=0; j<n; ++j)
                {
                    if(grid[i][j].status == CELL_CLOSED) // Closed
                    {
                        fprintf(gridFile, " %c ", CLOSED_CELL_CHAR);
                    }
                    else if(grid[i][j].status == CELL_FLAGGED)
                    {
                        fprintf(gridFile, " %c ", FLAGGED_CELL_CHAR);
                    }
                    else if(grid[i][j].status == CELL_MARKED)
                    {
                        fprintf(gridFile, " %c ", MARKED_CELL_CHAR);
                    }
                    else // If open
                    {
                        cellVal = grid[i][j].type;
                        fprintf(gridFile, " %c ",
                                (cellVal == EMPTY_CELL || cellVal == EMPTY_VISITED_CELL) ? EMPTY_CELL_CHAR : cellVal);
                    }
                }
                fprintf(gridFile, "\n");
            }
        }

        if(gridFile != stdout)
        {
            fclose(gridFile);
        }
    }
}
