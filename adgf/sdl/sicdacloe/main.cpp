/*****************************************************************************
 *
 *	SicDacLoe main program.
 *
 *  Description:
 *  Tic Tac Toe using LibSDL.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "game.h"
#include "screens.h"
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
    int i, num;
    GAME_S_T game;
    int mode = MODE_UNKNOWN;
    int skill = SKILL_BEST;
    
    // let's print a banner on the command line
    PrintBanner();
   
    // if no command line arguments
    switch (argc)
    {
        case 1:
            printf("Let's play...\n");
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
                        case 'p':
                            num = atoi(argv[i+1]);
                            if (num == 1) 
                            {
                                mode = MODE_ONE_PLAYER;
                            }
                            else if (num == 2) 
                            {
                                mode = MODE_TWO_PLAYER;
                            }
                            else
                            {
                                PrintUsage();
                                play = 0;
                            }                            
                            break;                        
                        case 's':
                            num = atoi(argv[i+1]);
                            if (num == 0) 
                            {
                                skill = SKILL_NONE;
                            }
                            else if (num == 1) 
                            {
                                skill = SKILL_RANDOM;
                            }
                            else if (num == 2) 
                            {
                                skill = SKILL_BEST;
                            }
                            else
                            {
                                PrintUsage();
                                play = 0;
                            }                            
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
        DoGame(&game, mode, skill);
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to Sic Dac Loe %s\n", VERSION);
    printf("******************************************************\n");
}

void PrintUsage()
{
    printf("Usage:  sicdacloe [-h][-p 1|2][-s 0|1|2][-v]\n");
    printf("   -h           display help\n");
    printf("   -p 1|2       number of players\n");
    printf("   -s 0|1|2     skill level\n");
    printf("   -v           display version\n");
}

/* end of main.c */
