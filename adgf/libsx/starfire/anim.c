/***********************************************************************

 Animation game routines for StarFire.

   File:  	anim.c

   Author: 	Brian Lingard

   Date:	10/31/97

   Revisions:
	0.0	10/31/97	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "starfire.h" */
#endif


/******************************************************************************
*  ToggleAnim - enable/disable animation                                      *
******************************************************************************/
void
ToggleAnim(MyProgram *data)
{
   if (data->anim.enable_anim)
   {
      printf("turning anim OFF\n");

      data->anim.enable_anim = FALSE;
   }
   else
   {
      printf("turning anim ON\n");

      data->anim.enable_anim = TRUE;

      EnableNextAnimFrame( data );
   }
}


/******************************************************************************
*  MovePhotonIcon - move photon icon                                          *
******************************************************************************/
void
MovePhotonIcon(MyProgram *data)
{
   int r, c;
   int idx;
   ICON_S_T *icon;

   /*  draw map as background
    */
   if (data->data.photon.erase_trail)
   {
      r = data->data.photon.previous_row;
      c = data->data.photon.previous_col;
      idx = data->data.map[r][c];
      icon = &data->icons[idx];
      if (data->data.photon.frame_count == 0)
      {
         DrawIcon(data, icon, r, c);
      }
   }

   /*  draw board as foreground
    */
   if (data->data.photon.hit_target)
   {
      data->data.photon.enable_anim = FALSE;
   }
   else
   {
      r = data->data.photon.current_row;
      c = data->data.photon.current_col;
      idx = data->data.board[r][c];
      icon = &data->icons[idx];
      DrawIcon(data, icon, r, c);
   }
}


/******************************************************************************
*  HandlePhotonCollision - handle photon collision detection                  *
******************************************************************************/
void
HandlePhotonCollision(int r, int c, MyProgram *data)
{

      switch( data->data.map[r][c] )
      {
         case ICON_UFO:
            UpdateStatus( "You blasted a ufo", data );
            AdjustValue( ICON_UFO, INCR_SCORE, data );
            AdjustValue( ICON_UFO, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_UFO_X;
            data->data.photon.hit_target = TRUE;
            break;

         case ICON_PLANET:
            UpdateStatus( "You blasted a planet", data );
            AdjustValue( ICON_PLANET, INCR_SCORE, data );
            AdjustValue( ICON_PLANET, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_PLANET_X;
            data->data.photon.hit_target = TRUE;
            break;

         case ICON_ROID:
            UpdateStatus( "You blasted an asteroid", data );
            AdjustValue( ICON_ROID, INCR_SCORE, data );
            AdjustValue( ICON_ROID, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_ROID_X;
            data->data.photon.hit_target = TRUE;
            break;
      }

}


/******************************************************************************
*  HandlePhotonMove - handle photon movement                                  *
******************************************************************************/
void
HandlePhotonMove(MyProgram *data)
{
   int r, c;


   data->data.photon.previous_row = r = data->data.photon.current_row;
   data->data.photon.previous_col = c = data->data.photon.current_col;

   data->data.board[r][c] = ICON_NONE;

   switch(data->data.photon.direction)
   {
      case ICON_SHIPU:
         r = r - 1;
         if (r < 0)
            r = MAX_GRID_ROW - 1;
         break;

      case ICON_SHIPD:
         r = r + 1;
         if (r >= MAX_GRID_ROW)
            r = 0;
         break;

      case ICON_SHIPL:
         c = c - 1;
         if (c < 0)
            c = MAX_GRID_COL - 1;
         break;

      case ICON_SHIPR:
         c = c + 1;
         if (c >= MAX_GRID_COL)
            c = 0;
         break;
   }

   HandlePhotonCollision( r, c, data );

   if (data->data.photon.hit_target)
   {
      data->data.board[r][c] = ICON_NONE;
   }
   else
   {
      data->data.board[r][c] = ICON_PHOTON;
   }

   data->data.photon.current_row = r;
   data->data.photon.current_col = c;

   MovePhotonIcon( data );

   data->data.photon.frame_count++;
}


/******************************************************************************
*  HandleNextAnimFrame - handle processing for next animation frame           *
******************************************************************************/
void
HandleNextAnimFrame(MyProgram *data)
{
/*
   printf("frame %d\n", data->anim.frame_count);
*/

   if (data->data.photon.enable_anim)
   {
      HandlePhotonMove( data );
   }
}


/* end of anim.c */
