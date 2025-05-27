/********************************************************************

   Functions for drawing within the drawing area gadget supported
   by LIBGFS, a GUI library based upon SRGP.

   Author:    Brian Lingard

   File:      gsdraw.c
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

   Functions in file:

	GS_AddNewColor
	GS_SetDrawingColor

	GS_ClearDrawArea

	GS_DefPoint
	GS_DrawPoint
	GS_DrawLine
	GS_DrawPolyline
	GS_DrawPolygon
	GS_DrawRectangle
	GS_DrawFillPolygon		- not implemented yet
	GS_DrawCircle			- not implemented yet
	GS_DrawFillCircle		- not implemented yet

	GS_InquireGadgetExtent

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

  GS_AddNewColor() -- This function adds a new color to the SRGP color table.

******************************************************************/
GS_errorType
GS_AddNewColor(GS_colorindexType index, GS_rgbType color)
{
   SRGP_loadColorTable(index, 1, &color.R, &color.G, &color.B);
   return(GSNOERROR);
} /* end of GS_AddNewColor() */


/******************************************************************

  GS_SetDrawingColor() -- This function sets the current drawing color.

******************************************************************/
GS_errorType
GS_SetDrawingColor(GS_gadgetID g, GS_colorindexType index)
{
   if (known_gadgets[g]->gadget_type == GSDRAWAREA) {
      if (known_windows[0]->window_planes_avail > 1)
      {
         known_gadgets[g]->gadget_fgd_color = index;
         SRGP_setColor(index);
      }
      else
      {
         known_gadgets[g]->gadget_fgd_color = GS_DEF_FGD_COLOR;
         SRGP_setColor(GS_DEF_FGD_COLOR);
      }
   }
   else {
      OutputErrorMsg(GSNOTDRAWAREA);
      return(GSNOTDRAWAREA);
   }

   return(GSNOERROR);
} /* end of GS_SetDrawingColor() */


/******************************************************************

  GS_ClearDrawArea() -- This function clears the specified drawing area.

******************************************************************/
GS_errorType
GS_ClearDrawArea(GS_gadgetID g)
{
   if (known_gadgets[g]->gadget_type == GSDRAWAREA)
      DrawDrawingArea(known_gadgets[g]);
   else {
      OutputErrorMsg(GSNOTDRAWAREA);
      return(GSNOTDRAWAREA);
   }

   return(GSNOERROR);
} /* end of GS_ClearDrawArea() */


/******************************************************************

  GS_DefPoint() -- This function returns a point structure from 
			specified x,y coordinates.

******************************************************************/
point
GS_DefPoint(int x, int y)
{ 
   return ( SRGP_defPoint( x, y ) );
}


/******************************************************************

  GS_DrawPoint() -- This function draws a point within the specified 
			drawing area gadget.

******************************************************************/
GS_errorType
GS_DrawPoint(GS_gadgetID g, point pt)
{ 
   point p;

   /*  offset the point to be within drawing area 
    */
   p.x = pt.x + known_gadgets[g]->gadget_extent.bottom_left.x;
   p.y = pt.y + known_gadgets[g]->gadget_extent.bottom_left.y;

   /*  check whether point is within specified drawing area
    */
   if ( PointInBox(p, known_gadgets[g]->gadget_extent) )
      SRGP_point(p);		/* draw the point */
   else {
      OutputErrorMsg(GSNOTINAREA);
      return(GSNOTINAREA);	/* return Not In Draw Area error */
   }

   return(GSNOERROR);
} /* end of GS_DrawPoint() */


/******************************************************************

  GS_DrawLine() -- This function draws a line within the specified 
			drawing area gadget.

******************************************************************/
GS_errorType
GS_DrawLine(GS_gadgetID g, point start, point end)
{
   point s, e;

   /*  offset the start and end to be within drawing area 
    */
   s.x = start.x + known_gadgets[g]->gadget_extent.bottom_left.x;
   s.y = start.y + known_gadgets[g]->gadget_extent.bottom_left.y;
   e.x = end.x + known_gadgets[g]->gadget_extent.bottom_left.x;
   e.y = end.y + known_gadgets[g]->gadget_extent.bottom_left.y;

   /*  check whether line is within specified drawing area
    */
   if (PointInBox(s, known_gadgets[g]->gadget_extent) && PointInBox(s, known_gadgets[g]->gadget_extent))
      SRGP_line(s, e);	/* draw the line */
   else {
      OutputErrorMsg(GSNOTINAREA);
      return(GSNOTINAREA);	/* return Not In Draw Area error */
   }

   return(GSNOERROR);
} /* end of GS_DrawLine() */


