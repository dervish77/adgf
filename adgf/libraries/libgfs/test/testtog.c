/*************************************************************************

   Test program for testing LIBGFS toggle button gadgets.

   File:	testtog.c
 
   Author:	Brian Lingard

   Date:	3/29/95

   Revisions:
     0.0  01/29/95  originated

*************************************************************************/

/* include necessary files */
#include "gspublic.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define DEBUG 1

#define SCREEN_WIDTH	400
#define SCREEN_HEIGHT	200

#define BUTTON_WIDTH	60
#define BUTTON_HEIGHT	20

#define FOREVER		1


/******************************************************************

  main()  

******************************************************************/
main(argc,argv)
   int argc;
   char *argv[];
{
   GS_gadgetID	 	load, run, stop, quit;
   GS_windowID	 	win;
   GS_eventType		event_type;

   GS_gadgetID	 	gid;
   char			key;


   /*  make a window
    */
   win = GS_MakeWindow( "testtog", SCREEN_WIDTH, SCREEN_HEIGHT,
			8, GSCYAN, GSWHITE);


   /*  make some toggle buttons 
    */
   load = GS_MakeToggleButton( "LOAD", BUTTON_WIDTH, BUTTON_HEIGHT,
			20, 170, GSBOTLEFT, GSBLACK, GSGREY, GSBLACK, 
			GSTOGSQUARE);

   run = GS_MakeToggleButton( "RUN", BUTTON_WIDTH, BUTTON_HEIGHT, 
			20, 120, GSBOTLEFT, GSBLACK, GSGREY, GSBLACK, 
			GSTOGSQUARE);

   stop = GS_MakeToggleButton( "STOP", BUTTON_WIDTH, BUTTON_HEIGHT, 
			20, 70, GSBOTLEFT, GSBLACK, GSGREY, GSBLACK, 
			GSTOGSQUARE);

   quit = GS_MakeToggleButton( "QUIT", BUTTON_WIDTH, BUTTON_HEIGHT,
	(SCREEN_WIDTH - 20), 170, GSBOTRIGHT, GSBLACK, GSGREEN, GSBLACK, 
	GSTOGSQUARE);


   /*  initialize the window
    */
   GS_InitWindow(win);


   /*  loop forever, until QUIT selected 
    */
   printf("\nHit 'q' or 'Q' to quit program\n");

   while (FOREVER) 
   {
      event_type = GS_WaitForEvent();

      if (event_type == GSKEYEVENT)
      {
         key = GS_InquireEventChar();

         printf("event - key = %c\n", key);

         if ((key == 'q') || (key == 'Q'))
            break;
      }

      else if (event_type == GSMOUSEVENT)
      {
         gid = GS_InquireEventGadgetID();

         if (gid == quit)
         {
            printf("quit button\n");
            break;
         }

         else if (gid == load)
            printf("load button is %d\n", GS_GetToggleState(gid));

         else if (gid == run)
            printf("run button is %d\n", GS_GetToggleState(gid));

         else if (gid == stop)
            printf("stop button is %d\n", GS_GetToggleState(gid));

         else
            printf("unknown gadget");
      }

   } /* end of forever loop */


   GS_CloseWindow(win);

   exit(0);
} /* end of main() */

/* end of file testtog.c */
