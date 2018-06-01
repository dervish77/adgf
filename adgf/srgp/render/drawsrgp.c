/********************************************************************

   This file contains code specific for drawing stuff on the screen
   using the SRGP graphics library.

   Author:    Brian Lingard

   File:      drawsrgp.c
 
   Revision History:
     0  3/18/95  originated

*********************************************************************/


/* include necessary files */
#include "srgp.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"
#include "shading.h"

/* #define DEBUG 1
*/

/* external globals */
extern renderType render_mode;
extern projectType projection_mode;
extern displayType display_mode;

extern vertexType vertex_list[];
extern edgeType edge_list[];
extern polygonType polygon_list[];

#ifdef DEBUG
extern FILE *debugfile;
#endif


/******************************************************************

  InitDisplayScreen() -- This function declares an SRGP screen and 
			initializes various SRGP setup stuff.

******************************************************************/
int
InitDisplayScreen()
{
   int planes_avail;	/* inquired number of planes available */
   rectangle full_screen;


/* declare visible SRGP screen */
   if (display_mode == STEREO) {
      SRGP_begin("RENDER", SCREEN_WIDTH, SCREEN_HEIGHT/2, MAX_PLANES, FALSE);

      full_screen = SRGP_defRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2);
   }
   else {
      SRGP_begin("RENDER", SCREEN_WIDTH, SCREEN_HEIGHT, MAX_PLANES, FALSE);

      full_screen = SRGP_defRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
   }

/* setup various init stuff */
   SRGP_setLocatorEchoType(CURSOR);
   SRGP_setLocatorButtonMask(LEFT_BUTTON_MASK);
   SRGP_setKeyboardProcessingMode(RAW);
   SRGP_setInputMode(KEYBOARD, EVENT);

/* if wanted full render, check if we're on color display */
   if (render_mode == FULL_REND) {
      planes_avail = SRGP_inquireCanvasDepth();

#ifdef DEBUG
      printf("planes avail = %d\n", planes_avail);
#endif

      if (planes_avail == 1) {
         render_mode == SOLD_REND;
      }
   }

/* set background of drawing area to black */
   SRGP_setColor(SRGP_BLACK);
   SRGP_fillRectangle(full_screen);

/* set current drawing color to white */
   SRGP_setColor(SRGP_WHITE);
   SRGP_setBackgroundColor(SRGP_BLACK);

   return(0);
} /* end of InitDisplayScreen() */


/******************************************************************

  CheckForQuit() -- This function waits for user input and checks 
			if the user has chosen to quit.  The function
			returns '1' when quit was chosen.
			

******************************************************************/
int
CheckForQuit()
{
   char keymeasure[BUFLEN];
   int whichdev;

   whichdev = SRGP_waitEvent(INDEFINITE);
   if (whichdev == KEYBOARD) {
     SRGP_getKeyboard(keymeasure,80);
     if ((keymeasure[0] == 'Q') || (keymeasure[0] == 'q')) return(1);
   }

   return(0);
} /* end of CheckForQuit() */


/******************************************************************

  DrawScreenBorders() -- This function draws horizontal and vertical
			lines to split the screen into four viewports. 

******************************************************************/
int
DrawScreenBorders()
{
   point left_point, right_point, top_point, bottom_point, mid_point;

   left_point = SRGP_defPoint(0, (SCREEN_HEIGHT / 2));
   right_point = SRGP_defPoint(SCREEN_WIDTH, (SCREEN_HEIGHT / 2));
   top_point = SRGP_defPoint((SCREEN_WIDTH / 2), SCREEN_HEIGHT);
   bottom_point = SRGP_defPoint((SCREEN_WIDTH / 2), 0);
   mid_point = SRGP_defPoint((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));

   if (display_mode == STEREO)		/* split screen vertically */
      SRGP_line(bottom_point, mid_point);
   else {				/* split screen both ways */
      SRGP_line(left_point, right_point);
      SRGP_line(bottom_point, top_point);
   }

   return(0);
} /* end of DrawScreenBorders */


