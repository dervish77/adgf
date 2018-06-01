/********************************************************************

   This file contains private code specific for use by other LIBGFS
   functions.  LIBGFS is based upon SRGP.

   Author:    Brian Lingard

   File:      gsprivat.c
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

   Functions in file:

	ComputeGadgetExtent
	ComputeGadgetCenter
	ComputeMaxTextWHD

	DrawPushButton
	DrawToggleButton
	DrawMenuBar
	DrawSubMenu
	DrawDrawingArea
	DrawTextGadget		- not implemented yet

	ToggleButtonState
	PointInBox
	ExtractItemLabel
	InitColorTable
	OutputGadget

	FreeGadgets
	FreeWindows
	OutputErrorMsg
	ParseString

*********************************************************************/


/* include necessary files */
#ifndef GSPRIVAT_H
#include "gsprivat.h"
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>



/*  declare private global variables 
 */
GS_gadgetID current_gadget_count=0;
GS_windowID current_window_count=0;

GSgadgetStruct *known_gadgets[GS_MAX_GADGETS];
GSwindowStruct *known_windows[GS_MAX_WINDOWS];

GS_errorMsgType error_strings[GSNOTDRAWAREA + 1] = 
			{ "GS no error                   ",
			  "GS error - not in draw area   ",
			  "GS error - gadget error       ",
			  "GS error - not button error   ",
			  "GS error - not menu bar error ",
			  "GS error - not sub menu error ",
			  "GS error - not draw area error" };


#ifdef GS_DEBUG
   FILE *gs_debug_file;
#endif



/*
 *
 *  Begin private functions
 *
 */

/******************************************************************

  ComputeGadgetExtent() -- This function computes the extent 
			rectangle of any gadget.

******************************************************************/
GS_errorType
ComputeGadgetExtent(GSgadgetStruct *b)
{

   /*  calculate extent depending on location type
    */
   switch(b->gadget_loc_type) {
      case GSCENTERED:
         b->gadget_extent.bottom_left.x = b->gadget_xloc - (b->gadget_width / 2);
         b->gadget_extent.bottom_left.y = b->gadget_yloc - (b->gadget_height / 2);
         b->gadget_extent.top_right.x = b->gadget_xloc + (b->gadget_width / 2);
         b->gadget_extent.top_right.y = b->gadget_yloc + (b->gadget_height / 2);
         break;

      case GSTOPLEFT:
         b->gadget_extent.bottom_left.x = b->gadget_xloc;
         b->gadget_extent.bottom_left.y = b->gadget_yloc - b->gadget_height;
         b->gadget_extent.top_right.x = b->gadget_xloc + b->gadget_width;
         b->gadget_extent.top_right.y = b->gadget_yloc;
         break;

      case GSBOTLEFT:
         b->gadget_extent.bottom_left.x = b->gadget_xloc;
         b->gadget_extent.bottom_left.y = b->gadget_yloc;
         b->gadget_extent.top_right.x = b->gadget_xloc + b->gadget_width;
         b->gadget_extent.top_right.y = b->gadget_yloc + b->gadget_height;
         break;

      case GSTOPRIGHT:
         b->gadget_extent.bottom_left.x = b->gadget_xloc - b->gadget_width;
         b->gadget_extent.bottom_left.y = b->gadget_yloc - b->gadget_height;
         b->gadget_extent.top_right.x = b->gadget_xloc;
         b->gadget_extent.top_right.y = b->gadget_yloc;
         break;

      case GSBOTRIGHT:
         b->gadget_extent.bottom_left.x = b->gadget_xloc - b->gadget_width;
         b->gadget_extent.bottom_left.y = b->gadget_yloc;
         b->gadget_extent.top_right.x = b->gadget_xloc;
         b->gadget_extent.top_right.y = b->gadget_yloc + b->gadget_height;
         break;

      default:
         fprintf(stderr, "ComputeGadgetExtent: unknown loc type\n");
         exit(1);
   }


   return(GSNOERROR);
} /* end of ComputeGadgetExtent()*/


/******************************************************************

  ComputeGadgetCenter() -- This function computes the center of 
			any gadget.  Assumes the extent has already
			been computed.

******************************************************************/
GS_errorType
ComputeGadgetCenter(GSgadgetStruct *b)
{
   long int dx, dy;

   dx = b->gadget_extent.top_right.x - b->gadget_extent.bottom_left.x;
   dy = b->gadget_extent.top_right.y - b->gadget_extent.bottom_left.y;

   b->gadget_center.x = b->gadget_extent.bottom_left.x + (dx / 2);
   b->gadget_center.y = b->gadget_extent.bottom_left.y + (dy / 2);

   return(GSNOERROR);
} /* end of ComputeGadgetCenter() */


