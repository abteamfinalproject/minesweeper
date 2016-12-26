/*
 * Scores
 * Author: AB Team (Abdelhakeem Osama and Abdelrahman Shams)
 */

#include "scores.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char strEqual(char *s1, char *s2)
{
    while(*s1 && *s2)
    {
        if(tolower(*s1) != tolower(*s2))
            return 0;
        ++s1;
        ++s2;
    }

    if(*s1 || *s2) // Not of equal length
        return 0;

    // else
    return 1;
}

char readScores(char *fileName, int numEntries, ScoreEntry *scores)
{
    FILE *file = fopen(fileName, "rb");
    char currentPlayer[128];
    int nameLength;
    int currentScore;
    if(!file) // Failed to open file
        return 0;

    // Read scores
    fseek(file, sizeof(char)*4, SEEK_SET); // Skip "ABMS" prefix
    fseek(file, sizeof(int), SEEK_CUR); // Skip number of entries (we already have it)
    for(int i=0; i<numEntries; ++i)
    {
        fread(&nameLength, sizeof(int), 1, file);
        fread(currentPlayer, sizeof(char), nameLength, file);
        currentPlayer[nameLength] = '\0';
        fread(&currentScore, sizeof(long long), 1, file);

        strcpy(scores[i].playerName, currentPlayer);
        scores[i].score = currentScore;
    }
    fclose(file);
    return 1;
}

char addScore(char playerName[128], long long score, char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    int entries;
    int nameLength;
    char found;

    if(!file) // Failed to open file (No scores have been added yet)
    {
        // Open file in write binary mode
        file = fopen(fileName, "wb");
        if(!file)
            return 0;
        // Write "ABMS" prefix
        char abms[4] = "ABMS";
        fwrite(abms, sizeof(char), 4, file);
        // Write number of entries
        entries = 1;
        fwrite(&entries, sizeof(int), 1, file);
        // Add new score entry
        nameLength = strlen(playerName);
        fwrite(&nameLength, sizeof(int), 1, file);
        fwrite(playerName, sizeof(char), nameLength, file);
        fwrite(&score, sizeof(long long), 1, file);
        fclose(file);
    }
    else // Some scores are already present
    {
        // Read current number of score entries
        fseek(file, sizeof(char)*4, SEEK_SET);
        fread(&entries, sizeof(int), 1, file);
        fclose(file);

        // Read score entries
        ScoreEntry scores[entries+1]; // Reserve +1 extra space for the newly added scores (if player is not found)
        readScores(fileName, entries, scores);

        // Update score entries
        found = 0;
        for(int i=0; i<entries; ++i) // Search if player already added
        {
            if(strEqual(scores[i].playerName, playerName))
            {
                scores[i].score += score;
                found = 1;
                break;
            }
        }

        if(!found) // New player?
        {
            strcpy(scores[entries].playerName, playerName);
            scores[entries].score = score;
            ++entries;
        }

        // Write them out again
        file = fopen(fileName, "rb+"); // Binary update mode
        if(!file) // Failed to open file
            return 0;
        fseek(file, sizeof(char)*4, SEEK_SET);
        fwrite(&entries, sizeof(int), 1, file); // New number of entries

        for(int i=0; i<entries; ++i)
        {
            nameLength = strlen(scores[i].playerName);
            fwrite(&nameLength, sizeof(int), 1, file);
            fwrite(scores[i].playerName, sizeof(char), nameLength, file);
            fwrite(&scores[i].score, sizeof(long long), 1, file);
        }
        fclose(file);
    }

    return 1;
}

char displayScores(char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    char currentPlayer[128];
    int entries;
    if(!file) // Failed to open file
        return 0;

    // Read number of score entries
    fseek(file, sizeof(char)*4, SEEK_SET); // Skip "ABMS" prefix
    fread(&entries, sizeof(int), 1, file);
    fclose(file);
    ScoreEntry scores[entries];
    readScores(fileName, entries, scores);

    // Sort scores
    char sorted;
    char temp[128];
    do
    {
        sorted = 1;
        for(int i=0; i<entries-1; ++i)
        {
            if(scores[i].score < scores[i+1].score)
            {
                sorted = 0;
                // Swap scores
                scores[i].score ^= scores[i+1].score;
                scores[i+1].score ^= scores[i].score;
                scores[i].score ^= scores[i+1].score;

                // Swap player name strings
                strcpy(temp, scores[i].playerName);
                strcpy(scores[i].playerName, scores[i+1].playerName);
                strcpy(scores[i+1].playerName, temp);
            }
        }
    } while(!sorted);

    // Print scores
    printf("%16s\t\tScore\n", "Player");
    printf("%16s\t\t-----\n", "------");
    for(int i=0; i<entries; ++i)
    {
        printf("%16s\t\t%d\n",
               scores[i].playerName, scores[i].score);
    }

    return 1;
}
