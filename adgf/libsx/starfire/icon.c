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

#ifndef _CALLBACK_H
#include "callback.h"
#endif



/*
 *  GLOBALS
 */
ICONFILE_S_T icon_file_array[MAX_NUM_ICONS] = 
{
	0, "icons/null.icn",	  0,   0,   0,   0,
        1, "icons/ufo.icn",     100,   0,  10,   0, 
	2, "icons/ufox.icn",      0,   0,   0,   0,
	2, "icons/photon.icn",    0,   0,  20,   1,
	4, "icons/null.icn",	  0,   0,   0,   0,
	5, "icons/null.icn",	  0,   0,   0,   0,
	6, "icons/null.icn",	  0,   0,   0,   0,
	7, "icons/null.icn",	  0,   0,   0,   0,
	8, "icons/null.icn",	  0,   0,   0,   0,
	9, "icons/null.icn",	  0,   0,   0,   0,
       10, "icons/planet.icn", 1000,   0,  50,   0, 
       11, "icons/planetx.icn",	  0,   0,   0,   0,
       12, "icons/roid.icn",     10,   0,  10,   0,
       13, "icons/roidx.icn",	  0,   0,   0,   0,
       14, "icons/bhole.icn",	  0,   0, 100,   0,
       15, "icons/worm.icn",	  0,   0,  20,   0,
       16, "icons/null.icn",	  0,   0,   0,   0,
       17, "icons/null.icn",	  0,   0,   0,   0,
       18, "icons/null.icn",	  0,   0,   0,   0,
       19, "icons/null.icn",	  0,   0,   0,   0,
       20, "icons/health.icn",   20,  25,   0,   0,
       21, "icons/ammo.icn",     20,   5,   0,  10,
       22, "icons/warp.icn",	 25,  10,   0,   0,
       23, "icons/slammer.icn",	 50,  50, 500,  10,
       24, "icons/null.icn",	  0,   0,   0,   0,
       25, "icons/null.icn",	  0,   0,   0,   0,
       26, "icons/null.icn",	  0,   0,   0,   0,
       27, "icons/null.icn",	  0,   0,   0,   0,
       28, "icons/null.icn",	  0,   0,   0,   0,
       29, "icons/null.icn",	  0,   0,   0,   0,
       30, "icons/shipx.icn",	  0,   0,   0,   0,
       31, "icons/shipu.icn",	500,   0,  20,   0,
       32, "icons/shipd.icn",   500,   0,  20,   0,
       33, "icons/shipl.icn",   500,   0,  20,   0,
       34, "icons/shipr.icn",   500,   0,  20,   0,
};


/******************************************************************************
*  AdjustValue - adjusts various score values                                 *
******************************************************************************/
void
AdjustValue(int iconidx, int method, MyProgram *data)
{
   switch( method )
   {
      case INCR_SCORE:
         data->score.score += icon_file_array[iconidx].score;
         break;

      case INCR_HEALTH:
         data->score.health += icon_file_array[iconidx].health;
         break;

      case INCR_AMMO:
         data->score.ammo += icon_file_array[iconidx].ammo;
         break;

      case INCR_WARP:
         data->score.warp += 1;
         break;

      case INCR_SLAMMER:
         data->score.slammer += 1;
         break;

      case DECR_SCORE:
         data->score.score -= icon_file_array[iconidx].score;
         if (data->score.score < 0) data->score.score = 0;
         break;

      case DECR_HEALTH:
         data->score.health -= icon_file_array[iconidx].damage;
         if (data->score.health < 0) data->score.health = 0;
         break;

      case DECR_AMMO:
         data->score.ammo -= icon_file_array[iconidx].ammo;
         if (data->score.ammo < 0) data->score.ammo = 0;
         break;

      case DECR_WARP:
         data->score.warp -= 1;
         if (data->score.warp < 0) data->score.warp = 0;
         break;

      case DECR_SLAMMER:
         data->score.slammer -= 1;
         if (data->score.slammer < 0) data->score.slammer = 0;
         break;
   }
}


/******************************************************************************
*  PlaceIcon - clear icon data                                                *
******************************************************************************/
void
PlaceIcon(int iconidx, int max_icons, MyProgram *data)
{
   int i, r, c, max;

   max = int_random( 1, max_icons );
   for (i = 0; i < max; i++)
   {
      r = int_random( 1, MAX_GRID_ROW );
      c = int_random( 1, MAX_GRID_COL );
      data->data.map[r-1][c-1] = iconidx;
   }
}


/******************************************************************************
*  PlacePlayerIcon - place player's icon                                      *
******************************************************************************/
void
PlacePlayerIcon(int r, int c, int iconidx, MyProgram *data)
{
   data->data.player.current_row = r;
   data->data.player.current_col = c;
   data->data.player.previous_row = r;
   data->data.player.previous_col = c;
   data->data.board[r][c] = iconidx;
}


/******************************************************************************
*  ClearIcon - clear icon data                                                *
******************************************************************************/
void
ClearIcon(ICON_S_T *data)
{
   int r, c;

   for (r = 0; r < data->size.y; r++)
   {
      for (c = 0; c < data->size.x; c++)
      {
         data->pixmap[r][c] = DEFAULT_COLOR;
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
LoadIcon(FILE *fp, ICON_S_T *iconptr)
{
   int 			r, c;
   ICON_TYPE_T		type;
   pointType 		size, topl;
   unsigned char	red, green, blue;
   int			nc, pixel;
   COLOR_RGB_T 		color;

   fscanf(fp, "%d\n", &type);
   iconptr->type = type;

   fscanf(fp, "%d %d %d %d\n", &size.x, &size.y, &topl.x, &topl.y);
   iconptr->size.x = size.x;
   iconptr->size.y = size.y;
   iconptr->top_left.x = topl.x;
   iconptr->top_left.y = topl.y;

   fscanf(fp, "%d\n", &nc);
   iconptr->num_colors = nc;

   for (c = 0; c < iconptr->num_colors; c++)
   {
      fscanf(fp, "%c %c %c\n", &red, &green, &blue );

      iconptr->colormap.map[c][R_IDX] = color[R_IDX] = red;
      iconptr->colormap.map[c][G_IDX] = color[G_IDX] = green;
      iconptr->colormap.map[c][B_IDX] = color[B_IDX] = blue;

/*
printf("r=%d, g=%d, b=%d\n", color[R_IDX], color[G_IDX], color[B_IDX]);
*/

/*
      UpdateColor(c, color, iconptr);
*/
   }

   for (r = 0; r < iconptr->size.y; r++)
   {
      for (c = 0; c < iconptr->size.x; c++)
      {
          fscanf(fp, "%d ", &pixel);
          iconptr->pixmap[r][c] = pixel;
      }
      fscanf(fp, "\n");
   }
}


/******************************************************************************
*  LoadIconArray - loads array of game icons                                  *
*                                                                             *
******************************************************************************/
void
LoadIconArray(MyProgram *data)
{
   FILE *fp;
   int i;

   fprintf( stdout, "Loading icons...\n");

   for (i = 0; i < MAX_NUM_ICONS; i++)
   {
      fp = fopen(icon_file_array[i].filename, "r");
      if (fp == (FILE *) NULL)
      {
         fprintf(stderr, 
		"file_load: can't open '%s' as icon file\n", 
		icon_file_array[i].filename);
         exit(1);
      }

/*
      fprintf( stdout, "   loading icon -- %s\n", icon_file_array[i].filename);
*/

      LoadIcon( fp, &data->icons[i] );

      fclose(fp);
   }
}



/* end of icon.c */
