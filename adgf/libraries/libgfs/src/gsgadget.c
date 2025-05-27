/********************************************************************

   Functions for making the various gadgets supported by LIBGFS, 
   a GUI library based upon SRGP.

   Author:    Brian Lingard

   File:      gsgadget.c
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

   Functions in file:

	GS_MakePushButton
	GS_MakeToggleButton
	GS_MakeMenuBar
	GS_MakeSubMenu		- not implemented yet
	GS_MakeDrawArea
	GS_MakeTextGadget	- not implemented yet
	GS_MakeWindow

	GS_SetToggleState
	GS_GetToggleState

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

  GS_MakePushButton() -- This function creates a labeled push button
	gadget and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakePushButton(char *label,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color)
{
   GSgadgetStruct 	*bg;
   GSbutton		*button;

   int 	i;

   int 	label_width=0, label_height=0, label_descent=0;


   /*  allocate memory for new gadget structure 
    */
   bg = (GSgadgetStruct *) calloc(1, sizeof(GSgadgetStruct));
   if (bg == (GSgadgetStruct *) NULL) {
      fprintf(stderr, "GS_MakePushButton: could not allocate new gadget\n");
      exit(1);
   }

   /*  save pointer in known gadgets array 
    */
   known_gadgets[current_gadget_count] = bg;

   /*  fill in gadget id and gadget type 
    */
   bg->gadget_id = current_gadget_count++;
   bg->gadget_type = GSPUSHBUTTON;

   if (current_gadget_count > GS_MAX_GADGETS) {
      fprintf(stderr, "GS_MakePushButton: exceeded max number of gadgets\n");
      exit(1);
   }

   /*  fill in width, height, x and y locations, and location type
    */
   bg->gadget_width = width;
   bg->gadget_height = height;
   bg->gadget_xloc = xloc;
   bg->gadget_yloc = yloc;
   bg->gadget_loc_type = loc_type;

   /*  fill in gadget color attributes 
    */
   bg->gadget_bor_color = bor_color;
   bg->gadget_bgd_color = bgd_color;
   bg->gadget_fgd_color = text_color;
   bg->gadget_high_color = text_color;

   /*  allocate memory for button structure 
    */
   button = (GSbutton *) calloc(1, sizeof(GSbutton));
   if (button == (GSbutton *) NULL) {
      fprintf(stderr, "GS_MakePushButton: could not allocate new button\n");
      exit(1);
   }
   bg->button = button;		/* save pointer to button structure */

   /*  save pointer to button label 
    */
   bg->button->label = label;

   /*  compute button extent and fill in button extent 
    */
   ComputeGadgetExtent(bg);
   ComputeGadgetCenter(bg);

   /*  compute label position 
    */
   SRGP_inquireTextExtent(label, &label_width, &label_height, &label_descent);

   bg->button->label_pos.x = bg->gadget_center.x - (label_width / 2);
   bg->button->label_pos.y = bg->gadget_center.y - (label_height / 2);

#ifdef GS_DEBUG
   OutputGadget(gs_debug_file, bg);
#endif

   return(bg->gadget_id);
} /* end of GS_MakePushButton() */


