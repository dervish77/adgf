/*****************************************************************************
 *
 *	DrawSdl main program.
 *
 *  Description:
 *  Demo program for drawing with LibSDL.
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
 *	Usage:	drawsdl [-g <pattern>|-h|-m|-v]
 *
 *		-g <pattern>        display graphics pattern
 *		-h                  display help
 *		-m                  display menu (default)
 *		-v                  display version
 *
 *           <pattern>
 *               1       pixels
 *               2       lines
 *               3       boxes
 *               4       triangles
 *               5       circles
 *               6       bitmaps
 *               7       blitters
 *               8       keys
 *               9       mouse
 *               10      animation
 *               11      text
 *               12      polygons
 *               13      sprites
 *               99      full demo
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"

#include "main.h"
#include "demo.h"



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
    int choice = DEMO_EXIT;    
    
    // let's print a banner on the command line
    PrintBanner();

    // parse command line args
    switch (argc)
    {
        case 1:
            // display menu of demos
            choice = DoMenu();
            break;

        case 2:
            if ( (argv[1][0] == '-') && (argv[1][1] == 'h') )
            {
                Usage(stdout, argv[0]);
            }
            else if ( (argv[1][0] == '-') && (argv[1][1] == 'm') )
            {
                choice = DoMenu();
            }
            else if ( (argv[1][0] == '-') && (argv[1][1] == 'v') )
            {
                choice = 0;
            }
            else
            {
                Usage(stderr, argv[0]);
            }
            break;
        case 3:
            if ( (argv[1][0] == '-') && (argv[1][1] == 'g') )
            {
                choice = atoi( argv[2] );
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

    // run the chosen demo
    switch(choice)
    {
        case DEMO_PIXELS:
            DemoPixels();
            break;
        case DEMO_LINES:
            DemoLines();
            break;
        case DEMO_BOXES:
            DemoBoxes();
            break;
        case DEMO_TRIANGLES:
            DemoTriangles();
            break;
        case DEMO_CIRCLES:
            DemoCircles();
            break;
        case DEMO_BITMAPS:
            DemoBitmaps();
            break;
        case DEMO_BLITTERS:
            DemoBlitters();
            break;
        case DEMO_KEYS:
            DemoKeys();
            break;
        case DEMO_MOUSE:
            DemoMouse();
            break;
        case DEMO_ANIM:
            DemoAnim();
            break;
        case DEMO_TEXT:
            DemoText();
            break;
        case DEMO_POLYGONS:
            DemoPolygons();
            break;
        case DEMO_SPRITES:
            DemoSprites();
            break;
        case DEMO_FULL:
            DemoFull();
            break;
        default:
            if (choice > DEMO_EXIT)
            {
                Usage(stderr, argv[0]);
            }
            break;
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("    Welcome to DrawSdl %s - LibSDL drawing demo\n", drawGetVersion());
    printf("******************************************************\n");
}

void Usage( FILE *fp, char *program )
{
   fprintf(fp, "\nUsage: %s [-g <pattern>|-h|-m|-v]\n", program);
   fprintf(fp, "\n");
   fprintf(fp, "  options:\n");
   fprintf(fp, "    -g <pattern>            display graphics pattern\n");
   fprintf(fp, "    -h                      display help\n");
   fprintf(fp, "    -m                      display menu (default)\n");
   fprintf(fp, "    -v                      display version\n");
   fprintf(fp, "\n");
   fprintf(fp, "  <pattern>\n");
   fprintf(fp, "                %d       pixels\n", DEMO_PIXELS);
   fprintf(fp, "                %d       lines\n", DEMO_LINES);
   fprintf(fp, "                %d       boxes\n", DEMO_BOXES);
   fprintf(fp, "                %d       triangles\n", DEMO_TRIANGLES);
   fprintf(fp, "                %d       circles\n", DEMO_CIRCLES);
   fprintf(fp, "                %d       bitmaps\n", DEMO_BITMAPS);
   fprintf(fp, "                %d       blitters\n", DEMO_BLITTERS);
   fprintf(fp, "                %d       keys\n", DEMO_KEYS);
   fprintf(fp, "                %d       mouse\n", DEMO_MOUSE);
   fprintf(fp, "                %d       animation\n", DEMO_ANIM);
   fprintf(fp, "                %d       text\n", DEMO_TEXT);
   fprintf(fp, "                %d       polygons\n", DEMO_POLYGONS);
   fprintf(fp, "                %d       sprites\n", DEMO_SPRITES);
   fprintf(fp, "                %d       full demo\n", DEMO_FULL);
   fprintf(fp, "\n");
}

int DoMenu()
{
    char choice[8];
    
    printf("\n");
    printf("1.  Demo Pixels\n");
    printf("2.  Demo Lines\n");
    printf("3.  Demo Boxes\n");
    printf("4.  Demo Triangles\n");
    printf("5.  Demo Circles\n");
    printf("6.  Demo Bitmaps\n");
    printf("7.  Demo Blitters\n");
    printf("8.  Demo Keys\n");
    printf("9.  Demo Mouse\n");
    printf("10. Demo Animation\n");
    printf("11. Demo Text\n");
    printf("12. Demo Polygons\n");
    printf("13. Demo Sprites\n");
    printf("99. Full Demo\n");
    printf("0.  Exit\n");
    printf("\n");
    printf("Enter choice: ");
    fgets(choice, 3, stdin);
    printf("\n");

    return(atoi(choice));  // converts ascii 0-9 into number 0-9
}

/* end of main.c */
