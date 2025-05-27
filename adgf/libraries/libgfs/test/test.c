/*************************************************************************

   Test program for testing LIBGFS, a GUI library based upon SRGP.

   File:	test.c
 
   Author:	Brian Lingard

   Date:	3/29/95

   Revisions:
     0.1  01/26/96  
     0.0  03/29/95  originated

*************************************************************************/

/* include necessary files */
#include "gspublic.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define DEBUG 1

#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600

#define BUTTON_WIDTH	60
#define BUTTON_HEIGHT	20

#define AREA_WIDTH	500
#define AREA_HEIGHT	500

#define FOREVER		1


/******************************************************************

  main()  

******************************************************************/
main(argc,argv)
   int argc;
   char *argv[];
{
   point 		start, end;

   GS_gadgetID	 	load, run, stop, quit;
   GS_gadgetID	 	drw_area;
   GS_windowID	 	win;
   GS_eventType		event_type;

   GS_gadgetID	 	gid;
   char			key;

   point		click, anchor;
   int			which_button;
   int			button_status;


   /*  make a window
    */
   win = GS_MakeWindow( "test", SCREEN_WIDTH, SCREEN_HEIGHT,
			4, GSCYAN, GSWHITE);


   /*  make some push buttons 
    */
   load = GS_MakePushButton( "LOAD", BUTTON_WIDTH, BUTTON_HEIGHT,
			20, 570, GSBOTLEFT, GSWHITE, GSGREY, GSBLACK);

   run = GS_MakePushButton( "RUN", BUTTON_WIDTH, BUTTON_HEIGHT, 
			90, 570, GSBOTLEFT, GSWHITE, GSGREY, GSBLACK);

   stop = GS_MakeToggleButton( "STOP", BUTTON_WIDTH, BUTTON_HEIGHT, 
			160, 570, GSBOTLEFT, GSBLACK, GSGREY, GSBLACK,
			GSTOGSQUARE);

   quit = GS_MakePushButton( "QUIT", BUTTON_WIDTH, BUTTON_HEIGHT,
	(SCREEN_WIDTH - 20), 570, GSBOTRIGHT, GSWHITE, GSGREEN, GSBLACK);


   /*  make a drawing area
    */
   drw_area = GS_MakeDrawArea( AREA_WIDTH, AREA_HEIGHT, 300, 275, 
				GSCENTERED, GSWHITE, GSBLACK, GSWHITE);


   /*  initialize the window
    */
   GS_InitWindow(win);


   /*  draw any lines or polygons here
    */
   start = GS_DefPoint(200, 200);
   end = GS_DefPoint(400, 200);
   GS_DrawLine(drw_area, start, end);


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
         else if ((key == 'c') || (key == 'C'))
            GS_ClearDrawArea(drw_area);
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
            printf("load button\n");

         else if (gid == run)
            printf("run button\n");

         else if (gid == stop)
            printf("stop button is %d\n", GS_GetToggleState(gid) );

         else if (gid == drw_area)
         {
            click = GS_InquireEventLocation();

            which_button = GS_InquireEventWhichButton();

            button_status = GS_InquireEventButtonStat();

            printf("draw area - button %d was %d at %d %d\n", 
			which_button, button_status, click.x, click.y);

            if (button_status == DOWN)
            {
               anchor.x = click.x;
               anchor.y = click.y;
            }
            else
            {
               GS_DrawLine(drw_area, anchor, click);
            }
         }

         else
            printf("unknown gadget");
      }

   } /* end of forever loop */


   GS_CloseWindow(win);

   exit(0);
} /* end of main() */

/* end of file test.c */