/******************************************************************

  ComputeMaxTextWHD() -- This function computes the maximum text width,
		height and descent of a list of text labels.

******************************************************************/
GS_errorType
ComputeMaxTextWHD(short int count, char *item_list, int *mxtw, int *mxth, int *mxtd)
{
   int i, tw, th, td, max_tw=0, max_th=0, max_td=0;
   char *current_item;

 
   for (i = 0; i < count; i++) {

      ExtractItemLabel(i, item_list, current_item);

      SRGP_inquireTextExtent(current_item, &tw, &th, &td);

      if (tw > max_tw) max_tw = tw;

      if (th > max_th) max_th = th;
  
      if (td > max_td) max_td = td;

   }

   *mxtw = max_tw;
   *mxth = max_th;
   *mxtd = max_td;

   return(GSNOERROR);
} /* end of ComputeMaxTextWHD() */


/******************************************************************

  DrawPushButton() -- This function draws the specified push 
		button gadget.

******************************************************************/
GS_errorType
DrawPushButton(GSgadgetStruct *bg)
{
   if (bg->gadget_type == GSPUSHBUTTON) {

      /*  draw background of button 
       */
      SRGP_setColor(bg->gadget_bgd_color);
      SRGP_fillRectangle(bg->gadget_extent);

      /*  draw outline of button
       */
      SRGP_setColor(bg->gadget_bor_color);
      SRGP_rectangle(bg->gadget_extent);

      /*  draw label of button
       */
      SRGP_setColor(bg->gadget_fgd_color);
      SRGP_text(bg->button->label_pos, bg->button->label);
   }
   else
      return(GSNOTBUTTONERR);

   return(GSNOERROR);
} /* end of DrawPushButton() */


/******************************************************************

  DrawToggleButton() -- This function draws the specified toggle 
		button gadget.

******************************************************************/
GS_errorType
DrawToggleButton(GSgadgetStruct *bg)
{
   if (bg->gadget_type == GSTOGBUTTON) {

      switch(bg->togbutton->shape)
      {
         case GSTOGSQUARE:
            if (bg->togbutton->state == FALSE)
            {
               /*  draw background of button 
                */
               SRGP_setColor(bg->gadget_bgd_color);
               SRGP_fillRectangle(bg->togbutton->square);

               /*  draw outline of button
                */
               SRGP_setColor(bg->gadget_bor_color);
               SRGP_rectangle(bg->togbutton->square);
            }
            else
            {
               /*  draw background of button 
                */
               SRGP_setColor(bg->gadget_bor_color);
               SRGP_fillRectangle(bg->togbutton->square);

               /*  draw outline of button
                */
               SRGP_setColor(bg->gadget_bgd_color);
               SRGP_rectangle(bg->togbutton->square);
            }
            break;
         case GSTOGDIAMOND:
            break;
         case GSTOGCIRCLE:
            break;
         default:
            break;
      }

      /*  draw label of button
       */
      SRGP_setColor(bg->gadget_fgd_color);
      SRGP_text(bg->togbutton->label_pos, bg->togbutton->label);
   }
   else
      return(GSNOTBUTTONERR);

   return(GSNOERROR);
} /* end of DrawToggleButton() */


/******************************************************************

  DrawMenuBar() -- This function draws the specified menu bar gadget.

******************************************************************/
GS_errorType
DrawMenuBar(GSgadgetStruct *mb)
{
   int 	i;
   char *item_label;

   GS_errorType ExtractItemLabel();


   if (mb->gadget_type == GSMENUBAR) {

      /*  draw background of menu bar 
       */
      SRGP_setColor(mb->gadget_bgd_color);
      SRGP_fillRectangle(mb->gadget_extent);

      /*  draw outline of menu bar
       */
      SRGP_setColor(mb->gadget_bor_color);
      SRGP_rectangle(mb->gadget_extent);

      /*  draw menu labels of menu bar
       */
      SRGP_setColor(mb->gadget_fgd_color);

      for (i = 0; i < mb->menubar->item_count; i++) {
         ExtractItemLabel(i, mb->menubar->item_list, item_label);
         SRGP_text(mb->menubar->item_pos[i], item_label);
      }
   }
   else
      return(GSNOTMENUBARERR);

   return(GSNOERROR);
} /* end of DrawMenuBar()*/


