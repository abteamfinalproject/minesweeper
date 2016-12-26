/*
 * Saving test unit
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../scores.h"

#define SCORESFILE "scores.dat"

int main(int argc, char *argv[])
{
	srand(time(NULL));
	printf("Adding scores...\n");
	for(int i=1; i<argc; ++i)
	{
		addScore(argv[i], rand()%200+100, SCORESFILE);
	}

	printf("Reading scores...\n\n");
	displayScores(SCORESFILE);

	return 0;
}
