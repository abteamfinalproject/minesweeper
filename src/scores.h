/*
 * Scores
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#ifndef __ABTEAM_SCORES_H__
#define __ABTEAM_SCORES_H__

typedef struct
{
    char playerName[128];
    long long score;
} ScoreEntry;

// Returns 1 if (s1) is identical to (s2), ignoring letter case. Otherwise, returns 0
char strEqual(char *s1, char *s2);

// Reads table of scores from file and stores it in (scores)
char readScores(char *fileName, int numEntries, ScoreEntry *scores);

// Adds the scores of the player to the table of scores file
char addScore(char playerName[128], long long score, char *fileName);

// Reads table of scores from file and displays it
char displayScores(char *fileName);

#endif
