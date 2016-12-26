/*
 * Saving Game
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "saving.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

char saveGame(int m, int n, Cell grid[m][n], int timePassed, int movesDone, char *fileName)
{
    FILE *file = fopen(fileName, "wb");
    if(!file) // Failed to open file
        return 1;
    // Else...
    char *abms = "ABMS";
    fwrite(abms, sizeof(char), 4, file);
    fwrite(&timePassed, sizeof(int), 1, file);
    fwrite(&movesDone, sizeof(int), 1, file);
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&n, sizeof(int), 1, file);
    fwrite(grid, sizeof(Cell), m*n, file);
    fclose(file);
    return 0;
}

char loadGame_info(int *m, int *n, int *timePassed, int *movesDone, char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if(!file) // Failed to open file
        return 1;
    // Else...
    fseek(file, sizeof(char)*4, SEEK_SET); // Skip starting 4 bytes ("ABMS")
    fread(timePassed, sizeof(int), 1, file);
    fread(movesDone, sizeof(int), 1, file);
    fread(m, sizeof(int), 1, file);
    fread(n, sizeof(int), 1, file);
    fclose(file);
    return 0;
}

char loadGame_grid(int m, int n, Cell grid[m][n], char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if(!file) // Failed to open file
        return 1;
    // Else...
    // Skip info
    fseek(file, sizeof(char)*4, SEEK_SET); // "ABMS"
    fseek(file, sizeof(int), SEEK_CUR); // Time passed
    fseek(file, sizeof(int), SEEK_CUR); // Moves done
    fseek(file, sizeof(int), SEEK_CUR); // Rows
    fseek(file, sizeof(int), SEEK_CUR); // Columns
    // Read grid
    fread(grid, sizeof(Cell), m*n, file);
    fclose(file);
    // Log grid to file for debugging
    printGrid(m, n, grid, GRID_FILE, 1);
    return 0;
}
