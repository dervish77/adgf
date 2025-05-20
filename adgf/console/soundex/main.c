/*****************************************************************************
 *
 *	Soundex translator main program.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	6/4/96
 *
 *	Revs:
 *	  0.4 	03/23/11  re-implemented command line parsing
 *	  0.0 	06/04/96  originated
 *
 *	Usage:	soundex [<surname string> | [-f surname_file]|[-h]|[-v]]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file.h"
#include "soundex.h"
#include "main.h"


#define DEBUG



/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
int main(int argc, char **argv)
{
   DATABASE_S_T		data;		/* main database */
   SURNAME_T		surname;	/* surname string */

   BOOLEAN_T        is_interactive = FALSE;
   BOOLEAN_T        is_file_list_given = FALSE;

   BOOLEAN_T        do_processing = TRUE;

   char prog_name[64];
   char file_list_name[64];
   int 	i, parse_count;


   // get program's name
   //
   strcpy( prog_name, argv[0] );


   // parse command line arguments
   //
   switch (argc)
   {
      case 1:
         is_interactive = TRUE;
         break;

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'f':
                     is_file_list_given = TRUE;
                     if ( argc == (i+2) )
                     {
                        strcpy( file_list_name, argv[i+1] );
                        i++;
                        do_processing = TRUE;
                     }
                     else
                     {
                        ErrorUsage(prog_name);
                        exit(1);
                     }
                     break;

                  case 'h':
                     ErrorUsage(prog_name);
                     do_processing = FALSE;
                     break;

                  case 'v':
                     do_processing = FALSE;
                     break;

                  default:
                     ErrorUsage(prog_name);
                     exit(1);
                     break;
               }	/* end of inner switch */
            }
            else
            {
               strcpy( data.surname, argv[i] );

               data.list.count = 1;
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */


   DisplayVersion( prog_name );


   //  get surname interactively from user
   //
   if ( is_interactive )
   {
      printf("\nEnter surname:  ");

      fgets( surname, MAX_SURNAME_LENGTH, stdin);

      strcpy( data.surname, surname );
      data.surname[ strlen(surname) - 1 ] = 0;

      data.list.count = 1;
   }


   //  read surnames from list
   //
   if ( is_file_list_given )
   {
            if ( OpenSurnameListFile( file_list_name, &data ) )
            {
               ErrorOpenFile( file_list_name );
            }
            else
            {
               ReadSurnameListFile( &data );

#ifdef DEBUG
               OutputSurnameList( &data );
#endif

               CloseSurnameListFile( &data );
            }
   }


   //  parse surname or the surname list
   //
   if ( do_processing )
   {
      parse_count = data.list.count;

      printf("\nSoundex output:\n");

      for (i = 0; i < parse_count; i++)
      {
         // if we have a list, take next surname from list
         if ( parse_count > 1 )
         {
            strcpy(data.surname, data.list.surname[i]);
         }

         ParseSurname( &data );

         DisplaySoundex( &data );
      }
   }

   return(0);
}


/*  DisplayVersion - output usage error message and exit
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
DisplayVersion( char *progname )
{
   fprintf(stdout, "Soundex - version %s\n", VERSION);
}


/*  ErrorUsage - output usage error message and exit
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
ErrorUsage( char *progname )
{
   fprintf(stderr, "Usage: %s [<surname string> | [-f surname_file]|[-h]|[-v]]\n", progname);
}


/* end of main.c */
