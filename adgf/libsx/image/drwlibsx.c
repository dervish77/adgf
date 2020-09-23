/***********************************************************************

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	10/20/95

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
   ClearDrawArea();   
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
      colormap.indexes[c] = 0;
   }   

   colormap.map[BLACK].r = 0;
   colormap.map[BLACK].g = 0;
   colormap.map[BLACK].b = 0;

   colormap.count = 0;
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


/******************************************************************

  DrawImageBuffer - draw current image buffer onto display

******************************************************************/
void
DrawImageBuffer(MyProgram *data)
{
   int r, c;

   COLOR_S_T color;

   char *ras_p;


   ras_p = (char *)&data->data.current.raster[0][0];

   for (r = 0; r < data->data.current.rsize; r++)
   {
      for (c = 0; c < data->data.current.csize; c++)
      {

         color.r = *(ras_p++);
         color.g = *(ras_p++);
         color.b = *(ras_p++);

         AddDrawColor(color);

         DrawPixel(c, r);
      }
   }

} /* end of DrawImageBuffer() */


/******************************************************************

  DrawHistogram - draw histogram of current image buffer

******************************************************************/
void
DrawHistogram(MyProgram *data)
{
   int i, x;
   int length;
   int x_offset, y_offset;
   float scale_factor;

   SetDrawArea(histarea_widget);

   ClearDrawArea();

   if (data->data.hist.computed)
   {
      /*  draw horizontal axis
       */
      SetDrawColor(GREEN);

      DrawLine(HIST_ORIG_X_OFFSET, 
		(HIST_Y_SIZE - HIST_ORIG_Y_OFFSET), 
		(HIST_ORIG_X_OFFSET + HIST_X_AXIS_LEN + 5), 
		(HIST_Y_SIZE - HIST_ORIG_Y_OFFSET) );

      /*  draw vertical axis
       */
      DrawLine(HIST_ORIG_X_OFFSET, 
		(HIST_Y_SIZE - HIST_ORIG_Y_OFFSET), 
		HIST_ORIG_X_OFFSET, 
		(HIST_Y_SIZE - (HIST_ORIG_Y_OFFSET + HIST_Y_AXIS_LEN + 1)));

      /*  draw histogram 
       */
      SetDrawColor(WHITE);

      scale_factor = (float) HIST_Y_AXIS_LEN / (float) (data->data.current.csize * data->data.current.rsize);

      x_offset = HIST_ORIG_X_OFFSET + 1 + 5;
      y_offset = HIST_ORIG_Y_OFFSET + 1;

      for (i = 0; i < MAX_GRADIENT_LEVELS; i++)
      {
         if (data->data.hist.array[i] > 0)
         {
            length = (int) (scale_factor * (float)data->data.hist.array[i]);

            x = x_offset + i;

            DrawLine( x, (HIST_Y_SIZE - y_offset), 
			x, (HIST_Y_SIZE - (y_offset + length)));
         }
      }
   }

   SetDrawArea(drawarea_widget);
}


/******************************************************************

  DrawLUT - draw current lookup table 

******************************************************************/
void
DrawLUT(MyProgram *data)
{
   int i, y;


   SetDrawArea(lutarea_widget);

   ClearDrawArea();

   for (i = 0; i < MAX_GRADIENT_LEVELS; i = i + 2)
   {
      y = data->data.lut[i] / 2;

      DrawPixel( (i / 2), (LUT_Y_SIZE - y + 1) );
   }

   SetDrawArea(drawarea_widget);
}


/* end of drwlibsx.c */
