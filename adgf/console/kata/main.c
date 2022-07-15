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

#include "kata.h"


#define DEBUG


#define VERSION "0.1"


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int BOOLEAN_T;


void DisplayVersion( char *progname );
void ErrorUsage( char *progname );


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
   char prog_name[64];
   char file_list_name[64];

   BOOLEAN_T  do_processing = TRUE;
   BOOLEAN_T  is_interactive = FALSE;

   int 	i, parse_count;
   int  knum = 1;


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
               knum = atoi(argv[i]);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   DisplayVersion( prog_name );

   if ( do_processing )
   {
      kata(knum);
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
void DisplayVersion( char *progname )
{
   fprintf(stdout, "Kata - version %s\n", VERSION);
}


/*  ErrorUsage - output usage error message and exit
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void ErrorUsage( char *progname )
{
   fprintf(stderr, "Usage: %s [number] | [-h]|[-v]]\n", progname);
}


/* end of main.c */
