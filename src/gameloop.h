/*
 * Game Loop
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_LOOP_H__
#define __ABTEAM_LOOP_H__

#include "grid.h"

// Game loop return codes
#define PLAYER_WON 0
#define PLAYER_LOST 1
#define SAVE_AND_EXIT 2
#define EXIT_NO_SAVE 3

#define SAVING_FILE "savedgame.dat"
#define SCORES_FILE "scores.dat"

// System calls for clearing command line screen
#if defined (__MINGW32__) || defined (__MINGW64__)
#define CLR_SCR "cls"
#elif defined (__gnu_linux__)
#define CLR_SCR "clear"
#endif

// Calculates the score of the player after [timePassed] seconds have passed and [movesDone] moves have been done.
int calculateScore(int m, int n, int timePassed, int movesDone);

/*
 * Prints a header line showing the time passed in seconds, number of moves done, and current score,
 * in addition to the number of flagged cells and number of cells marked with a question mark
 */
void printHeader(int timePassed, int movesDone, int flagged, int marked, long long score);

// Gets the coordinates of the next move from player
void getMove(int m, int n, Position *pos);

// Returns 1 if player won, 0 otherwise
char hasWon(int m, int n, Cell grid[m][n]);

//Starts the game.
char startGame(int m, int n, Cell grid[m][n], int timePassed, int movesDone);

#endif
