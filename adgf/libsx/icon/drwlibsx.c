/***********************************************************************

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	9/29/95

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

#ifndef _CALLBCKS_H
#include "callbcks.h"         /* prototypes for callback functions       */
#endif


/* define global default color array */
COLOR_RGB_T default_colors[MAX_COLOR_MAP] = { 160, 160, 160,
						  255, 255, 255,
						  255, 0, 0, 
						  0, 255, 0,
						  0, 0, 255,
						  255, 255, 0,
						  255, 0, 255,
						  0, 255, 255 };


/******************************************************************************
*  ClearScreenDisplay - clears the currently active display                   *
******************************************************************************/
void
ClearScreenDisplay(Widget w)
{
   SetDrawArea(w);
   ClearDrawArea();             
}


/******************************************************************************
*  SetDrawColor - sets current drawing color of the active display to the     *
*                 index specified                                             *
******************************************************************************/
void
SetDrawColor(int idx)	/* NOTE:  idx is libsx color index */
{
   SetColor(idx);
}


/******************************************************************************
*  SetCurrentColor - sets current drawing color to the index specified        *
******************************************************************************/
void
SetCurrentColor(int idx, MyProgram *data)
{
   int color_idx;


   data->current_draw_color = idx;

   color_idx = data->data.colormap.indexes[idx];

   SetBgColor(data->current_color_area, color_idx);

   SetDrawArea(data->work_draw_area);
   SetDrawColor(color_idx);
}


/******************************************************************************
*  UpdateButtonColor - updates color select button's color                    *
******************************************************************************/
void
UpdateButtonColor(int idx, MyProgram *data)
{
   SetBgColor(data->color_buttons[idx], data->data.colormap.indexes[idx]);
}


/******************************************************************************
*  UpdateColor - updates specified entry in the colormap with modified color  *
******************************************************************************/
void
UpdateColor(int idx, COLOR_RGB_T color, MyProgram *data)
{
   int c_index;

   c_index = GetRGBColor( (int)color[R_IDX], 
				(int)color[G_IDX], 
				(int)color[B_IDX] );

   data->data.colormap.map[idx][R_IDX] = color[R_IDX];
   data->data.colormap.map[idx][G_IDX] = color[G_IDX];
   data->data.colormap.map[idx][B_IDX] = color[B_IDX];

   data->data.colormap.indexes[idx] = c_index;
}


/******************************************************************************
*  InitColorMap - initializes the color map table to a set of default colors  *
*                 and sets the current drawing color to default.              *
******************************************************************************/
void
InitColorMap(MyProgram *data)
{
   int c;
   
   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      UpdateColor(c, default_colors[c], data);
   }

   SetCurrentColor(DEFAULT_COLOR, data);
}


/******************************************************************************
*  DrawGrid - draws grid in working draw area                                 *
******************************************************************************/
void
DrawGrid(MyProgram *data)
{
   int i, j;
   int startx, starty;

   int grid_size;

   SetDrawArea(data->work_draw_area);
   SetDrawColor(WHITE);

   /* calculate horizontal grid spacing */
   grid_size = SCREEN_X_SIZE / data->data.size.x;

   data->grid.size.x = grid_size;

   startx = 0;

   /* draw vertical grid lines */
   for (i = 0; i < data->data.size.x; i++)
   {
      if ( startx < (SCREEN_X_SIZE - 1) )
         DrawLine(startx, 0, startx, SCREEN_Y_SIZE);

      startx += grid_size;		/* increment by grid size */
   }

   /* calculate vertical grid spacing */
   grid_size = SCREEN_Y_SIZE / data->data.size.y;

   data->grid.size.y = grid_size;

   starty = 0;

   /* draw horizontal grid lines */
   for (j = 0; j < data->data.size.y; j++)
   {
      if ( starty < (SCREEN_Y_SIZE - 1) )
         DrawLine(0, starty, SCREEN_X_SIZE, starty);

      starty += grid_size;		/* increment by grid size */
   }

   /* init bounding box points */
   for (i = 0; i < data->data.size.y; i++)
   {
      for (j = 0; j < data->data.size.x; j++)
      {
         data->grid.top_left[i][j].x = data->grid.size.x * j;
         data->grid.top_left[i][j].y = data->grid.size.y * i;

         data->grid.bot_right[i][j].x = data->grid.top_left[i][j].x + data->grid.size.x;
         data->grid.bot_right[i][j].y = data->grid.top_left[i][j].y + data->grid.size.y;
      }
   }
}


/******************************************************************************
*  PaintGridCell - paints the specified grid cell using icon color at the     *
*                  same pixel                                                 *
******************************************************************************/
void
PaintGridCell(int r, int c, MyProgram *data)
{
   SetDrawArea(data->work_draw_area);

   SetDrawColor( data->data.colormap.indexes[data->current_grid_color] );

   data->data.pixmap[r][c] = data->current_grid_color;

   DrawFilledBox( (data->grid.top_left[r][c].x + 1),
			(data->grid.top_left[r][c].y + 1),
			(data->grid.size.x - 1),
			(data->grid.size.y - 1) );
}


/******************************************************************************
*  PaintPixel - paints the specified pixel of the icon                        *
******************************************************************************/
void
PaintPixel(int r, int c, MyProgram *data)
{
   pointType	center, top_left;

   center.x = MAX_ICON_X_SIZE / 2;
   center.y = MAX_ICON_Y_SIZE / 2;

   top_left.x = center.x - (data->data.size.x / 2);
   top_left.y = center.y - (data->data.size.y / 2);

   SetDrawArea(data->preview_area);

   SetDrawColor( data->data.colormap.indexes[ data->data.pixmap[r][c] ] );

   DrawPixel( (top_left.x + c), (top_left.y + r) );
}


/* end of drwlibsx.c */