/******************************************************************

  GS_MakeToggleButton() -- This function creates a labeled toggle button
	gadget and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakeToggleButton(char *label,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color,
			short int toggle_shape)
{
   GSgadgetStruct 	*bg;
   GStogbutton		*togbutton;

   int 	i;

   int 	label_width=0, label_height=0, label_descent=0;


   /*  allocate memory for new gadget structure 
    */
   bg = (GSgadgetStruct *) calloc(1, sizeof(GSgadgetStruct));
   if (bg == (GSgadgetStruct *) NULL) {
      fprintf(stderr, "GS_MakeToggleButton: could not allocate new gadget\n");
      exit(1);
   }

   /*  save pointer in known gadgets array 
    */
   known_gadgets[current_gadget_count] = bg;

   /*  fill in gadget id and gadget type 
    */
   bg->gadget_id = current_gadget_count++;
   bg->gadget_type = GSTOGBUTTON;

   if (current_gadget_count > GS_MAX_GADGETS) {
      fprintf(stderr, "GS_MakeToggleButton: exceeded max number of gadgets\n");
      exit(1);
   }

   /*  fill in width, height, x and y locations, and location type
    */
   bg->gadget_width = width;
   bg->gadget_height = height;
   bg->gadget_xloc = xloc;
   bg->gadget_yloc = yloc;
   bg->gadget_loc_type = loc_type;

   /*  fill in gadget color attributes 
    */
   bg->gadget_bor_color = bor_color;
   bg->gadget_bgd_color = bgd_color;
   bg->gadget_fgd_color = text_color;
   bg->gadget_high_color = text_color;

   /*  allocate memory for toggle button structure 
    */
   togbutton = (GStogbutton *) calloc(1, sizeof(GStogbutton));
   if (togbutton == (GStogbutton *) NULL) {
      fprintf(stderr, "GS_MakeToggleButton: could not allocate new button\n");
      exit(1);
   }
   bg->togbutton = togbutton;	/* save pointer to toggle button structure */

   /*  init state to false
    */
   bg->togbutton->state = GSFALSE;

   /*  save pointer to button label 
    */
   bg->togbutton->label = label;

   /*  save toggle button shape 
    */
   bg->togbutton->shape = toggle_shape;

   /*  compute button extent and fill in button extent 
    */
   ComputeGadgetExtent(bg);
   ComputeGadgetCenter(bg);

   /*  compute label position 
    */
   SRGP_inquireTextExtent(label, &label_width, &label_height, &label_descent);

   bg->togbutton->label_pos.x = bg->gadget_center.x - (label_width / 8);
   bg->togbutton->label_pos.y = bg->gadget_center.y - (label_height / 2);

   /*  compute toggle button's shape parameters
    */
   switch(bg->togbutton->shape)
   {
      case GSTOGSQUARE:
         bg->togbutton->square.bottom_left.x = bg->gadget_extent.bottom_left.x;
         bg->togbutton->square.bottom_left.y = bg->gadget_extent.bottom_left.y;
         bg->togbutton->square.top_right.x = bg->togbutton->square.bottom_left.x + (bg->gadget_extent.top_right.y - bg->gadget_extent.bottom_left.y);
         bg->togbutton->square.top_right.y = bg->gadget_extent.top_right.y;
         break;
      case GSTOGDIAMOND:
         break;
      case GSTOGCIRCLE:
         break;
      default:
         break;
   }

#ifdef GS_DEBUG
   OutputGadget(gs_debug_file, bg);
#endif

   return(bg->gadget_id);
} /* end of GS_MakeToggleButton() */