/******************************************************************

  DrawScreenText() -- This functions labels the various viewports.

******************************************************************/
int
DrawScreenText()
{
   point xy_text_point, zy_text_point, xz_text_point, camera_point;

   xy_text_point = SRGP_defPoint(10, ((SCREEN_HEIGHT/2) + 10));
   zy_text_point = SRGP_defPoint(((SCREEN_WIDTH/2) + 10),
					 ((SCREEN_HEIGHT/2) + 10));
   xz_text_point = SRGP_defPoint(10, 10);
   camera_point = SRGP_defPoint(((SCREEN_WIDTH/2) + 10), 10);

   switch(display_mode) {
      case ALL:
         SRGP_text(xy_text_point, "xy plane");
         SRGP_text(zy_text_point, "zy plane");
         SRGP_text(xz_text_point, "xz plane");
         switch(projection_mode) {
            case PARALLEL:
               SRGP_text(camera_point, "parallel view from camera");
               break;
            case PERSPECTIVE:
               SRGP_text(camera_point, "perspective view from camera");
               break;
            default:
               SRGP_text(camera_point, "view from camera");
               break;
         }
         break;
      case ONLY_CAMERA:
         if (projection_mode == PARALLEL)
            SRGP_text(xz_text_point, "parallel view from camera");
         else
            SRGP_text(xz_text_point, "perspective view from camera");
         break;
      case STEREO:
         SRGP_text(xz_text_point, "left eye view");
         SRGP_text(camera_point, "right eye view");
         break;
      default:
         fprintf(stderr, "DrawScreenText: unknown display mode\n");
         exit(1);
   }

   return(0);
} /* end of DrawScreenText() */


/******************************************************************

  DrawAxes() -- draws coordinate axes within the camera viewport 

******************************************************************/
int
DrawAxes()
{
   point origin, x_end, y_end, z_end;
   point x_end_text, y_end_text, z_end_text;
   double x_axis_length;

   origin = SRGP_defPoint((0.75 * SCREEN_WIDTH), (0.25 * SCREEN_HEIGHT));

   x_end = SRGP_defPoint((0.95 * SCREEN_WIDTH), (0.25 * SCREEN_HEIGHT));
   y_end = SRGP_defPoint((0.75 * SCREEN_WIDTH), (0.45 * SCREEN_HEIGHT));

   x_axis_length = (0.95 * SCREEN_WIDTH) - (0.75 * SCREEN_WIDTH);
   x_axis_length = 0.707 * x_axis_length;

   z_end = SRGP_defPoint((0.75 * SCREEN_WIDTH) - x_axis_length, 
			(0.25 * SCREEN_HEIGHT) - x_axis_length);

   x_end_text = SRGP_defPoint((0.95 * SCREEN_WIDTH) + 5, 
					(0.25 * SCREEN_HEIGHT));
   y_end_text= SRGP_defPoint((0.75 * SCREEN_WIDTH), 
					(0.45 * SCREEN_HEIGHT) + 5);
   z_end_text = SRGP_defPoint((0.75 * SCREEN_WIDTH) - x_axis_length - 10, 
			(0.25 * SCREEN_HEIGHT) - x_axis_length - 10);

   SRGP_line(origin, x_end);
   SRGP_line(origin, y_end);
   SRGP_line(origin, z_end);

   SRGP_text(x_end_text, "x");
   SRGP_text(y_end_text, "y");
   SRGP_text(z_end_text, "-z");

   return(0);
} /* end of DrawAxes() */


/******************************************************************

  MapToView() -- This function maps world coordinate point to the
		viewport by applying the specified mapping transform.

		This function returns an SRGP point.

******************************************************************/
point
MapToView(vertex, mapxform)
   vertexType vertex;		/* world coordinate point */
   matrixType *mapxform;	/* world to view mapping transform */
{
   point view_p;		/* SRGP point */
   matrixType current_pt;	/* specified vertex as matrix */
   matrixType new_pt;		/* transformed vertex as matrix */

   int MultMatrix();


   /* convert specified vertex as matrix */
   current_pt.rows = 3;
   current_pt.cols = 1;
   current_pt.array[0][0] = vertex.x;
   current_pt.array[1][0] = vertex.y;
   current_pt.array[2][0] = vertex.z;	/* should always be '1' */

   /* transform world point to viewport point */
   MultMatrix(mapxform, &current_pt, &new_pt);

   /* translate into SRGP point */
   view_p = SRGP_defPoint(new_pt.array[0][0], new_pt.array[1][0]);

   return(view_p);
} /* end of MapToView() */


