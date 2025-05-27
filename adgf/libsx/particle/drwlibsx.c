/***********************************************************************

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	9/18/95

  Drawing related functions using the LIBSX library.

***********************************************************************/



/* include necessary files */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

#ifndef _CALLBACK_H
#include "callback.h"          /* prototypes for callback functions       */
#endif


#define GREY2INTENSITY(g)	(( ((float) g) / 255.0) * 1.0)

#define INTENSITY2GREY(i)	((int) (i * 255))


/*  extern necessary function calls 
 */
extern pointType MapToView(wpointType vertex, matrixType *mapxform);

extern Widget drawarea_widget;


/*  declare static globals
 */
static COLORMAP_S_T colormap;	/* local color map structure */

static int current_color_index;



/******************************************************************************
*  ClearScreenDisplay - clears all currently drawn viewports                  *
******************************************************************************/
void
ClearScreenDisplay()
{
   int x, y;

   ClearDrawArea();   

/*
printf("clearing raster ...");
*/

   /* clear local raster array */
   for (y = 0; y < RASTER_Y_SIZE; y++)
   {
      for (x = 0; x < RASTER_X_SIZE; x++)
      {
         raster[x][y] = (UBYTE_T) BLACK;
      }
   }  

/*
printf(" done\n");
*/
}


/******************************************************************************
*  ClearColorMap - clears local color map                                     *
******************************************************************************/
void
ClearColorMap()
{
   int c;
  
   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      colormap.valid[c] = FALSE;
   }   

   colormap.map[BLACK].r = 0;
   colormap.map[BLACK].g = 0;
   colormap.map[BLACK].b = 0;
}


/******************************************************************************
*  SetCurrentColor - sets current drawing color to index specified               *
******************************************************************************/
void
SetCurrentColor(int color_idx)
{
   int idx;

   idx = colormap.indexes[color_idx];

   SetColor(idx);    

   current_color_index = color_idx;
}


/******************************************************************************
*  SetDrawColor - sets current drawing color to index specified               *
******************************************************************************/
void
SetDrawColor(int color_idx)
{
/*
printf("setting color index %d\n", color_idx);
*/

   SetColor(color_idx);    

   current_color_index = color_idx;
}


/******************************************************************************
*  AddDrawColor - adds a new color to the color table                         *
******************************************************************************/
void
AddDrawColor(COLOR_S_T color)
{
   int 		c, c_index, rgb_index;
   BOOLEAN_T	exists = FALSE;
   

   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      if (colormap.valid[c])
      {
         if ( (color.r == colormap.map[c].r)
		&& (color.g == colormap.map[c].g)
		&& (color.b == colormap.map[c].b) )
         {
            exists = TRUE;
            c_index = c;
         }
      }
   }

   if (!exists)
   {
      rgb_index = GetRGBColor( (int)color.r, (int)color.g, (int)color.b );
      c_index = colormap.count;

      if (c_index >= 0 && c_index < MAX_COLOR_MAP)
      {
         colormap.map[c_index].r = color.r;
         colormap.map[c_index].g = color.g;
         colormap.map[c_index].b = color.b;

         colormap.valid[c_index] = TRUE;

         colormap.indexes[c_index] = rgb_index;

         colormap.count++;

         printf("Added color %d,%d,%d as index %d\n", color.r, color.g, color.b, c_index);

         if (c_index > 250) 
         {
            printf("WARNING: exceeded 250 colors, c_index = %d\n", c_index);
         }
      }
      else
      {
         printf("WARNING: allocation of color failed, set to black (c_index was %d)\n", c_index);


         SetDrawColor(BLACK);
      }
   }  

/*   SetDrawColor(c_index); */
   SetCurrentColor(c_index);
}


/******************************************************************************
*  DrawScreenBorders - splits screen into four viewports and labels each      *
******************************************************************************/
void
DrawScreenBorders()
{
   pointType xy_tp, zy_tp, xz_tp, camera_tp;

   SetDrawColor(WHITE);

   DrawLine( 0, InvertY(SCREEN_Y_SIZE / 2), 
		SCREEN_X_SIZE, InvertY(SCREEN_Y_SIZE / 2) );

   DrawLine( (SCREEN_X_SIZE / 2), InvertY(0), 
		(SCREEN_X_SIZE / 2), InvertY(SCREEN_Y_SIZE) );

   xy_tp.x = 10;
   xy_tp.y = (SCREEN_Y_SIZE / 2) + 10;

   zy_tp.x = (SCREEN_X_SIZE / 2) + 10;
   zy_tp.y = (SCREEN_Y_SIZE / 2) + 10;

   xz_tp.x = 10;
   xz_tp.y = 10;

   camera_tp.x = (SCREEN_X_SIZE / 2) + 10;
   camera_tp.y = 10;

   DrawText( "xy view", xy_tp.x, InvertY(xy_tp.y) );
   DrawText( "zy view", zy_tp.x, InvertY(zy_tp.y) );
   DrawText( "xz view", xz_tp.x, InvertY(xz_tp.y) );
   DrawText( "camera view", camera_tp.x, InvertY(camera_tp.y) );
}