/******************************************************************

  GS_MakeMenuBar() -- This function creates a menu bar
	gadget and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakeMenuBar(short int item_count,
			char *item_list,
			GS_gadgetID *submenu_list,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color)
{
   GSgadgetStruct 	*mb;
   GSmenubar		*menubar;
   point		*tpos;		/* array of text positions */
   rectangle		*trect;		/* array of item bounding rects */

   int max_tw, max_th, max_td;		/* max text width, height, descent */
   int delta_mbx;
   int tspx = 20, tx = 5, ty = 5;
   point rect_bl;
   int i;


   /*  allocate memory for new gadget structure 
    */
   mb = (GSgadgetStruct *) calloc(1, sizeof(GSgadgetStruct));
   if (mb == (GSgadgetStruct *) NULL) {
      fprintf(stderr, "GS_MakeMenuBar: could not allocate new gadget\n");
      exit(1);
   }

   /*  save pointer in known gadgets array 
    */
   known_gadgets[current_gadget_count] = mb;

   /*  fill in gadget id and gadget type 
    */
   mb->gadget_id = current_gadget_count++;
   mb->gadget_type = GSMENUBAR;

   if (current_gadget_count > GS_MAX_GADGETS) {
      fprintf(stderr, "GS_MakeMenuBar: exceeded max number of gadgets\n");
      exit(1);
   }

   /*  fill in width, height, x and y locations, and location type 
    */
   mb->gadget_width = width;
   mb->gadget_height = height;
   mb->gadget_xloc = xloc;
   mb->gadget_yloc = yloc;
   mb->gadget_loc_type = loc_type;

   /*  fill in gadget color attributes 
    */
   mb->gadget_bor_color = bor_color;
   mb->gadget_bgd_color = bgd_color;
   mb->gadget_fgd_color = text_color;
   mb->gadget_high_color = text_color;

   /*  allocate memory for new menu bar structure 
    */
   menubar = (GSmenubar *) calloc(1, sizeof(GSmenubar));
   if (menubar == (GSmenubar *) NULL) {
      fprintf(stderr, "GS_MakeMenuBar: could not allocate new menubar\n");
      exit(1);
   }
   mb->menubar = menubar;	/* save pointer to menu bar structure */

   /*  fill in menu item count, menu item list array, and IDs of submenus
    */
   mb->menubar->item_count = item_count;
   mb->menubar->item_list = item_list;
   mb->menubar->submenu_ids = submenu_list;

   /*  compute menu bar extent and center  
    */
   ComputeGadgetExtent(mb);
   ComputeGadgetCenter(mb);

   /*  allocate memory for array of points
    */
   tpos = (point *) calloc(item_count, sizeof(point));
   if (tpos == (point *) NULL) {
      fprintf(stderr, "GS_MakeMenuBar: could not allocate point array\n");
      exit(1);
   }
   mb->menubar->item_pos = tpos;

   /*  allocate memory for array of rectangles
    */
   trect = (rectangle *) calloc(item_count, sizeof(rectangle));
   if (trect == (rectangle *) NULL) {
      fprintf(stderr, "GS_MakeMenuBar: could not allocate rectangle array\n");
      exit(1);
   }
   mb->menubar->item_rect = trect;

   /*  compute max text width, height, and descent
    */
   ComputeMaxTextWHD(item_count, item_list, &max_tw, &max_th, &max_td);

   /*  compute bounding rectangles for each item  
    */
   delta_mbx = max_tw + tspx;

   rect_bl.x = mb->gadget_extent.bottom_left.x;
   rect_bl.y = mb->gadget_extent.bottom_left.y;

   for (i = 0; i < item_count; i++) {

      mb->menubar->item_rect[i].bottom_left.x = rect_bl.x;
      mb->menubar->item_rect[i].bottom_left.y = rect_bl.y;

      mb->menubar->item_rect[i].top_right.x = rect_bl.x + delta_mbx;
      mb->menubar->item_rect[i].top_right.y = rect_bl.y + mb->gadget_height;

      rect_bl.x += delta_mbx;
   }

   /*  compute text positions for each item
    */
   for (i = 0; i < item_count; i++) {

      mb->menubar->item_pos[i].x = mb->menubar->item_rect[i].bottom_left.x + tx;
      mb->menubar->item_pos[i].y = mb->menubar->item_rect[i].bottom_left.y + ty;

   }

#ifdef GS_DEBUG
   OutputGadget(gs_debug_file, mb);
#endif

   return(mb->gadget_id);
} /* end of GS_MakeMenuBar() */


/******************************************************************

  GS_MakeSubMenu() -- This function creates a sub menu gadget
	and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakeSubMenu( )
{
   GSgadgetStruct *sbm;



   return(sbm->gadget_id);
}


/******************************************************************

  GS_MakeDrawArea() -- This function creates a drawing area gadget
	and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakeDrawArea( long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int fgd_color)	/* drawing color */
{
   GSgadgetStruct *area;


   /*  allocate memory for new drawing area gadget 
    */
   area = (GSgadgetStruct *) calloc(1, sizeof(GSgadgetStruct));
   if (area == (GSgadgetStruct *) NULL) {
      fprintf(stderr, "GS_MakeDrawArea: could not allocate new gadget\n");
      exit(1);
   }

   /*  save pointer in known gadgets array 
    */
   known_gadgets[current_gadget_count] = area;

   /*  fill in draw area id 
    */
   area->gadget_id = current_gadget_count++;
   area->gadget_type = GSDRAWAREA;

   if (current_gadget_count > GS_MAX_GADGETS) {
      fprintf(stderr, "GS_MakeDrawArea: exceeded max number of gadgets\n");
      exit(1);
   }

   /*  fill in width, height, x and y locations, and location type 
    */
   area->gadget_width = width;
   area->gadget_height = height;
   area->gadget_xloc = xloc;
   area->gadget_yloc = yloc;
   area->gadget_loc_type = loc_type;

   /*  fill in draw area color attributes 
    */
   area->gadget_bor_color = bor_color;
   area->gadget_bgd_color = bgd_color;
   area->gadget_fgd_color = fgd_color;
   area->gadget_high_color = fgd_color;

   /*  compute drawing area extent rectangle 
    */
   ComputeGadgetExtent(area);

#ifdef GS_DEBUG
   OutputGadget(gs_debug_file, area);
#endif

   return(area->gadget_id);
} /* end of GS_MakeDrawArea() */


