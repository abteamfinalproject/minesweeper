/*
 * Grid Initialization
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_GRID_H__
#define __ABTEAM_GRID_H__

// Cell statuses
#define CELL_CLOSED 0
#define CELL_OPEN 1
#define CELL_FLAGGED 2
#define CELL_MARKED 3

// Cell types
#define EMPTY_CELL '0'
#define EMPTY_VISITED_CELL 'V'
#define MINE_CELL '*'
#define LOSS_MINE '!'
#define MISSED_MINE 'M'
#define INCORRECT_FLAG '-'

// Cell representations for printing
#define EMPTY_CELL_CHAR ' '
#define CLOSED_CELL_CHAR 'X'
#define FLAGGED_CELL_CHAR 'F'
#define MARKED_CELL_CHAR '?'

typedef struct
{
    char status;
    /*
     * Possible values for (status):
     *  0: Closed
     *  1: Open
     *  2: Flagged
     *  3: Marked
     */
    char type;
    /*
     * Possible values for (type):
     * 	'0': Empty
     *  'v': Empty and visited
     *	'1'~'8': Number of adjacent cells with mines
     *	'*': Mine
     *  '!': Loss mine
     *  'M': Missed mine
     *  '-': Incorrect flag
     */
} Cell;

typedef struct
{
    int x;
    int y;
} Position;

/*
* Gets a random position in a grid of (m X n) dimensions
* NOTE: for this function to work, srand(time(NULL)) must be called at least once before
* using this function or any of its dependents
* to seed the random number generator
*/
Position getRandomPos(int m, int n);

// Returns 1 if Positions (a) and (b) have the same coordinates, 0 otherwise
char positionsEqual(Position a, Position b);

// Returns 1 if (arr) contains (key), 0 otherwise
char arrayContains(Position *arr, int arrsize, Position key);

// Zeroes out (empty) all cells and set them closed
void prepareGrid(int m, int n, Cell grid[m][n]);

/*
 * Populates grid of (m X n) dimensions with mines and numbers. (call prepareGrid first!)
 * This function shall be called after the player makes his first move (firstPos) which shall
 * not contain a mine (be aware of that when choosing mine positions randomly!)
 * NOTE: Prior validation for (m) and (n) is required!
 */
void initGrid(Position firstPos, int m, int n, Cell grid[m][n]);

/*
 * Print grid of (m X n) dimensions
 * To print to (stdout), simply pass an empty string for (filename)
 * For debugging mode (i.e.: all cells open), pass a none zero value for (debug)
 */
void printGrid(int m, int n, Cell grid[m][n], char *filename, char debug);

#endif
