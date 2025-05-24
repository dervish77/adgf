/*****************************************************************************
 *
 *	Wordle - code for word guessing game
 *
 *	File:	game.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	05/17/2025
 *
 *	Revs:
 *	  0.0 	05/17/2025  originated
 *
 *****************************************************************************/

#ifndef _GAME_H
#define _GAME_H


/*  define version
 */
#define VERSION		"0.1"
#define VERSIONDATE	"05/17/2025"


/*  define some constants
 */
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define SHORT_BUFF_LEN	10
#define LONG_BUFF_LEN	40

#define GUESS_LENGTH    5	/* each guess is 5 letters */
#define MAX_GUESSES		6	/* max number of guesses */

// guess letter status
#define LETTER_NO_MATCH		0
#define LETTER_MATCH		1
#define LETTER_EXACT		2

// game status
#define STATUS_NO_WIN		0
#define STATUS_LOSE			1
#define STATUS_WIN			2


/*  define some useful types
 */
typedef unsigned char BOOLEAN_T;

typedef char SHORT_BUFFER_T[SHORT_BUFF_LEN];
typedef char LONG_BUFFER_T[LONG_BUFF_LEN];

typedef short int 	 INDEX_T;



/*  define guess structure
 */
typedef struct guess_s_t {
   INDEX_T           idnum;      /* guess id number */
   SHORT_BUFFER_T    guess;      /* guess string */
   int               status[GUESS_LENGTH]; /* status for each letter of guess */
} GUESS_S_T;


/*  define word structure
 */
typedef struct word_s_t {
   INDEX_T           idnum;      /* word id number */
   SHORT_BUFFER_T    word;       /* word string */
} WORD_S_T;


/*  define main game structure
 */
typedef struct game_s_t {
   BOOLEAN_T          play_game;        /* play game flag */
   BOOLEAN_T          suppress;         /* suppress instructions flag */
   BOOLEAN_T          debug_enabled;    /* debug flag */
   BOOLEAN_T          verbose;          /* verbose flag */
   INDEX_T            guess_count;
   int                status;           /* current game status */
   GUESS_S_T          guesses[MAX_GUESSES];
   WORD_S_T           word;             /* word to be guessed */
} GAME_S_T;


/*  declare prototypes for all functions
 */

extern void InitGame(GAME_S_T *game);

extern void PlayGame(GAME_S_T *game);

extern void CloseGame(GAME_S_T *game);

#endif 	/* _GAME_H */