/******************************************************************

  GS_MakeTextGadget() -- This function creates a text gadget
	and returns the ID of the gadget.

******************************************************************/
GS_gadgetID
GS_MakeTextGadget( )
{
   GSgadgetStruct *tg;



   return(tg->gadget_id);
}


/******************************************************************

  GS_MakeWindow() -- This function creates a window and returns the 
			ID of the window.  This function also must be
			the first function called by the application
			before creating gadgets.

******************************************************************/
GS_windowID
GS_MakeWindow( char *name,
			long int width,
			long int height,
			short int num_planes,
			short int bgd_color,
			short int fgd_color)
{
   GSwindowStruct *win;


   /*  allocate memory for new window structure 
    */
   win = (GSwindowStruct *) calloc(1, sizeof(GSwindowStruct));
   if (win == (GSwindowStruct *) NULL) {
      fprintf(stderr, "GS_MakeWindow: could not allocate new window\n");
      exit(1);
   }

   /*  save pointer in known windows array 
    */
   known_windows[current_window_count] = win;

   /*  fill in window id 
    */
   win->window_id = current_window_count++;

   if (current_window_count > GS_MAX_WINDOWS) {
      fprintf(stderr, "GS_MakeWindow: exceeded max number of windows\n");
      exit(1);
   }

   /*  fill in name, width, height, and number of planes 
    */
   win->window_name = name;
   win->window_width = width;
   win->window_height = height;
   win->window_num_planes = 0;
//   win->window_num_planes = num_planes;

   /*  fill in window color attributes 
    */
   win->window_bgd_color = bgd_color;
   win->window_fgd_color = fgd_color;


   /*  allocate memory for event structure and save in window structure
    */
   win->window_event = (GSeventStruct *) calloc(1, sizeof(GSeventStruct));
   if (win->window_event == (GSeventStruct *) NULL) {
      fprintf(stderr, "GS_MakeWindow: could not allocate event structure\n");
      exit(1);
   }
 
   /*  open up a debug file if debug is enabled
    */
#ifdef GS_DEBUG
   gs_debug_file = fopen("gsdebug.log", "w");
   if (gs_debug_file == (FILE *) NULL) {
      fprintf(stderr, "GS_MakeWindow: could not open debug file\n");
      exit(1);
   }
#endif

   /*  declare visible SRGP screen 
    */
   SRGP_begin(  known_windows[win->window_id]->window_name, 
	        known_windows[win->window_id]->window_width, 
		known_windows[win->window_id]->window_height, 
		known_windows[win->window_id]->window_num_planes, 
		FALSE);

   /*  setup various init stuff 
    */
   SRGP_setLocatorEchoType(CURSOR);
   SRGP_setLocatorButtonMask(LEFT_BUTTON_MASK);
   SRGP_setKeyboardProcessingMode(RAW);
   SRGP_setInputMode(KEYBOARD, EVENT);
   SRGP_setInputMode(LOCATOR, EVENT);

   /*  check for how many planes we got 
    */
   known_windows[win->window_id]->window_planes_avail = 
					SRGP_inquireCanvasDepth();


   return( win->window_id );
} /* end of GS_MakeWindow() */


/******************************************************************

  GS_SetToggleState() -- This function sets a toggle button gadget 
			state to the value of 'state', and redraws 
			the toggle button.

******************************************************************/
GS_errorType 
GS_SetToggleState(GS_gadgetID g, GS_boolean state)
{
   known_gadgets[g]->togbutton->state = state;

   return( DrawToggleButton( known_gadgets[g] ) );
}


/******************************************************************

  GS_GetToggleState() -- This function returns the specified toggle
			button gadget's state.

******************************************************************/
GS_boolean
GS_GetToggleState(GS_gadgetID g)
{
   return( known_gadgets[g]->togbutton->state );
}


/* end of file gsgadget.c */