/******************************************************************

  DrawSubMenu() -- This function draws the specified submenu gadget.

******************************************************************/
GS_errorType
DrawSubMenu(GSgadgetStruct *sm)
{
   int 	i;
   char *item_label;

   GS_errorType ExtractItemLabel();


   if (sm->gadget_type == GSSUBMENU) {

      /*  draw background of sub menu
       */
      SRGP_setColor(sm->gadget_bgd_color);
      SRGP_fillRectangle(sm->gadget_extent);

      /*  draw outline of sub menu
       */
      SRGP_setColor(sm->gadget_bor_color);
      SRGP_rectangle(sm->gadget_extent);

      /*  draw menu labels of sub menu
       */
      SRGP_setColor(sm->gadget_fgd_color);

      for (i = 0; i < sm->submenu->item_count; i++) {
         ExtractItemLabel(i, sm->submenu->item_list, item_label);
         SRGP_text(sm->submenu->item_pos[i], item_label);
      }
   }
   else
      return(GSNOTSUBMENUERR);

   return(GSNOERROR);
} /* end of DrawSubMenu()*/


/******************************************************************

  DrawDrawingArea() -- This function draws the specified drawing area.

******************************************************************/
GS_errorType
DrawDrawingArea(GSgadgetStruct *area)
{

   if (area->gadget_type == GSDRAWAREA) {

      /*  draw background of drawing area
       */
      SRGP_setColor(area->gadget_bgd_color);
      SRGP_fillRectangle(area->gadget_extent);

      /*  draw outline of drawing area
       */
      SRGP_setColor(area->gadget_bor_color);
      SRGP_rectangle(area->gadget_extent);

      /*  reset drawing color back to foreground color
       */
      SRGP_setColor(area->gadget_fgd_color);
   }
   else
      return(GSNOTDRAWAREA);

   return(GSNOERROR);
} /* end of DrawDrawingArea()*/


/******************************************************************

  DrawTextGadget() -- This function draws the specified text gadget.

******************************************************************/
GS_errorType
DrawTextGadget(GSgadgetStruct *tg)
{

   return(GSNOERROR);
}


/******************************************************************

  ToggleButtonState() -- This function toggle's a toggle button state.

******************************************************************/
GS_errorType
ToggleButtonState(GSgadgetStruct *tb)
{
   tb->togbutton->state = TOGGLE_STATE(tb->togbutton->state);
   return(GSNOERROR);
}


/******************************************************************

  PointInBox() -- This function determines if a point is within the 
		bounding rectangle.

******************************************************************/
short int
PointInBox(point p, rectangle r)
{
   if ((p.x < r.bottom_left.x) || (r.top_right.x < p.x))
      return(GS_NOTINBOX);

   if ((p.y < r.bottom_left.y) || (r.top_right.y < p.y))
      return(GS_NOTINBOX);

   return(GS_INBOX);
} /* end of PointInBox() */


/******************************************************************

  ExtractItemLabel() -- This function extracts a menu item label
		from a space delimited list of labels.

******************************************************************/
GS_errorType
ExtractItemLabel(int which, char *item_list, char *item_label)
{
   int count;
   char *list_array[GS_MAX_ITEM_COUNT];

   count = ParseString(item_list, list_array);

   if (which <= count)
      item_label = &list_array[which][0];
   else
      item_label = (char *) NULL;

   return(GSNOERROR);
} /* end of ExtractItemLabel() */


/******************************************************************

  InitColorTable() -- This function initializes the SRGP color table
		with some default color values.

******************************************************************/
GS_errorType
InitColorTable()
{
   GS_colorType		ct[9];
   GS_rgbType 		usht[9];

   int i;

   /*  set the intensities of each color component
    */
   ct[GSRED].IR = 1.0;     ct[GSRED].IG = 0.0;     ct[GSRED].IB = 0.0;
   ct[GSGREEN].IR = 0.0;   ct[GSGREEN].IG = 1.0;   ct[GSGREEN].IB = 0.0;
   ct[GSBLUE].IR = 0.0;    ct[GSBLUE].IG = 0.0;    ct[GSBLUE].IB = 1.0;
   ct[GSCYAN].IR = 0.0;    ct[GSCYAN].IG = 1.0;    ct[GSCYAN].IB = 1.0;
   ct[GSMAGENTA].IR = 1.0; ct[GSMAGENTA].IG = 0.0; ct[GSMAGENTA].IB = 1.0;
   ct[GSYELLOW].IR = 1.0;  ct[GSYELLOW].IG = 1.0;  ct[GSYELLOW].IB = 0.0;
   ct[GSGREY].IR = 0.7;    ct[GSGREY].IG = 0.7;    ct[GSGREY].IB = 0.7;

   /*  convert to integer values and load SRGP color table
    */
   for (i = GSRED; i < 9; i++) {
      usht[i].R = (ush) (GSMAXGREYLEVEL * ct[i].IR);
      usht[i].G = (ush) (GSMAXGREYLEVEL * ct[i].IG);
      usht[i].B = (ush) (GSMAXGREYLEVEL * ct[i].IB);

      SRGP_loadColorTable(i, 1, &usht[i].R, &usht[i].G, &usht[i].B);
   }
 
   return(GSNOERROR);
} /* end of InitColorTable() */


