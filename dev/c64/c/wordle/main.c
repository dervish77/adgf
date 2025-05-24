/*****************************************************************************
 *
 *	Wordle - word guessing game
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	05/17/2025
 *
 *	Revs:
 *	  0.0 	05/17/2025  originated
 *
 *	Usage:	wordle [[-h]|[-v]]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <math.h>
#include <time.h>

#include "game.h"

#include "peekpoke.h"
#define USE_COLOR 1


#define DEBUG


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


void DisplayBanner( char *progname );
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
   GAME_S_T game;
	
   char prog_name[16];

   BOOLEAN_T  do_processing = TRUE;
   BOOLEAN_T  is_interactive = TRUE;
#if 0
   int 	i, parse_count;
#endif

#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to black */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

   // seed the random generator
   //
   srand( time(0) );

   // get program's name
   //
   strcpy( prog_name, argv[0] );

#if 0
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
                     exit(0);
                     break;
               }	/* end of inner switch */
            }
            else
            {
               do_processing = TRUE;
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */
#endif

   DisplayBanner( prog_name );

   if ( do_processing )
   {
	  InitGame(&game);
      PlayGame(&game);
	  CloseGame(&game);
   }

   return(0);
}


/*  DisplayBanner - output game banner with version
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void DisplayBanner( char *progname )
{
	printf("\n");
	printf("###################################\n");
	printf("#    Wordle 64 - Version %s      #\n", VERSION);
	printf("###################################\n");
	printf("\n");
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
   fprintf(stderr, "Usage: %s [[-h]|[-v]]\n", progname);
}


/* end of main.c */
