/*****************************************************************************
 *
 *	DrawSdl unit test main program.
 *
 *  Description:
 *  Unit test program for drawing with LibSDL.
 *
 *	File:	main.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/
/*****************************************************************************
 *
 *	Usage:	drawunit [-h|-v]
 *
 *		-h                  display help
 *		-v                  display version
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"

#include "main.h"
#include "unit.h"



/*
 *  STATICS
 */



/*
 *  FUNCTIONS
 */

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
    int do_unit_test = 0;    
    
    // let's print a banner on the command line
    PrintBanner();

    // parse command line args
    switch (argc)
    {
        case 1:
            // run the unit test suite
            do_unit_test = 1;
            break;

        case 2:
            if ( (argv[1][0] == '-') && (argv[1][1] == 'h') )
            {
                Usage(stdout, argv[0]);
            }
            else if ( (argv[1][0] == '-') && (argv[1][1] == 'v') )
            {
                do_unit_test = 0;
            }
            else
            {
                Usage(stderr, argv[0]);
            }
            break;
        default:
            Usage(stderr, argv[0]);
            break;
    }

    // run the unit test suite
    if ( do_unit_test )
    {
        DoUnitTest();
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("    Welcome to DrawUnit %s - LibSDL unit test\n", drawGetVersion());
    printf("******************************************************\n");
}

void Usage( FILE *fp, char *program )
{
   fprintf(fp, "\nUsage: %s [-h|-v]\n", program);
   fprintf(fp, "\n");
   fprintf(fp, "  options:\n");
   fprintf(fp, "    -h                      display help\n");
   fprintf(fp, "    -v                      display version\n");
   fprintf(fp, "\n");
}

/* end of main.cpp */
