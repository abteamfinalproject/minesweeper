/*
 * Utility functions for obtaining validated input from the user
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_INPUT_H__
#define __ABTEAM_INPUT_H__

// Used to remove the ENTER character and any extra characters left in (stdin)
void flushstdin(void);

// Trims leading and trailing spaces from a string
void trimSpaces(char *str);

char ab_getchar(void);
int getint(void);
void getstring(int size, char *str);

#endif
