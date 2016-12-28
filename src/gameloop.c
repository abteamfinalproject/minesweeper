/*
 * Game Loop
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "gameloop.h"
#include "input.h"
#include "grid.h"
#include "actions.h"
#include "saving.h"
#include "scores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h> // for tolower
#include <poll.h> // for stdin polling

#define GAME_IN_PROGRESS -1

int calculateScore(int m, int n, int timePassed, int movesDone)
{
    long long score;
    if(!timePassed || !movesDone)
        score = 0;
    else
        score = ((pow(m,4))*(pow(n,4)))/(timePassed*movesDone);
    return score;
}

void printHeader(int timePassed, int movesDone, int flagged, int marked, long long score)
{
    printf("Time: %ds\tMoves: %d\tFlagged: %d\tMarked: %d\tScore: %lld\n", timePassed, movesDone, flagged, marked, score);

}

void getMove(int m, int n, Position *pos)
{
    char buffer[8];
    char valid;
    do
    {
        valid = 1;
        printf("Position ([X][SPACE][Y]): ");
        getstring(8, buffer);

        // Make sure input contains only digits
        for(int i=0; buffer[i]; ++i)
        {
            if(!isdigit(buffer[i]) && !isspace(buffer[i]))
            {
                valid = 0;
                break;
            }
        }

        // Parse input
        if(sscanf(buffer, "%d %d", &pos->x, &pos->y) != 2)
        {
            valid = 0;
        }
        else if(pos->x < 0 || pos->x >= m || pos->y < 0 || pos->y >= n)
        {
            valid = 0;
        }

        if(!valid)
            printf("Please enter a valid position!\n");
    } while(!valid);
}

char hasWon(int m, int n, Cell grid[m][n])
{
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            // Found a non-mine closed cell? Hasn't won yet then...
            if(grid[i][j].type != MINE_CELL && grid[i][j].status == CELL_CLOSED)
            {
                return 0;
            }
        }
    }

    return 1;
}

char startGame(int m, int n, Cell grid[m][n], int timePassed, int movesDone)
{
    // Input polling variables
    struct pollfd pfd;
    pfd.fd = 0; // File descriptor for stdin
    pfd.events = POLLIN; // There is data to read
    // End of input polling variables

    char end = GAME_IN_PROGRESS;
    Position move;
    char action;
    char result;
    int flaggedCells = 0, markedCells = 0, score;
    time_t start;
    // First move?
    if(movesDone == 0)
    {
        printGrid(m, n, grid, "", 0);
        printf("\n");
        // Get first move
        printf("Your first move:\n");
        getMove(m, n, &move);
        initGrid(move, m, n, grid);
        // Log grid to file for debugging
        printGrid(m, n, grid, GRID_FILE, 1);
        openCell(m, n, grid, move);
        ++movesDone;
        start = time(NULL); // Start counting time after first move
        if(hasWon(m, n, grid)) // Won after first move? ;)
        {
            end = PLAYER_WON;
            ++timePassed; // On first move time will be 0, so add one second for proper score calculation
        }
    }

    else // Game loaded from file? Count flags and question marks
    {
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j].status == CELL_FLAGGED)
                    ++flaggedCells;
                else if(grid[i][j].status == CELL_MARKED)
                    ++markedCells;
            }
        }
        start = time(NULL)-timePassed;
    }

    score = calculateScore(m, n, timePassed, movesDone);
    // Enter game loop
    while(end == GAME_IN_PROGRESS)
    {
        system(CLR_SCR);
        printHeader(timePassed, movesDone, flaggedCells, markedCells, score);
        printf("\n");
        printGrid(m, n, grid, "", 0);
        printf("\n");
        // Prompt user for action
        printf("\t[O]pen Cell\n");
        printf("\t[F]lag Cell\n");
        printf("\t[M]ark Cell\n");
        printf("\t[U]nmark Cell\n");
        printf("\t[S]ave & Quit Game\n");
        printf("\t[Q]uit Game\n");
        printf("Action: ");

        if(poll(&pfd, 1, 6oe3)) // Poll stdin for 60 seconds
        {
            action = ab_getchar();
            action = tolower(action);
            switch(action)
            {
            case 'o':
                getMove(m, n, &move);
                result = openCell(m, n, grid, move);
                if(result == ALREADY_OPEN)
                {
                    printf("The cell is already open!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == CELL_IS_FLAGGED)
                {
                    printf("The cell is flagged!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == CELL_IS_MARKED)
                {
                    printf("The cell is marked!");
                    flushstdin(); // Wait for ENTER
                }
                else
                {
                    ++movesDone;
                    // Check for winning or loss
                    if(result == TOUCHED_MINE)
                    {
                        end = PLAYER_LOST;
                    }
                    else if(hasWon(m, n, grid))
                    {
                        end = PLAYER_WON;
                    }
                }
                break;
            case 'f':
                getMove(m, n, &move);
                result = flagCell(m, n, grid, move);
                if(result == ALREADY_OPEN)
                {
                    printf("The cell is already open!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == ALREADY_FLAGGED)
                {
                    printf("The cell is already flagged!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == ALREADY_MARKED)
                {
                    printf("The cell is already marked!");
                    flushstdin(); // Wait for ENTER
                }
                else
                {
                    ++flaggedCells;
                    ++movesDone;
                }
                break;
            case 'm':
                getMove(m, n, &move);
                result = markCell(m, n, grid, move);
                if(result == ALREADY_OPEN)
                {
                    printf("The cell is already open!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == ALREADY_FLAGGED)
                {
                    printf("The cell is already flagged!");
                    flushstdin(); // Wait for ENTER
                }
                else if(result == ALREADY_MARKED)
                {
                    printf("The cell is already marked!");
                    flushstdin(); // Wait for ENTER
                }
                else
                {
                    ++markedCells;
                    ++movesDone;
                }
                break;
            case 'u':
                getMove(m, n, &move);
                result = unmarkCell(m, n, grid, move);
                if(result == FLAG_REMOVED)
                {
                    --flaggedCells;
                    ++movesDone;
                }
                else if(result == MARK_REMOVED)
                {
                    --markedCells;
                    ++movesDone;
                }
                else
                {
                    printf("The cell is not flagged nor marked!");
                    flushstdin(); // Wait for ENTER
                }
                break;
            case 's':
                // Save game and return to main menu
                score = calculateScore(m, n, timePassed, movesDone);
                timePassed = time(NULL)-start;
                result = saveGame(m, n, grid, timePassed,  movesDone, SAVING_FILE);
                if(result == 1)
                {
                    printf("Failed to save game!");
                    flushstdin(); // Wait for ENTER
                    break;
                }
                else
                {
                    printf("Game saved successfully!");
                    flushstdin(); // Wait for ENTER
                    return SAVE_AND_EXIT;
                }
            case 'q':
                // Return to main menu if user confirms their choice
                printf("Are you sure that you want to quit the game without saving?\n(Y/y for yes, otherwise for no): ");
                action = ab_getchar();
                action = tolower(action);
                if(action == 'y')
                {
                    return EXIT_NO_SAVE;
                }
                else
                {
                    break;
                }
            default:
                printf("Unknown Action!\n");
                flushstdin(); // Wait for ENTER
            }
        }

        timePassed = time(NULL)-start; // Update time
        score = calculateScore(m, n, timePassed, movesDone); // Update score
    }

    // Game ended, player won or lost.
    system(CLR_SCR);
    printHeader(timePassed, movesDone, flaggedCells, markedCells, score);
    printf("\n");
    switch(end)
    {
    case PLAYER_WON:
        // Marked all mines with F
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j].type == MINE_CELL)
                    grid[i][j].status = CELL_FLAGGED;
            }
        }
        printGrid(m, n, grid, "", 0);
        printf("\n");
        printf("Congratulations! You have won!\n");
        char playerName[128];
        printf("Please enter your name: ");
        getstring(128, playerName);
        if(!addScore(playerName, score, SCORES_FILE))
        {
            printf("Couldn't record score to file!\n");
            flushstdin(); // Wait for ENTER
        }
        break;
    case PLAYER_LOST:
        printf("You've touched a mine! BOOM! :'(\n\n");
        // Open all cells and mark false flags and missed mines
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j].status == CELL_FLAGGED)
                {
                    if(grid[i][j].type != MINE_CELL)
                    {
                        grid[i][j].type = INCORRECT_FLAG;
                        grid[i][j].status = CELL_OPEN;
                    }
                }
                else // if not flagged (open, closed, or marked)
                {
                    // Not flagged but actually a mine?
                    if(grid[i][j].type == MINE_CELL)
                    {
                        grid[i][j].type = MISSED_MINE;
                        grid[i][j].status = CELL_OPEN;
                    }
                    // Not flagged  and not a mine
                    else
                    {
                        grid[i][j].status = CELL_OPEN;
                    }
                }
            }
        }
        // Unveil grid
        printGrid(m, n, grid, "", 0);
        flushstdin(); // Wait for ENTER
    }

    return end;
}





