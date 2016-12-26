/*
 * Utility functions for obtaining validated input from the user
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "input.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ENTER_KEY 10

void flushstdin()
{
    while(getchar() != ENTER_KEY);
}

void trimSpaces(char *str)
{
    char *pstr = str;
    int curchar = 0;
    while(isspace(*pstr)) // Trim leading whitespaces
        ++pstr;

    // Trim trailing whitespaces
    while(*pstr)
    {
        if(!isspace(*pstr)) // Not space?
        {
            str[curchar++] = *pstr;
        }
        else if(*pstr == ' ' && *(pstr+1) && !isspace(*(pstr+1))) // Space preceding a non-space non-null character?
        {
            str[curchar++] = *pstr;
        }

        ++pstr;
    }

    str[curchar] = '\0';
}

char ab_getchar()
{
    char buffer[3];
    getstring(3, buffer);
    char c;
    sscanf(buffer, "%c", &c);
    return c;
}

int getint()
{
    char buffer[4];
    char valid;
    do
    {
        valid = 1;
        getstring(4, buffer);

        // Input consists of digits only?
        for(int i=0; buffer[i]; ++i)
        {
            if(!isdigit(buffer[i]) && !isspace(buffer[i]))
            {
                printf("Please enter a valid number: ");
                valid = 0;
                break;
            }
        }
    }
    while(!valid);

    // User entered a number...
    int number;
    sscanf(buffer, "%d", &number);
    return number;
}

void getstring(int size, char *str)
{
    char overflow;
    do
    {
        overflow = 0;

        /*
         * We are actually getting only (size-2) characters...
        /* Because the newline at the end of the string is also read,
        /* and last character is automatically set to '\0' by (fgets)
         */
        fgets(str, size, stdin);

        if(!strchr(str, '\n')) // no newline (i.e.: fgets buffer overflow)
        {
            flushstdin();
            printf("Too much characters given!\nTry again: ");
            overflow = 1;
        }
        else // replace newline by null-terminator
        {
            int i;
            for(i=0; str[i] != '\n'; ++i);
            str[i] = '\0';
        }

        trimSpaces(str);
    }
    while(overflow || str[0] == '\0');
}
