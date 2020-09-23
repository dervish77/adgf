/***********************************************************************

   File:  	icon.c

   Author: 	Brian Lingard

   Date:	9/29/95

  High level functions for icon editor.

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "icon.h" */
#endif

#ifndef _CALLBCKS_H
#include "callbcks.h"
#endif


/* #define ICON_DEBUG 1
*/

extern void InitColorMap(MyProgram *data);



/******************************************************************************
*  InitDatabase - initializes pointers to global database arrays              *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{
   int i, j;

   data->project_loaded = FALSE;
   data->project_saved = FALSE;

   data->load_file_name[0] = '\0';
   data->save_file_name[0] = '\0';

   data->load_file = (FILE *) NULL;
   data->save_file = (FILE *) NULL;

   data->data.type = 0;

   data->data.size.x = DEFAULT_ICON_X_SIZE;
   data->data.size.y = DEFAULT_ICON_Y_SIZE;

   data->data.top_left.x = 0;
   data->data.top_left.y = 0;

   data->data.num_colors = MAX_COLORS;

   for (i = 0; i < data->data.size.x; i++)
   {
      for (j = 0; j < data->data.size.y; j++)
      {
         data->data.pixmap[i][j] = DEFAULT_COLOR;
      }
   }

   data->grid.draw_grid_flag = TRUE;
}


/******************************************************************************
*  ClearIcon - clear icon data                                                *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*                                                                             *
******************************************************************************/
void
ClearIcon(MyProgram *data)
{
   int i, j;

   for (i = 0; i < data->data.size.x; i++)
   {
      for (j = 0; j < data->data.size.y; j++)
      {
         data->data.pixmap[i][j] = DEFAULT_COLOR;
      }
   }
}


/******************************************************************************
*  LoadIcon - loads icon file                                                 *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*  type                                                                       *
*  sx sy tlx tly                                                              *
*  num_colors                                                                 *
*  c1_red c1_green c1_blue                                                    *
*  c2_red c2_green c3_blue                                                    *
*  ...                                                                        *
*  cn_red cn_green cn_blue                                                    *
*  r1c1 ... r1cn                                                              *
*  ...                                                                        *
*  rnc1 ... rncn                                                              *
*                                                                             *
******************************************************************************/
void
LoadIcon(MyProgram *data)
{
   int 			r, c;
   ICON_TYPE_T		type;
   pointType 		size, topl;
   unsigned char	red, green, blue;
   int			nc, pixel;

   fscanf(data->load_file, "%d\n", &type);
   data->data.type = type;

   fscanf(data->load_file, "%d %d %d %d\n", &size.x, &size.y, &topl.x, &topl.y);
   data->data.size.x = size.x;
   data->data.size.y = size.y;
   data->data.top_left.x = topl.x;
   data->data.top_left.y = topl.y;

   fscanf(data->load_file, "%d\n", &nc);
   data->data.num_colors = nc;

   for (c = 0; c < data->data.num_colors; c++)
   {
      fscanf(data->load_file, "%c %c %c\n", &red, &green, &blue );

      data->data.colormap.map[c][R_IDX] = red;
      data->data.colormap.map[c][G_IDX] = green;
      data->data.colormap.map[c][B_IDX] = blue;
   }

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
          fscanf(data->load_file, "%d ", &pixel);
          data->data.pixmap[r][c] = pixel;
      }
      fscanf(data->load_file, "\n");
   }

   for (c = 0; c < data->data.num_colors; c++)
   {
      UpdateColor(c, data->data.colormap.map[c], data);
      UpdateButtonColor(c, data);
   }
   SetCurrentColor(DEFAULT_COLOR, data);

   UpdateDisplay(data);
   UpdatePreview(data);
}


