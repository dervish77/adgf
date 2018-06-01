/*****************************************************************************
 *
 *	DrawDemo main program.
 *
 *  Description:
 *  DrawDemo using LibSDL.
 *
 *	File:	main.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


/*
 *  STATICS
 */



/*
 *  FUNCTIONS
 */

void DrawByMode(int mode, int x, int y)
{
    switch(mode)
    {
        case 1:
            drawPixel( CLR_WHITE, x, y );
            break;
        case 2:
            drawSolidRect( CLR_WHITE, x, y, 50, 50 );
            break;
        case 3:
            drawCircle( CLR_WHITE, x, y, 50 );
            break;
    }
    drawSwapBuffers();
}


void Demo()
{
    int w, h;    // screen width and height   

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" p  - pixel mode\n");
    printf(" r  - rectangle mode\n");
    printf(" c  - circle mode\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(1000);  

    // initialize the drawing package
    drawInitExtended(WIDTH, HEIGHT, BPP, "DrawDemo");
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //

    // draw white dots while left mouse button is pressed
    int done = 0;
    int drawing = 0;
    char key;
    int x, y;
    int mode = 1;
    while (!done)
    {
        switch( drawGetEvent( &x, &y, &key ) )
        {
            case KEY_DOWN:
                switch(key)
                {
                    case 'p':
                        mode = 1;
                        break;
                    case 'r':
                        mode = 2;
                        break;
                    case 'c':
                        mode = 3;
                        break;
                    case 'q':
                        done = 1;
                        break;
                    case 'x':
                        drawBackground(CLR_BLACK);
                        drawSwapBuffers();
                        break;
                }
                break;
#if 0
	    case MOUSE_MOTION:
                if (drawing)
                {
                    DrawByMode( mode, x, y );
                }
                break;
#endif
	    case MOUSE_LEFT_DOWN:
                drawing = 1;
                if (drawing)
                {
                    DrawByMode( mode, x, y );
                }
                break;
            case MOUSE_LEFT_UP:
                drawing = 0;
                break;
            case MOUSE_RIGHT_DOWN:
                done = 1;
                break;
            case WINDOW_QUIT:
                done = 1;
                break;
        }
    }

    // END DEMO HERE //

    drawQuit();
}


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

       
    // if no command line arguments
    switch (argc)
    {
        case 1:
            PrintBanner();
            printf("Let's draw ...\n");
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
    
    if (play)
    {
        Demo();
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to DrawDemo %s\n", VERSION);
    printf("******************************************************\n");
    printf("\nUsing DrawSdl version %s\n\n", drawGetVersion() );
}

void PrintUsage()
{
    printf("Usage:  drawdemo [-h][-v]\n");
    printf("   -h           display help\n");
    printf("   -v           display version\n");
}

/* end of main.c */