/******************************************************************************
*  DrawScreenLabel - labels viewport when viewport is entire screen           *
******************************************************************************/
void
DrawScreenLabel(VIEW_SCREEN_T viewport)
{
   pointType xz_tp;

   SetDrawColor(WHITE);

   xz_tp.x = 10;
   xz_tp.y = 10;

   switch (viewport)
   {
      case ORTH_XY_VIEW:
         DrawText( "xy view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case ORTH_ZY_VIEW:
         DrawText( "zy view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case ORTH_XZ_VIEW:
         DrawText( "xz view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case CAMERA_VIEW:
         DrawText( "camera view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      default:
         break;
   }
}


/******************************************************************************
*  DrawCameraLocation - draws an icon at the current camera location          *
******************************************************************************/
void
DrawCameraLocation(VIEW_SCREEN_T viewport, MyProgram *data, matrixType *mapxform)
{
   wpointType	eyeloc, lookat;
   pointType 	camera_pt, lap_pt, new_lap_pt;
   int 		text_ht, text_wd;
   XFont 	font;

   SetDrawColor(WHITE);

   font = GetWidgetFont(drawarea_widget);

   text_ht = FontHeight(font);
   text_wd = TextWidth(font, "C");

   switch(viewport)
   {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         eyeloc.x = data->data.view.eyeloc.x;
         eyeloc.y = data->data.view.eyeloc.y;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.x;
         lookat.y = data->data.view.lookat.y;
         lookat.z = 1.0;
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         eyeloc.x = data->data.view.eyeloc.z;
         eyeloc.y = data->data.view.eyeloc.y;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.z;
         lookat.y = data->data.view.lookat.y;
         lookat.z = 1.0;
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         eyeloc.x = data->data.view.eyeloc.x;
         eyeloc.y = data->data.view.eyeloc.z;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.x;
         lookat.y = data->data.view.lookat.z;
         lookat.z = 1.0;
         break;
      default:
         break;
   }

   camera_pt = MapToView(eyeloc, mapxform);
   lap_pt = MapToView(lookat, mapxform);

   DrawText( "C", camera_pt.x, (InvertY(camera_pt.y) - (text_ht / 2)) );

   DrawFilledBox( camera_pt.x, InvertY(camera_pt.y), 3, 3 );

   new_lap_pt = LerpPoint( &camera_pt, &lap_pt, 0.1 );

   DrawLine( camera_pt.x, InvertY(camera_pt.y), 
				new_lap_pt.x, InvertY(new_lap_pt.y) );

/*
   DrawFilledBox( lap_pt.x, InvertY(lap_pt.y), 3, 3 );
*/
}


/******************************************************************

  DrawParticle -- This function draws the particle at its current 
			position in its current color.

******************************************************************/
void
DrawParticle(wpointType *position, COLOR_S_T *color, matrixType *mapxform)
{
   pointType pos_p;
   int cindex;
   COLOR_S_T current_color;

/*
printf("position is %f,%f,%f\n", position->x, position->y, position->z);
*/

   pos_p = MapToView(*position, mapxform);

/*
printf("drawing particle at %d,%d\n", pos_p.x, pos_p.y);
*/

   cindex = raster[pos_p.x][pos_p.y];

/*
printf("cindex = %d\n", cindex);
*/

   if (cindex != BLACK)
   {
      current_color.r = CLAMP((color->r + colormap.map[cindex].r), 0, 255);
      current_color.g = CLAMP((color->g + colormap.map[cindex].g), 0, 255);
      current_color.b = CLAMP((color->b + colormap.map[cindex].b), 0, 255);
   }
   else
   {
      current_color.r = color->r;
      current_color.g = color->g;
      current_color.b = color->b;
   }

   AddDrawColor(current_color);

   raster[pos_p.x][pos_p.y] = (UBYTE_T) current_color_index;

   DrawPixel(pos_p.x, InvertY(pos_p.y) );
} 


/* end of drwlibsx.c */