/******************************************************************

  GS_DrawPolyline() -- This function draws a polyline within the specified 
			drawing area gadget.

******************************************************************/
GS_errorType
GS_DrawPolyline(GS_gadgetID g, int vert_count, point *vertices)
{
   int i;
   point p_a[GS_MAX_VERTICES];

   /*  offset the vertices to be within drawing area 
    */
   for (i = 0; i < vert_count; i++)
   {
      p_a[i].x = vertices->x + known_gadgets[g]->gadget_extent.bottom_left.x;
      p_a[i].y = vertices->y + known_gadgets[g]->gadget_extent.bottom_left.y;

      vertices++;

      if ( !PointInBox(p_a[i], known_gadgets[g]->gadget_extent) )
      {
         OutputErrorMsg(GSNOTINAREA);
         return(GSNOTINAREA);	/* return Not In Draw Area error */
      }
   }

   SRGP_polyLine( vert_count, &p_a[0] );

   return(GSNOERROR);
} /* end of GS_DrawPolyline() */


/******************************************************************

  GS_DrawRectangle() -- This function draws a rectangle within the 
			specified drawing area gadget.

******************************************************************/
GS_errorType
GS_DrawRectangle(GS_gadgetID g, rectangle rect)
{
   rectangle r;

   /*  offset the rectangle to be within drawing area 
    */
   r.bottom_left.x = rect.bottom_left.x + known_gadgets[g]->gadget_extent.bottom_left.x;
   r.bottom_left.y = rect.bottom_left.y + known_gadgets[g]->gadget_extent.bottom_left.y;
   r.top_right.x = rect.top_right.x + known_gadgets[g]->gadget_extent.bottom_left.x;
   r.top_right.y = rect.top_right.y + known_gadgets[g]->gadget_extent.bottom_left.y;

   /*  check whether rectangle is within specified drawing area
    */
   if (PointInBox(r.bottom_left, known_gadgets[g]->gadget_extent) && PointInBox(r.top_right, known_gadgets[g]->gadget_extent))
      SRGP_rectangle(r);	/* draw the rectangle */
   else {
      OutputErrorMsg(GSNOTINAREA);
      return(GSNOTINAREA);	/* return Not In Draw Area error */
   }

   return(GSNOERROR);
} /* end of GS_DrawRectangle() */


/******************************************************************

  GS_DrawPolygon() -- This function draws a polygon within the specified 
			drawing area gadget.

******************************************************************/
GS_errorType
GS_DrawPolygon(GS_gadgetID g, int vert_count, point *vertices)
{
   int i;
   point p_a[GS_MAX_VERTICES];

   /*  offset the vertices to be within drawing area 
    */
   for (i = 0; i < vert_count; i++)
   {
      p_a[i].x = vertices->x + known_gadgets[g]->gadget_extent.bottom_left.x;
      p_a[i].y = vertices->y + known_gadgets[g]->gadget_extent.bottom_left.y;

      vertices++;

      if ( !PointInBox(p_a[i], known_gadgets[g]->gadget_extent) )
      {
         OutputErrorMsg(GSNOTINAREA);
         return(GSNOTINAREA);	/* return Not In Draw Area error */
      }
   }

   SRGP_polygon( vert_count, &p_a[0] );

   return(GSNOERROR);
} /* end of GS_DrawPolygon() */


/******************************************************************

  GS_InquireGadgetExtent() -- This function makes an inquiry for 
		the extent rectangle of the specified gadget.

******************************************************************/
GS_errorType
GS_InquireGadgetExtent(GS_gadgetID g, rectangle *rect)
{
   if (known_gadgets[g]->gadget_type == GSDRAWAREA) {

      rect->bottom_left.x = known_gadgets[g]->gadget_extent.bottom_left.x;
      rect->bottom_left.y = known_gadgets[g]->gadget_extent.bottom_left.y;
      rect->top_right.x = known_gadgets[g]->gadget_extent.top_right.x;
      rect->top_right.y = known_gadgets[g]->gadget_extent.top_right.y;
   }
   else {
      OutputErrorMsg(GSNOTDRAWAREA);
      return(GSNOTDRAWAREA);
   }

   return(GSNOERROR);
} /* end of GS_InquireGadgetExtent() */


/* end of file gsdraw.c */
