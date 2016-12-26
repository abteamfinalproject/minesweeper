/*
 * Minesweeper Project - Main
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "input.h"
#include "grid.h"
#include "gameloop.h"
#include "saving.h"
#include "scores.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int sig)
{
    switch(sig)
    {
    case SIGINT:
        signal(SIGINT, handler);
        break;
    case SIGTSTP:
        signal(SIGTSTP, handler);
        break;
    case SIGQUIT:
        signal(SIGQUIT, handler);
    }
}

int main()
{
    signal(SIGINT, handler); // (Ctrl-C)
    signal(SIGTSTP, handler); // (Ctrl-Z)
    signal(SIGQUIT, handler); // (Ctrl-\)
    setbuf(stdout, NULL); // Write directly to screen (i.e.: no buffer)
    int m, n;
    char choice;
    char valid; // Flag for input validation

    // Print main menu
    while(1)
    {
        valid = 1;
        do
        {
            system(CLR_SCR);
            printf("Minesweeper Game\n\n\t1) New Game\n\t2) Load Game\n\t3) Hall of Fame\n\t4) Exit\n\n");
            printf("Choice: ");
            choice = ab_getchar();
            system(CLR_SCR);
            if(choice == '1')
            {
                printf("Enter the dimensions of the grid\n");
                printf("Rows: ");
                m = getint();
                printf("Columns: ");
                n = getint();
                while(m < 2 || m > 30 || n < 2 || n > 30)
                {
                    printf("Please enter dimensions between 2x2 and 30x30\n");
                    printf("Rows: ");
                    m = getint();
                    printf("Columns: ");
                    n = getint();
                }
                system(CLR_SCR);
                Cell grid[m][n];
                prepareGrid(m, n, grid);
                startGame(m, n, grid, 0, 0);
            }
            else if(choice == '2')
            {
                int timePassed;
                int movesDone;
                if(loadGame_info(&m, &n, &timePassed, &movesDone, SAVING_FILE) == 0)
                {
                    Cell grid[m][n];
                    if(loadGame_grid(m, n, grid, SAVING_FILE) == 0)
                    {
                        startGame(m, n, grid, timePassed, movesDone);
                    }
                    else
                    {
                        printf("Couldn't load saved game grid!");
                        flushstdin(); // Wait for ENTER
                    }
                }
                else
                {
                    printf("Couldn't load saved game info!");
                    flushstdin(); // Wait for ENTER
                }
            }
            else if(choice == '3')
            {
                printf("Hall of Fame\n\n");
                if(!displayScores(SCORES_FILE))
                    printf("Failed to read scores from file!");
                flushstdin(); // Wait for ENTER

            }
            else if(choice == '4')
            {
                return 0;
            }
            else
            {
                printf("Invalid choice!");
                valid = 0;
                flushstdin(); // Wait for ENTER
            }
        }
        while(!valid);
    }

    return 0;
}