/******************************************************************

  DrawWorldLine() -- This function draws the specified world coordinate 
			line on the specified viewport. 

******************************************************************/
int
DrawWorldLine(startv, endv, mapxform)
   vertexType startv;
   vertexType endv;
   matrixType *mapxform;
{
   point start_p, end_p;


   /* map start and end of line to viewport coordinates */
   start_p = MapToView(startv, mapxform);
   end_p =  MapToView(endv, mapxform);

#ifdef DEBUG
   fprintf(debugfile, "drawing from %d,%d to %d,%d\n", start_p.x, start_p.y, end_p.x, end_p.y); 
#endif

   /* draw line on screen */
   SRGP_line(start_p, end_p);

   return(0);
} /* end of DrawWorldLine() */


/******************************************************************

  DrawShadedPolygon() -- This function draws a filled polygon from
		the global list if it was supposed to be visible.
		Current shading mode is constant shading for entire
		polygon.  Intensity of shading is correlated to 
		the polygon's orientation.

 	NOTE:  clipping is not handled properly!!

*******************************************************************/
int
DrawShadedPolygon(p, mapxform)
   int p;			/* polygon list index */
   matrixType *mapxform;	/* viewport mapping xform */
{
   int v;			/* vertex index */
   RGBType color;		/* polygon's actual color */
   vertexType vert;		/* temp vertex */

   point vertices[4];		/* array of polygon's vertices */

   int ComputeColor();
   int SetNewColor();


   /* draw only if this polygon is visible */
   if (polygon_list[p].visible == VISIBLE) {

      /* compute polygon's actual shading color */
      ComputeColor(p, &color);

      /* set new drawing color to computed color */
      SetNewColor(color); 

      /* build polygon vertex array */
      for (v = 0; v < polygon_list[p].num_edges; v++) {
         vert.x = vertex_list[polygon_list[p].vert_list[v]].x;
         vert.y = vertex_list[polygon_list[p].vert_list[v]].y;
         vert.z = 1.0;

         vertices[v] = MapToView(vert, mapxform);
      }

      /* draw shaded polygon */
      SRGP_fillPolygon(polygon_list[p].num_edges, &vertices[0]);

   }

   return(0);
} /* end of DrawShadedPolygon() */


/******************************************************************

  DrawPolygon() -- This function draws an unshaded polygon from
		the global list if it supposed to be visible.

******************************************************************/
int
DrawPolygon(p, map_xform)
   int p;			/* polygon list index */
   matrixType *map_xform;	/* viewport mapping xform */
{
   int e;			/* edge index */
   int accept;			/* edge accept flag */
   vertexType sv, ev;		/* start and end vertices */

   int NoClip3DEdge();


   /* draw only if this polygon is visible */
   if (polygon_list[p].visible == VISIBLE) {

      /* for all edges of this polygon */
      for (e = 0; e < polygon_list[p].num_edges; e++) {

         /* extract clipped start and end vertices */
         accept = NoClip3DEdge(polygon_list[p].edge_list[e], &sv, &ev);

         if (accept)
            DrawWorldLine(sv, ev, map_xform);
      }
   }

   return(0);
} /* end of DrawPolygon() */


/******************************************************************

  AddNewColor() -- This function adds a new color to the SRGP color table.

******************************************************************/
int
AddNewColor(index, color)
   int index;
   RGBType color;
{
   SRGP_loadColorTable(index, 1, &color.R, &color.G, &color.B);
   return(0);
} /* end of AddNewColor() */


/******************************************************************

  SetDrawColor() -- This function sets the current drawing color.

******************************************************************/
int
SetDrawColor(index)
   int index;
{
   SRGP_setColor(index);
   return(0);
} /* end of SetDrawColor() */

/* end of drawsrgp.c */
