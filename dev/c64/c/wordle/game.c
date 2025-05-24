/*****************************************************************************
 *
 *	Wordle - code for word guessing game
 *
 *	File:	game.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	05/17/2025
 *
 *	Revs:
 *	  0.0 	05/17/2025  originated
 *
 *	Usage:	wordle [args]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <math.h>
#include <time.h>

#include "game.h"


//#define DEBUG

#define TO_UPPER(c) (c & 0xDF)
#define TO_LOWER(c) (c | 0x20)


// Table of words to randomly select
//
#define NUM_WORDS 20
WORD_S_T words[] = {
1,  "READY",
2,  "ACTOR",
3,  "STEAR",
4,  "ANGER",
5,  "BINGO",
6,  "WINGS",
7,  "RULER",
8,  "SUPER",
9,  "GUMBO",
10, "TAPER",
11, "FINAL",
12, "PIECE",
13, "FOXES",
14, "FINAL",
15, "POINT",
16, "BAKER",
17, "PENNY",
18, "CAMEL",
19, "FIXES",
20, "COUNT",
-1,	" "
};

void DebugPrint(char *msg)
{
	#ifdef DEBUG
	printf("%s\n", msg);
	#endif
}
void DebugPrintNumber(char *msg, int value)
{
	#ifdef DEBUG
	printf("%s %d\n", msg, value);
	#endif
}
void DebugPrintString(char *msg, char *str)
{
	#ifdef DEBUG
	printf("%s %s\n", msg, str);
	#endif
}


// Local functions to be called by PlayGame()
//

void InitGame(GAME_S_T *game)
{
	int i, s;
	
	DebugPrint("InitGame");
	
	game->play_game = TRUE;
	game->suppress = TRUE;
	game->debug_enabled = TRUE;
	game->verbose = TRUE;	
		
	game->guess_count = 0;
	
	game->status = STATUS_NO_WIN;
	
	// clear guesses
	for (i = 0; i < MAX_GUESSES; i++)
	{
		game->guesses[i].idnum = i + 1;
		strcpy( game->guesses[i].guess, " " );
		
		for (s = 0; s < GUESS_LENGTH; s++ )
		{
			game->guesses[i].status[s] = LETTER_NO_MATCH;
		}
	}
	
	// clear picked word
	game->word.idnum = 0;
	strcpy( game->word.word, " " );
}

void CloseGame(GAME_S_T *game)
{
	DebugPrint("CloseGame");	
	game->play_game = FALSE;
}

INDEX_T RandomPick()
{
	INDEX_T index;
	int value; 
    int upper_bound = NUM_WORDS * 100;
    int lower_bound = 100;
	
	DebugPrint("RandomPick");

	value = rand() % (upper_bound - lower_bound + 1) + lower_bound;
	printf("value = %d\n", value);
	
	index = value / 100;
	printf("random = %d\n", index);
	
	return(index);
}
void PickWord(GAME_S_T *game)
{
	INDEX_T index;

	DebugPrint("PickWord");
	
	index = RandomPick();
	
	if (index == NUM_WORDS)
		index = NUM_WORDS - 1;
	
	game->word.idnum = words[index].idnum;
	strcpy( game->word.word, words[index].word );
	
	DebugPrintString("Picked =", game->word.word);
}

void DisplayGuesses(GAME_S_T *game)
{
	int i,j;
	
	DebugPrint("DisplayGuesses");
	
	printf("\n");
	printf("\nGuess -- Status\n");
	printf("\n");

	for (i = 0; i < game->guess_count; i++)
	{
		printf("%s -- ", game->guesses[i].guess);
		
		for (j = 0; j < GUESS_LENGTH; j++)
		{
			switch (game->guesses[i].status[j])
			{
				case LETTER_NO_MATCH:
					printf("-");
					break;
				case LETTER_MATCH:
					printf("y");
					break;
				case LETTER_EXACT:
					printf("G");
					break;
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void GetGuess(GAME_S_T *game)
{
	int i;
	SHORT_BUFFER_T guess;
	
	INDEX_T index = game->guess_count;
	
	DebugPrint("GetGuess");
	
	printf("Enter guess> ");
	scanf("%s", &guess);
	
	if (strlen(guess) > 0)
	{
		if (strlen(guess) <= 5)
		{	
			for (i = 0; i < GUESS_LENGTH; i++)
			{
				guess[i] = toupper(guess[i]);
			}
			strcpy( game->guesses[index].guess, guess );
		}
		else
		{
			printf("ERROR\n");
			exit(0);
		}
	}
}

void CheckGuess(GAME_S_T *game)
{
	int i,j;
	int exacts = 0;

	INDEX_T index = game->guess_count;

	DebugPrint("CheckGuess");
	
	game->guess_count++;
	
	// do checking
	DebugPrintNumber("guess # ", game->guess_count);
	
	for (i = 0; i < GUESS_LENGTH; i++)
	{
		// check for exact position match
		if (game->guesses[index].guess[i] == game->word.word[i])
		{
			game->guesses[index].status[i] = LETTER_EXACT;
			exacts++;
		}
		else // check for other position matches
		{
			for (j = 0; j < GUESS_LENGTH; j++)
			{
				if ( i != j )
				{
					if (game->guesses[index].guess[i] == game->word.word[j])
					{
						game->guesses[index].status[i] = LETTER_MATCH;
					}
				}
			}
		}
	}
	
	if (exacts == GUESS_LENGTH)
	{
		game->status = STATUS_WIN;
	}
	else if (game->guess_count == MAX_GUESSES)
	{
		game->status = STATUS_LOSE;
	}
}

void DisplayGameResults(GAME_S_T *game)
{
	DebugPrint("DisplayGameResults");
	
	if (game->status == STATUS_LOSE)
	{
		printf("!!! You Lose !!!\n");
		printf("\nWord was %s\n", game->word.word);
	}
	
	if (game->status == STATUS_WIN)
	{
		printf("!!! You Win !!!\n");
	}
}


// External function to be called by main()
//
void PlayGame(GAME_S_T *game)
{
	BOOLEAN_T done;

	DebugPrint("PlayGame");
	
	if (game->play_game);
	{
		PickWord(game);
	
		while (!done)
		{
	
			if ( game->status == STATUS_LOSE || game->status == STATUS_WIN )
			{
				done = 1;
			}
			else
			{
				GetGuess(game);
		
				CheckGuess(game);
				
				DisplayGuesses(game);
			}
		}
	
		DisplayGameResults(game);
	}
}

/* end of game.c */
