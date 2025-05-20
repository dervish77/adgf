/*****************************************************************************
 *
 *	Soundex translator program routines.
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
#include "soundex.h"
#include "file.h"


#define DEBUG



/*  OpenSurnameListFile	- opens specified surname list file
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
int
OpenSurnameListFile( char *filename, DATABASE_S_T *data )
{
   strcpy( data->list.filename, filename );

   data->list.fp = fopen( &data->list.filename[0], "r" );
   if ( data->list.fp EQ (FILE *) NULL)
   {
      return(TRUE);
   }

   return(FALSE);
}


/*  ReadSurnameListFile	- reads current surname list file
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 *
 *  Notes:	file format
 *
 *	count
 *	surname_string_1
 *	surname_string_2
 *	...
 *	surname_string_n
 *
 *  example:
 *
 *	3
 *	evans
 *	hildebrant
 *	smith
 *
 */
int
ReadSurnameListFile( DATABASE_S_T *data )
{
   int i, count;
   SURNAME_T surname;


   fscanf( data->list.fp, "%d\n", &count );

   data->list.count = count;

   for (i = 0; i < data->list.count; i++)
   {
      fscanf( data->list.fp, "%s\n", surname);

      strcpy(data->list.surname[i], surname);
   }

   return(FALSE);
}


/*  OutputSurnameList	- outputs surname list to screen
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
int
OutputSurnameList( DATABASE_S_T *data )
{
   int i;

   printf("\nSurname List:  count = %d\n", data->list.count);

   for (i = 0; i < data->list.count; i++)
   {
      printf("    %d - %s\n", i, data->list.surname[i]);
   }

   return(FALSE);
}


/*  CloseSurnameListFile	- closes current surname list file
 *
 *  Parameters:
 *	data		- pointer to database structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
int
CloseSurnameListFile( DATABASE_S_T *data )
{
   fclose( data->list.fp );

   return(FALSE);
}


/*  ErrorOpenFile	- output open file error message and exit
 *
 *  Parameters:
 *	string		- pointer to character string
 *
 *  Returns:
 *	none
 */
void
ErrorOpenFile( char *string )
{
   fprintf(stderr, "Error:  opening %s as surname list file\n", string);
   exit(1);
}


/* end of file.c */
