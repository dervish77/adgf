/*****************************************************************************
 *
 *	Soundex translator program - soundex routines.
 *
 *	File:	soundex.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	6/4/96
 *
 *	Revs:
 *	  0.0 	6/4/96  originated
 *
 *	Usage:	soundex [surname string]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "file.h"
#include "soundex.h"


#define DEBUG

//#define DEBUG2



/*  ParseSurname	- parses current surname
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
int
ParseSurname( DATABASE_S_T *data )
{
   int i, index;
   char letter;

   SURNAME_T soundex_codes;
   strcpy( soundex_codes, SOUNDEX_LETTERS );

   SURNAME_T surname;
   SURNAME_T parsed;

   // clear out the soundex code value
   for (i=0; i<sizeof(data->soundex_code); i++)
   {
      data->soundex_code[i] = '0';
      surname[i] = ' ';
      parsed[i] = ' ';
   }
   strcpy( surname, data->surname );
   strcpy( parsed, data->surname );
   for (i=0; i<LETTERS_USED_LEN; i++)
   {
       data->letters_used[i] = ' ';
   }

   // parse each letter of surname
   for (i=1; i<strlen(parsed); i++)
   {
       letter = parsed[i];
       if ( !isalpha( letter ))
       {
           letter = 'a';
       }

       letter = toupper( letter );
       index = letter - 'A';

       parsed[i] = soundex_codes[index];
       if (parsed[i] == '0')
       {
           surname[i] = '0';
       }
   }

#ifdef DEBUG2
   printf("surname1 - %s\n", data->surname);
   printf("surname2 - %s\n", surname);
   printf("parsed   - %s\n", parsed);
#endif

   // compress out the zeros
   data->soundex_code[0] = parsed[0];
   data->soundex_code[1] = '-';
   index = 2;
   for (i=1; i<strlen(parsed); i++)
   {
       if (parsed[i] != '0')
       {
           data->soundex_code[index] = parsed[i];
           data->letters_used[index-2] = surname[i];
           index++;
       }
   }
   data->soundex_code[5] = 0;

   return(FALSE);
}


/*  DisplaySoundex	- output current soundex to screen
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
int
DisplaySoundex( DATABASE_S_T *data )
{
   printf("    %s    ", data->surname );

   if (data->letters_used[0] != ' ') printf("%c", data->letters_used[0]);

   if (data->letters_used[1] != ' ') printf(", %c", data->letters_used[1]);

   if (data->letters_used[2] != ' ') printf(", %c",  data->letters_used[2]);

   printf("    %s\n", data->soundex_code );

   printf("\n");

   return(FALSE);
}


/* end of soundex.c */