/******************************************************************

  OutputGadget() -- This function outputs the specified gadget's data
		to the specified file pointer.

******************************************************************/
GS_errorType
OutputGadget(FILE *file, GSgadgetStruct *g)
{
   fprintf(file, "Gadget data:\n");
   fprintf(file, "  id = %d\n", g->gadget_id);
   fprintf(file, "  type = %d\n", g->gadget_type);
   fprintf(file, "  width = %d\n", g->gadget_width);
   fprintf(file, "  height = %d\n", g->gadget_height);
   fprintf(file, "  xloc = %d\n", g->gadget_xloc);
   fprintf(file, "  yloc = %d\n", g->gadget_yloc);
   fprintf(file, "  loc type = %d\n", g->gadget_loc_type);
   fprintf(file, "  bor color = %d\n", g->gadget_bor_color);
   fprintf(file, "  bgd color = %d\n", g->gadget_bgd_color);
   fprintf(file, "  fgd color = %d\n", g->gadget_fgd_color);
   fprintf(file, "  high color = %d\n", g->gadget_high_color);
   fprintf(file, "  extent bot left.x = %d\n", g->gadget_extent.bottom_left.x);
   fprintf(file, "  extent bot left.y = %d\n", g->gadget_extent.bottom_left.y);
   fprintf(file, "  extent top right.x = %d\n", g->gadget_extent.top_right.x);
   fprintf(file, "  extent top right.y = %d\n", g->gadget_extent.top_right.y);
   fprintf(file, "  center x,y = %d,%d\n", g->gadget_center.x, g->gadget_center.y);

   switch(g->gadget_type) {
      case GSPUSHBUTTON:
         fprintf(file, "  label = %s\n", g->button->label);
         fprintf(file, "  label_pos x,y = %d,%d\n", g->button->label_pos.x, g->button->label_pos.y);
         break;
      case GSTOGBUTTON:
         fprintf(file, "  label = %s\n", g->togbutton->label);
         fprintf(file, "  label_pos x,y = %d,%d\n", g->togbutton->label_pos.x, g->togbutton->label_pos.y);
         break;
      case GSMENUBAR:
         fprintf(file, "  item count = %d\n", g->menubar->item_count);
         break;
      case GSSUBMENU:
         fprintf(file, "  item count = %d\n", g->submenu->item_count);
         break;
      case GSTEXTGAD:
         fprintf(file, "  num chars = %d\n", g->textgad->num_chars);
         fprintf(file, "  string = %s\n", g->textgad->string);
         break;
      default:
         break;
   }
   return(GSNOERROR);
} /* end of OutputGadget() */


/******************************************************************

  FreeGadgets() -- This function deallocates all known gadgets.

******************************************************************/
GS_errorType
FreeGadgets()
{
   int i;
   
   for (i = 0; i < current_gadget_count; i++)
   {
      switch(known_gadgets[i]->gadget_type)
      {
         case GSPUSHBUTTON:
         case GSTOGBUTTON:
            free(known_gadgets[i]->button);
            break;

         case GSMENUBAR:
            free(known_gadgets[i]->menubar->item_pos);
            free(known_gadgets[i]->menubar->item_rect);
            free(known_gadgets[i]->menubar);
            break;

         case GSSUBMENU:
            free(known_gadgets[i]->submenu->item_pos);
            free(known_gadgets[i]->submenu->item_rect);
            free(known_gadgets[i]->submenu);
            break;

         case GSDRAWAREA:
            break;

         case GSTEXTGAD:
            free(known_gadgets[i]->textgad->string);
            free(known_gadgets[i]->textgad);
            break;

         default:
            break;
      }

      free(known_gadgets[i]);
   }

   return(GSNOERROR);
} /* end of FreeGadgets() */


/******************************************************************

  FreeWindows() -- This function deallocates all known windows.

******************************************************************/
GS_errorType
FreeWindows()
{
   int i;
   
   for (i = 0; i < current_window_count; i++) 
   {
      free(known_windows[i]->window_event);	/* free event structure */
      free(known_windows[i]);			/* free window itself */
   }

   return(GSNOERROR);
} /* end of FreeWindows() */


/******************************************************************

  OutputErrorMsg() -- This function outputs an error msg to stderr.

******************************************************************/
GS_errorType 
OutputErrorMsg(GS_errorType type)
{
   fprintf( stderr, "%s\n", error_strings[type] );

   return(GSNOERROR);
} /* end of OutputErrorMsg() */


/*****************************************************************
*  ParseString - parses list of strings into array of strings    *
******************************************************************/
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */

/* end of file gsprivat.c */
