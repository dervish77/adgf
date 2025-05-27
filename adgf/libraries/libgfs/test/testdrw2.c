/*************************************************************************

   Test program for testing LIBGFS 2 drawing area gadgets.

	Key functions:
		q 	- quit
		c 	- clear draw area 1
		l	- draw line
		r	- draw rectangle
		p	- draw polygon

   File:	testdrw2.c
 
   Author:	Brian Lingard

   Date:	1/29/95

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

#define SCREEN_WIDTH	730
#define SCREEN_HEIGHT	520

#define AREA1_WIDTH	500
#define AREA1_HEIGHT	500

#define AREA2_WIDTH	200
#define AREA2_HEIGHT	500

#define FOREVER		1

static verts_x[5] = { 200, 210, 240, 270, 280 };

static verts_y[5] = { 100, 140, 180, 140, 100 };


/******************************************************************

  main()  

******************************************************************/
main(argc,argv)
   int argc;
   char *argv[];
{
   point 		start, end;

   rectangle		rect;

   point		verts[5];

   GS_rgbType		color;

   GS_gadgetID	 	drw_area1, drw_area2;
   GS_windowID	 	win;
   GS_eventType		event_type;

   GS_gadgetID	 	gid;
   char			key;

   point		click;
   int			which_button;
   int			button_status;

   int 			i;



   /*  make a window
    */
   win = GS_MakeWindow( "testdraw", SCREEN_WIDTH, SCREEN_HEIGHT,
			8, GSCYAN, GSWHITE);


   /*  make two drawing areas
    */
   drw_area1 = GS_MakeDrawArea( AREA1_WIDTH, AREA1_HEIGHT, 260, 260, 
				GSCENTERED, GSWHITE, GSBLACK, GSWHITE);

   drw_area2 = GS_MakeDrawArea( AREA2_WIDTH, AREA2_HEIGHT, 620, 260, 
				GSCENTERED, GSWHITE, GSBLACK, GSWHITE);


   /*  initialize the window
    */
   GS_InitWindow(win);


   /*  draw any lines or polygons here for drawing area 1
    */
   start = GS_DefPoint(20, 20);
   end = GS_DefPoint(480, 480);
   GS_DrawLine(drw_area1, start, end);

   rect.bottom_left = GS_DefPoint(50, 400);
   rect.top_right = GS_DefPoint(150, 450);
   GS_DrawRectangle(drw_area1, rect);

   GS_SetDrawingColor(drw_area1, GSGREEN);
   for (i = 0; i < 5; i++)
      verts[i] = GS_DefPoint(verts_x[i], verts_y[i]);
   GS_DrawPolyline(drw_area1, 5, &verts[0]);

   GS_SetDrawingColor(drw_area1, GSRED);
   for (i = 0; i < 5; i++)
      verts[i] = GS_DefPoint(verts_x[i] + 100, verts_y[i]);
   GS_DrawPolygon(drw_area1, 5, &verts[0]);


   /*  draw color ramp in drawing area 2
    */
   start = GS_DefPoint(25, 25);
   end = GS_DefPoint(175, 25);

   color.R = 1000;
   color.G = 0;
   color.B = 0;

   for (i = 0; i < 200; i++)
   {
      color.R += 2000;
      color.G += 1000;
      color.B += 250;

      GS_AddNewColor( GS_CUSTOM_COLOR_START + i, color );

      start.y++;
      end.y++;

      GS_SetDrawingColor(drw_area2, GS_CUSTOM_COLOR_START + i );
      GS_DrawLine( drw_area2, start, end );
   }


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
            GS_ClearDrawArea(drw_area1);
         else if ((key == 'l') || (key == 'L'))
            GS_DrawLine(drw_area1, start, end);
         else if ((key == 'r') || (key == 'R'))
            GS_DrawRectangle(drw_area1, rect);
         else if ((key == 'p') || (key == 'P'))
            GS_DrawPolygon(drw_area1, 5, &verts[0]);
      }

      else if (event_type == GSMOUSEVENT)
      {
         gid = GS_InquireEventGadgetID();

         if (gid == drw_area1)
         {
            click = GS_InquireEventLocation();

            which_button = GS_InquireEventWhichButton();

            button_status = GS_InquireEventButtonStat();

            printf("draw area 1 - button %d was %d at %d %d\n", 
			which_button, button_status, click.x, click.y);
         }

         else if (gid == drw_area2)
         {
            click = GS_InquireEventLocation();

            which_button = GS_InquireEventWhichButton();

            button_status = GS_InquireEventButtonStat();

            printf("draw area 2 - button %d was %d at %d %d\n", 
			which_button, button_status, click.x, click.y);
         }
         else
            printf("unknown gadget");
      }

   } /* end of forever loop */


   GS_CloseWindow(win);

   exit(0);
} /* end of main() */

/* end of file testdrw2.c */
