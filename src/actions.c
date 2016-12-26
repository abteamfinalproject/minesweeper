/*
 * Game Actions
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "actions.h"
#include "grid.h"
#include <stdlib.h>
#include <stdint.h>

void openEmpty(int m, int n, Cell grid[m][n], Position cellPos)
{
    Cell *current = &grid[cellPos.x][cellPos.y];
    current->status = CELL_OPEN;

    if(current->type == EMPTY_CELL) // Empty but NOT visited (some adjacent cells are not open yet)
    {
        // Mark cell as visited
        current->type = EMPTY_VISITED_CELL;

        // Open adjacent cells
        Position topLeft = {cellPos.x-1, cellPos.y-1};
        Position bottomRight = {cellPos.x+1, cellPos.y+1};
        Position currentPos;

        for(int i=topLeft.x; i<=bottomRight.x; ++i)
        {
            currentPos.x = i;
            for(int j=topLeft.y; j<=bottomRight.y; ++j)
            {
                currentPos.y = j;
                // (i) and (j) within grid boundaries?
                if(i>=0 && i<m && j>=0 && j<n)
                {
                    openEmpty(m, n, grid, currentPos);
                }
            }
        }
    }
}

char openCell(int m, int n, Cell grid[m][n], Position cellPos)
{
    Cell *current = &grid[cellPos.x][cellPos.y];

    if (current->status==CELL_FLAGGED)
    {
        return CELL_IS_FLAGGED;
    }

    else if (current->status==CELL_MARKED)
    {
        return CELL_IS_MARKED;
    }

    else if (current->status==CELL_OPEN)
    {
        // Count the number of flags in adjacent cells
        int numFlags = 0;
        Position topLeft = {cellPos.x-1, cellPos.y-1};
        Position bottomRight = {cellPos.x+1, cellPos.y+1};

        for(int i=topLeft.x; i<=bottomRight.x; ++i)
        {
            for(int j=topLeft.y; j<=bottomRight.y; ++j)
            {
                // (i) and (j) within grid boundaries?
                if(i>=0 && i<m && j>=0 && j<n)
                {
                    if(grid[i][j].status == CELL_FLAGGED)
                    {
                        ++numFlags;
                    }
                }
            }
        }

        // Number of flags equals cell value?
        if(numFlags == grid[cellPos.x][cellPos.y].type-48)
        {
            char foundMine = 0;
            char allAlreadyOpen = 1;
            // Open all adjacent cells which are not flagged
            Position topLeft = {cellPos.x-1, cellPos.y-1};
            Position bottomRight = {cellPos.x+1, cellPos.y+1};
            Position currentPos;

            for(int i=topLeft.x; i<=bottomRight.x; ++i)
            {
                currentPos.x = i;
                for(int j=topLeft.y; j<=bottomRight.y; ++j)
                {
                    currentPos.y = j;
                    // (i) and (j) within grid boundaries?
                    if(i>=0 && i<m && j>=0 && j<n)
                    {
                        if(grid[i][j].status == CELL_CLOSED)
                        {
                            allAlreadyOpen = 0;
                            if(openCell(m, n, grid, currentPos) == TOUCHED_MINE)
                            {
                                foundMine = 1;
                            }
                        }
                    }
                }
            }
            return foundMine ? TOUCHED_MINE : (allAlreadyOpen ?  ALREADY_OPEN : 0);
        }
        else // If number of flags not equal to cell value
        {
            return ALREADY_OPEN;
        }
    }

    current->status = CELL_OPEN;

    if (current->type==MINE_CELL)
    {
        current->type = LOSS_MINE;
        return TOUCHED_MINE;
    }
    else if(current->type==EMPTY_CELL)
    {
        openEmpty(m, n, grid, cellPos);
    }

    return 0;
}

char flagCell(int m, int n, Cell grid[m][n], Position cellPos)
{
    Cell *current = &grid[cellPos.x][cellPos.y];

    if (current->status==CELL_OPEN)
    {
        return ALREADY_OPEN;
    }
    else if (current->status==CELL_FLAGGED)
    {
        return ALREADY_FLAGGED;
    }
    else if (current->status==CELL_MARKED)
    {
        return ALREADY_MARKED;
    }

    current->status = CELL_FLAGGED ;
    return 0;
}

char markCell(int m, int n, Cell grid[m][n], Position cellPos)
{
    Cell *current = &grid[cellPos.x][cellPos.y];

    if (current->status==CELL_OPEN)
    {
        return ALREADY_OPEN;
    }
    else if (current->status==CELL_FLAGGED)
    {
        return ALREADY_FLAGGED;
    }
    else if (current->status==CELL_MARKED)
    {
        return ALREADY_MARKED;
    }

    current->status = CELL_MARKED;
    return 0;
}

char unmarkCell(int m, int n, Cell grid[m][n], Position cellPos)
{
    Cell *current = &grid[cellPos.x][cellPos.y];

    if(current->status == CELL_FLAGGED)
    {
        current->status = CELL_CLOSED;
        return FLAG_REMOVED;
    }
    else if(current->status == CELL_MARKED)
    {
        current->status = CELL_CLOSED;
        return MARK_REMOVED;
    }
    else
    {
        return NOT_FLAGGED_NOR_MARKED; // Cell is neither flagged nor marked with a question mark
    }
}
