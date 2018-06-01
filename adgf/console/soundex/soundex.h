/*****************************************************************************
 *
 *	Soundex translator program - soundex routines header file.
 *
 *	File:	soundex.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	6/4/96
 *
 *	Revs:
 *	  0.0 	6/4/96  originated
 *
 *****************************************************************************/

#ifndef _SOUNDEX_H
#define _SOUNDEX_H

#include "main.h"
#include "file.h"


/*  array of soundex codes for alphabet
 */
#define SOUNDEX_LETTERS "01230120022455012623010202"


/*  define surname string type
 */
#define MAX_SURNAME_LENGTH	40
typedef char SURNAME_T[MAX_SURNAME_LENGTH];


/*  define soundex string type
 */
#define SOUNDEX_LEN		6
typedef char SOUNDEX_T[SOUNDEX_LEN];


/*  define letters used array type
 */
#define LETTERS_USED_LEN	3
typedef char LETTERS_T[LETTERS_USED_LEN];


/*  define file name string type
 */
#define FILE_NAME_LEN		30
typedef char FILENAME_T[FILE_NAME_LEN];


/*  define surname list structure type
 */
#define MAX_SURNAMES_IN_LIST	100
typedef struct surname_list_s_t {
   FILENAME_T   filename;   /* surname list file name string */
   FILE         *fp;        /* surname list file pointer */
   int          count;      /* surname list count */
   SURNAME_T    surname[MAX_SURNAMES_IN_LIST];
} SURNAME_LIST_S_T;


/*  define main database structure
 */
typedef struct database_s_t {
   SURNAME_T		surname;	/* surname string */
   SURNAME_LIST_S_T	list;		/* surname list */
   SOUNDEX_T		soundex_code;	/* soundex coding */
   LETTERS_T		letters_used;	/* letters used array */
} DATABASE_S_T;


/*  declare prototypes for all functions
 */
extern int ParseSurname( DATABASE_S_T *data );

extern int DisplaySoundex( DATABASE_S_T *data );


#endif 	/* _SOUNDEX_H */
