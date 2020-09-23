/*****************************************************************************
 *
 *	Breakout main program.
 *
 *  Description:
 *  Breakout using LibSDL.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *	Date:	11/12/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "game.h"
#include "version.h"



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
    int play = 1;
    int i;

    GAME_S_T game;
    
    // if no command line arguments
    switch (argc)
    {
        case 1:
            printf("Let's play...\n");
            PrintBanner();
            break;
        case 2:
        case 3:
            i = 1;
            while (i < argc)
            {
                if (argv[i][0] == '-')
                {
                    switch(argv[i][1])
                    {
                        case 'h':
                            PrintUsage();
                            play = 0;
                            break;
                        case 'v':
                            PrintBanner();
                            play = 0;
                            break;
                        default:
                            play = 0;
                            exit(1);
                    }	/* end of inner switch */
                }
                i++;	/* increment arg index */
            }
            break;
        default:
            break;
    }
    
    // run the game
    if (play)
    {
        DoGame(&game);
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to Breakout %s\n", VERSION);
    printf("******************************************************\n");
}

void PrintUsage()
{
    printf("Usage:  breakout [-h][-v]\n");
    printf("   -h           display help\n");
    printf("   -v           display version\n");
}

/* end of main.c */
