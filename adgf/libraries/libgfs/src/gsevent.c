/********************************************************************

   Functions for initializing windows, and handling events which are
   supported by LIBGFS, a GUI library based upon SRGP.

   Author:    Brian Lingard

   File:      gsevent.c
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

   Functions in file:

	GS_InitWindow
        GS_CloseWindow
	GS_WaitForEvent
	GS_InquireEventChar
	GS_InquireEventGadgetID
	GS_InquireEventLocation
	GS_InquireEventMenuItem

	CorrelatePick
	CorrelateMenuItem

*********************************************************************/


/* include necessary files */
#ifndef GSPRIVAT_H
#include "gsprivat.h"
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
 *
 *  Begin public functions
 *
 */


/******************************************************************

  GS_InitWindow() -- This function opens the specified window and 
			initializes various SRGP stuff.  This function
			also draws all known gadgets and drawing
			areas in the window.

******************************************************************/
GS_errorType
GS_InitWindow(GS_windowID w)
{
   int planes_avail;		/* number of planes available */
   rectangle full_screen;
   int i;


   /*  define rectangle for full screen
    */
   full_screen = SRGP_defRectangle(0, 0, known_windows[w]->window_width, known_windows[w]->window_height);

   /*  initialize the color table
    */
   InitColorTable();

   /*  set background of the window to the desired background color 
    */
   SRGP_setColor(known_windows[w]->window_bgd_color);
   SRGP_fillRectangle(full_screen);

   /*  set current drawing color to the window foreground color 
    */
   SRGP_setColor(known_windows[w]->window_fgd_color);
   SRGP_setBackgroundColor(known_windows[w]->window_bgd_color);

   /*  draw all known gadgets on screen 
    */
   for (i = 0; i < current_gadget_count; i++) {
      switch(known_gadgets[i]->gadget_type) {
         case GSPUSHBUTTON:
            DrawPushButton(known_gadgets[i]);
            break;
         case GSTOGBUTTON:
            DrawToggleButton(known_gadgets[i]);
            break;
         case GSMENUBAR:
            DrawMenuBar(known_gadgets[i]);
            break;
         case GSSUBMENU:
            DrawSubMenu(known_gadgets[i]);
            break;
         case GSDRAWAREA:
            DrawDrawingArea(known_gadgets[i]);
            break;
         case GSTEXTGAD:

            break;
         default:
            fprintf(stderr, "GS_InitWindow: unknown gadget type found\n");
            exit(1);
      }
   }
     
   return(GSNOERROR);
} /* end of GS_InitWindow() */


/******************************************************************

  GS_CloseWindow() -- This function closes the specified window 
		after freeing all allocated memory for gadgets 
		and windows.

******************************************************************/
GS_errorType
GS_CloseWindow(GS_windowID w)
{
   FreeGadgets();
   FreeWindows();

   SRGP_end();
  
   return(GSNOERROR);
} /* end of GS_CloseWindow() */