/******************************************************************************
*  SaveIcon - saves current icon to file                                      *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*  type                                                                       *
*  sx sy tlx tly                                                              *
*  num_colors                                                                 *
*  c1_red c1_green c1_blue                                                    *
*  c2_red c2_green c3_blue                                                    *
*  ...                                                                        *
*  cn_red cn_green cn_blue                                                    *
*  r1c1 ... r1cn                                                              *
*  ...                                                                        *
*  rnc1 ... rncn                                                              *
*                                                                             *
******************************************************************************/
void
SaveIcon(MyProgram *data)
{
   int r, c;

   fprintf(data->save_file, "%d\n", data->data.type);

   fprintf(data->save_file, "%d %d %d %d\n", 
				data->data.size.x, data->data.size.y, 
				data->data.top_left.x, data->data.top_left.y );

   fprintf(data->save_file, "%d\n", data->data.num_colors);

   for (c = 0; c < data->data.num_colors; c++)
   {
      fprintf(data->save_file, "%c %c %c\n", 
				data->data.colormap.map[c][R_IDX],
				data->data.colormap.map[c][G_IDX],
				data->data.colormap.map[c][B_IDX] );
   }

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
          fprintf(data->save_file, "%d ", data->data.pixmap[r][c]);
      }
      fprintf(data->save_file, "\n");
   }
}


/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{
   int r, c;

   ClearScreenDisplay(data->work_draw_area);

   DrawGrid(data);

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
         data->current_grid_color = data->data.pixmap[r][c];

         PaintGridCell(r, c, data);
      }
   }
}


/******************************************************************************
*  FlipIcon - flips icon either vertical or horizontal                        *
******************************************************************************/
void
FlipIcon(int mode, MyProgram *data)
{
   int r, c;
   int pixmap[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];

   switch(mode) 
   {
      case FLIP_VERT:
         for (r = 0; r < data->data.size.y; r++)
         {
            for (c = 0; c < data->data.size.x; c++)
            {
               pixmap[(data->data.size.y - 1) - r][c] = data->data.pixmap[r][c];
            }
         }
         break;

      case FLIP_HORIZ:
         for (r = 0; r < data->data.size.y; r++)
         {
            for (c = 0; c < data->data.size.x; c++)
            {
               pixmap[r][(data->data.size.x - 1) - c] = data->data.pixmap[r][c];
            }
         }
         break;

      default:
         break;
   }

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
         data->data.pixmap[r][c] = pixmap[r][c];
      }
   }
}


/******************************************************************************
*  RotateIcon - rotates icon towards left or right (currently 90 deg)         *
******************************************************************************/
void
RotateIcon(int mode, MyProgram *data)
{
   int r, c;
   int pixmap[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];

   switch(mode) 
   {
      case ROTATE_LEFT:
         for (r = 0; r < data->data.size.y; r++)
         {
            for (c = 0; c < data->data.size.x; c++)
            {
               pixmap[(data->data.size.y - 1) - r][c] = data->data.pixmap[c][r];
            }
         }
         break;

      case ROTATE_RIGHT:
         for (r = 0; r < data->data.size.y; r++)
         {
            for (c = 0; c < data->data.size.x; c++)
            {
               pixmap[r][(data->data.size.x - 1) - c] = data->data.pixmap[c][r];
            }
         }
         break;

      default:
         break;
   }

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
         data->data.pixmap[r][c] = pixmap[r][c];
      }
   }
}


/******************************************************************************
*  UpdatePreview - updates preview display following changes in the database  *
******************************************************************************/
void
UpdatePreview(MyProgram *data)
{
   int r, c;

   ClearScreenDisplay(data->preview_area);

   for (r = 0; r < data->data.size.y; r++)
   {
      for (c = 0; c < data->data.size.x; c++)
      {
         PaintPixel(r, c, data);
      }
   }
}


/******************************************************************************
*  CorrelatePick - determines which grid cell was selected                    *
******************************************************************************/
void
CorrelatePick(int x, int y, MyProgram *data)
{
   int r, c;


   /* save previously picked row and column */
   data->grid.prev_pick_row = data->grid.pick_row;
   data->grid.prev_pick_col = data->grid.pick_col;


   /* calculate picked row */
   r = y / data->grid.size.y;
   
   if ( (y % data->grid.size.y) == 0 )
   {
      r++;
   }


   /* calculate picked column */
   c = x / data->grid.size.x;
   
   if ( (x % data->grid.size.x) == 0 )
   {
      c++;
   }


   /* return picked row and column */
   data->grid.pick_row = r;
   data->grid.pick_col = c;


   /* is this pick valid? */
   if ( (r == data->grid.prev_pick_row) && (c == data->grid.prev_pick_col) )
      data->grid.pick_flag = TRUE;
   else
      data->grid.pick_flag = FALSE;
}


/******************************************************************************
*  ParseString - parses list of strings into array of strings                 *
******************************************************************************/
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


/* end of icon.c */
