/*****************************************************************************
 *
 *	Emboss main program.
 *
 *  Description:
 *  Embossing Demo using LibSDL.
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

void DrawImage(spriteContext *sprite, int cx, int cy)
{
    int tlx, tly;
    int sw, sh;

    drawGetSpriteExtent(sprite, &sw, &sh);

    tlx = cx - sw/2;
    tly = cy - sh/2;

    drawSprite(sprite, tlx, tly);
}


void UpdateView(DEMO_S_T *demo, int x, int y)
{
    switch(demo->view_mode)
    {
        case MODE_VIEW_ALL:
            drawBackground(CLR_BLACK);
            DrawImage( &demo->inputSprite, LEFT_X, CENTER_Y);
            DrawImage( &demo->mapSprite, MIDDLE_X, CENTER_Y);
            DrawImage( &demo->outputSprite, RIGHT_X, CENTER_Y);
            break;
        case MODE_VIEW_INPUT:
            drawBackground(CLR_BLACK);
            DrawImage( &demo->inputSprite, MIDDLE_X, CENTER_Y);
            break;
        case MODE_VIEW_MAP:
            drawBackground(CLR_BLACK);
            DrawImage( &demo->mapSprite, MIDDLE_X, CENTER_Y);
            break;
        case MODE_VIEW_OUTPUT:
            drawBackground(CLR_BLACK);
            DrawImage( &demo->outputSprite, MIDDLE_X, CENTER_Y);
            break;
        default:
            break;
    }
    drawSwapBuffers();
}


void Demo(DEMO_S_T *demo)
{
    int w, h;    // screen width and height   

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" a  - view all images\n");
    printf(" i  - view input image\n");
    printf(" m  - view map image\n");
    printf(" o  - view output image\n");
    printf(" r  - repeat processing\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(1000);  

    // initialize the drawing package
    drawInitExtended(demo->screen_w, demo->screen_h, demo->bpp, "Emboss");
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // load sprites
    drawLoadSprite(&demo->inputSprite,  demo->inputName);
    drawLoadSprite(&demo->mapSprite,    demo->mapName);

    drawLoadSprite(&demo->outputSprite, demo->outputName);

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //

    int done = 0;
    char key;
    int x, y;

    UpdateView( demo, x, y );

    while (!done)
    {
        switch( drawGetEvent( &x, &y, &key ) )
        {
            case KEY_DOWN:
                switch(key)
                {
                    case 'a':
                        printf("viewing all\n");
                        demo->view_mode = MODE_VIEW_ALL;
                        UpdateView( demo, x, y );
                        break;
                    case 'i':
                        demo->view_mode = MODE_VIEW_INPUT;
                        printf("viewing input\n");
                        UpdateView( demo, x, y );
                        break;
                    case 'm':
                        demo->view_mode = MODE_VIEW_MAP;
                        printf("viewing map\n");
                        UpdateView( demo, x, y );
                        break;
                    case 'o':
                        demo->view_mode = MODE_VIEW_OUTPUT;
                        printf("viewing output\n");
                        UpdateView( demo, x, y );
                        break;
                    case 'r':
                        printf("repeat processing\n");
                        demo->view_mode = MODE_VIEW_ALL;
                        UpdateView( demo, x, y );
                        break;
                    case 'q':
                        done = 1;
                        break;
                    case 'x':
                        printf("clearing screen\n");
                        drawBackground(CLR_BLACK);
                        drawSwapBuffers();
                        break;
                }
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

    DEMO_S_T demo;

    demo.view_mode = MODE_VIEW_ALL;
    demo.screen_w = WIDTH;
    demo.screen_h = HEIGHT;
    demo.bpp = BPP;               
    strcpy(demo.inputName, DEFAULT_INPUT_NAME);
    strcpy(demo.mapName, DEFAULT_MAP_NAME);
    strcpy(demo.outputName, DEFAULT_OUTPUT_NAME);

    // if no command line arguments
    switch (argc)
    {
        case 1:
            PrintBanner();
            printf("Let's draw ...\n");
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
                            PrintUsage();
                            play = 0;
                            break;        
                        case 'v':
                            PrintBanner();
                            play = 0;
                            break;
                        case 'i':
                            strcpy(demo.inputName, argv[i+1]);
                            i++;
                            break;
                        case 'm':
                            strcpy(demo.mapName, argv[i+1]);
                            i++;
                            break;
                        case 'o':
                            strcpy(demo.outputName, argv[i+1]);
                            i++;
                            break;
                        default:
                            PrintUsage();
                            play = 0;
                            exit(1);
                    }	/* end of inner switch */
                }
                i++;	/* increment arg index */
            }
            break;
    }
    
    if (play)
    {
        Demo(&demo);
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to Emboss %s\n", VERSION);
    printf("******************************************************\n");
    printf("\nUsing DrawSdl version %s\n\n", drawGetVersion() );
}

void PrintUsage()
{
    printf("Usage:  emboss [-h][-v] [-i input-file] [-m map-file] [-o output-file]\n");
    printf("   -h           display help\n");
    printf("   -v           display version\n");
    printf("   -i file      input image file\n");
    printf("   -m file      map image file\n");
    printf("   -o file      output image file\n");
}

/* end of main.c */