/******************************************************************

  GS_WaitForEvent() -- This function waits for an event to occur
		and once an event occurs, it figures out which type
		of event and possibly which gadget, draw area,
		and window it occurred in.  The event structure
		of the current window is updated.

		This function returns the event type.

******************************************************************/
GS_eventType
GS_WaitForEvent()
{
   GS_eventType		event_type;
   char			keymeasure[GS_BUFLEN];
   locator_measure	locmeas;
   int 			device;
   GS_gadgetID		which_gadget;
   short int		which_menu_item;

   GS_boolean		state;


   /*  wait indefinitely for an event to occur
    */
   device = SRGP_waitEvent(INDEFINITE);

   /*  determine which type of event has occurred
    */
   switch(device) {
      case KEYBOARD:
         SRGP_getKeyboard(keymeasure, GS_BUFLEN);

         known_windows[0]->window_event->event_type = GSKEYEVENT;
         known_windows[0]->window_event->event_char = keymeasure[0];
         known_windows[0]->window_event->event_window_id = 0;

         event_type = GSKEYEVENT;
         break;

      case LOCATOR:
         SRGP_getLocator(&locmeas);

         known_windows[0]->window_event->event_loc.x = locmeas.position.x;
         known_windows[0]->window_event->event_loc.y = locmeas.position.y;

         known_windows[0]->window_event->event_button = 
					locmeas.button_of_last_transition;

         switch(locmeas.button_of_last_transition) 
         {
            case LEFT_BUTTON: 
               known_windows[0]->window_event->event_button_stat = 
					locmeas.button_chord[LEFT_BUTTON];

               if (locmeas.button_chord[LEFT_BUTTON] == DOWN) 
               {

                  which_gadget = CorrelatePick(locmeas.position);
                  known_windows[0]->window_event->event_gadget_id = 
							which_gadget;

                  if (which_gadget >= 0)	/* was a gadget picked? */
                  {
                     switch(known_gadgets[which_gadget]->gadget_type) 
                     {
                        case GSPUSHBUTTON:
                           event_type = GSMOUSEVENT;
                           break;

                        case GSTOGBUTTON:
                           event_type = GSMOUSEVENT;
                           ToggleButtonState(known_gadgets[which_gadget]);
                           DrawToggleButton(known_gadgets[which_gadget]);
                           break;

                        case GSMENUBAR:
                        case GSSUBMENU:
                           which_menu_item = CorrelateMenuItem(which_gadget, 
							locmeas.position);
                           known_windows[0]->window_event->event_menu_item = 
							which_menu_item;
                           event_type = GSMOUSEVENT;
                           break;

                        case GSDRAWAREA:
                           /* adjust to relative location of draw area */ 
                           known_windows[0]->window_event->event_loc.x = 
				known_windows[0]->window_event->event_loc.x 
		- known_gadgets[which_gadget]->gadget_extent.bottom_left.x;

                           known_windows[0]->window_event->event_loc.y = 
				known_windows[0]->window_event->event_loc.y
		- known_gadgets[which_gadget]->gadget_extent.bottom_left.y;

                           event_type = GSMOUSEVENT;
                           break;

                        case GSTEXTGAD:
                           event_type = GSNOEVENT;
                           break;

                        default:
                           event_type = GSNOEVENT;
                           break;
                     }
                  } 
                  else /* no gadget was picked */
                  {
                     event_type = GSNOEVENT;
                  }
               }

               else /* handle button up */
               {
                  which_gadget = CorrelatePick(locmeas.position);
                  known_windows[0]->window_event->event_gadget_id = which_gadget;

                  if (which_gadget >= 0)	/* was a gadget picked? */
                  {
                     switch(known_gadgets[which_gadget]->gadget_type) 
                     {
                        case GSDRAWAREA:
                           /* adjust to relative location of draw area */ 
                           known_windows[0]->window_event->event_loc.x = 
				known_windows[0]->window_event->event_loc.x 
		- known_gadgets[which_gadget]->gadget_extent.bottom_left.x;

                           known_windows[0]->window_event->event_loc.y = 
				known_windows[0]->window_event->event_loc.y
		- known_gadgets[which_gadget]->gadget_extent.bottom_left.y;

                           event_type = GSMOUSEVENT;
                           break;

                        default:
                           event_type = GSNOEVENT;
                           break;
                     }
                  } 
                  else /* no gadget was picked */
                  {
                     event_type = GSNOEVENT;
                  }
               }
               break;

            case MIDDLE_BUTTON:
               known_windows[0]->window_event->event_button_stat = 
					locmeas.button_chord[MIDDLE_BUTTON];
               event_type = GSNOEVENT;
               break;

            case RIGHT_BUTTON:
               known_windows[0]->window_event->event_button_stat = 
					locmeas.button_chord[RIGHT_BUTTON];
               event_type = GSNOEVENT;
               break;

            default:
               event_type = GSNOEVENT;
               break;
         }
         known_windows[0]->window_event->event_type = event_type;

         break;

      case NO_DEVICE:
         fprintf(stderr, "GS Error - wait for event timed out\n");
         known_windows[0]->window_event->event_type = GSNOEVENT;
         event_type = GSNOEVENT;
         break;

      default:
         known_windows[0]->window_event->event_type = GSNOEVENT;
         event_type = GSNOEVENT;
         break;
   }

   return(event_type);
} /* end of GS_WaitForEvent() */


/******************************************************************

  GS_InquireEventChar() -- This function returns the character which
		the user typed in on the keyboard device.

******************************************************************/
char
GS_InquireEventChar()
{
   return( known_windows[0]->window_event->event_char );
}


/******************************************************************

  GS_InquireEventGadgetID() -- This function returns the id of the 
		gadget which had a mouse event.

******************************************************************/
GS_gadgetID
GS_InquireEventGadgetID()
{
   return( known_windows[0]->window_event->event_gadget_id );
}


/******************************************************************

  GS_InquireEventLocation() -- This function returns the x,y 
		location of the mouse event.

******************************************************************/
point
GS_InquireEventLocation()
{
   point pt;
   
   pt.x = known_windows[0]->window_event->event_loc.x;
   pt.y = known_windows[0]->window_event->event_loc.y;

   return( pt );
}


/******************************************************************

  GS_InquireEventWhichButton() -- This function returns the which 
		button was pressed during the mouse event.

******************************************************************/
int
GS_InquireEventWhichButton()
{
   return( known_windows[0]->window_event->event_button );
}


/******************************************************************

  GS_InquireEventButtonStat() -- This function returns the button
		status of the mouse event.

******************************************************************/
int
GS_InquireEventButtonStat()
{
   return( known_windows[0]->window_event->event_button_stat );
}


/******************************************************************

  GS_InquireEventMenuItem() -- This function returns the index of the
		menu item which had a mouse event.

******************************************************************/
short int
GS_InquireEventMenuItem()
{
   return( known_windows[0]->window_event->event_menu_item );
}


/*
 *
 *  Begin private functions
 *
 */


/******************************************************************

  CorrelatePick() -- This function determines which gadget the user
		has clicked the mouse upon.

******************************************************************/
GS_gadgetID
CorrelatePick(point pt)
{
   GS_gadgetID 	gid;
   int 		i;

   gid = -1;

   for (i = 0; i < current_gadget_count; i++) {

      if (PointInBox(pt, known_gadgets[i]->gadget_extent)) {
         gid = known_gadgets[i]->gadget_id;
         break;
      }
   }

   return(gid);
} /* end of CorrelatePick() */


/******************************************************************

  CorrelateMenuItem() -- This function determines which menu item
		the user has picked.

******************************************************************/
short int
CorrelateMenuItem(GS_gadgetID gid, point pt)
{
   short int 	mit;	/* menu item ID */
   int 		i;

   mit = 0; /* TEMPORARY!!! set to first menu item */ 

   return(mit);
} /* end of CorrelateMenuItem() */


/* end of file gsevent.c */
