/***********************************************************************

 Movement game routines for StarFire.

   File:  	move.c

   Author: 	Brian Lingard

   Date:	10/05/97

   Revisions:
	0.0	10/13/97	Originated

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
*  MovePlayerIcon - move player icon                                          *
******************************************************************************/
void
MovePlayerIcon(MyProgram *data)
{
   int r, c;
   int idx;
   ICON_S_T *icon;

   /*  draw map as background
    */
   r = data->data.player.previous_row;
   c = data->data.player.previous_col;
   idx = data->data.map[r][c];
   icon = &data->icons[idx];
   DrawIcon(data, icon, r, c);

   /*  draw board as foreground
    */
   r = data->data.player.current_row;
   c = data->data.player.current_col;
   idx = data->data.board[r][c];
   icon = &data->icons[idx];
   DrawIcon(data, icon, r, c);
}


/******************************************************************************
*  HandlePlayerCollision - handle player collision detection                               *
******************************************************************************/
void
HandlePlayerCollision(int r, int c, MyProgram *data)
{
   if ( data->data.map[r][c] == ICON_NONE )
   {
      UpdateStatus( "Empty space", data );
   }
   else
   {
      switch( data->data.map[r][c] )
      {
         case ICON_HEALTH:
            UpdateStatus( "Picked up some health, yes", data );
            AdjustValue( ICON_HEALTH, INCR_SCORE, data );
            AdjustValue( ICON_HEALTH, INCR_HEALTH, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_AMMO:
            UpdateStatus( "Picked up some ammo, blast em", data );
            AdjustValue( ICON_AMMO, INCR_SCORE, data );
            AdjustValue( ICON_AMMO, INCR_HEALTH, data );
            AdjustValue( ICON_AMMO, INCR_AMMO, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_WARP:
            UpdateStatus( "Picked up a warp drive, yee haaa", data );
            AdjustValue( ICON_WARP, INCR_SCORE, data );
            AdjustValue( ICON_WARP, INCR_HEALTH, data );
            AdjustValue( ICON_WARP, INCR_WARP, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_SLAMMER:
            UpdateStatus( "Picked up a planet slammer, groovy", data );
            AdjustValue( ICON_SLAMMER, INCR_SCORE, data );
            AdjustValue( ICON_SLAMMER, INCR_HEALTH, data );
            AdjustValue( ICON_SLAMMER, INCR_AMMO, data );
            AdjustValue( ICON_SLAMMER, INCR_SLAMMER, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_UFO:
            UpdateStatus( "You collided with a ufo, weirdness", data );
            AdjustValue( ICON_UFO, INCR_SCORE, data );
            AdjustValue( ICON_UFO, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_UFO_X;
            break;

         case ICON_PLANET:
            UpdateStatus( "You smashed into a planet, major bummer", data );
            AdjustValue( ICON_PLANET, INCR_SCORE, data );
            AdjustValue( ICON_PLANET, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_PLANET;
            break;

         case ICON_ROID:
            UpdateStatus( "You hit an asteroid, bummer", data );
            AdjustValue( ICON_ROID, INCR_SCORE, data );
            AdjustValue( ICON_ROID, DECR_HEALTH, data );
            data->data.map[r][c] = ICON_ROID_X;
            break;

         case ICON_BHOLE:
            UpdateStatus( "You fell into a black hole, crunch", data );
            AdjustValue( ICON_BHOLE, DECR_HEALTH, data );
            break;

         case ICON_WORM:
            UpdateStatus( "You fell into a wormhole, cowabunga", data );
            AdjustValue( ICON_WORM, DECR_HEALTH, data );
            InitBoard( data );
            UpdateDisplay( data );
            break;
      }
   }
}


/******************************************************************************
*  HandlePlayerMove - handle player movement                                  *
******************************************************************************/
void
HandlePlayerMove(char key, MyProgram *data)
{
   int r, c;

   data->data.player.previous_row = r = data->data.player.current_row;
   data->data.player.previous_col = c = data->data.player.current_col;

   data->data.board[r][c] = ICON_NONE;

   switch(key)
   {
      case KEY_UP:
         r = r - 1;
         if (r < 0)
            r = MAX_GRID_ROW - 1;
         HandlePlayerCollision( r, c, data );
         data->data.board[r][c] = ICON_SHIPU;
         break;

      case KEY_DOWN:
         r = r + 1;
         if (r >= MAX_GRID_ROW)
            r = 0;
         HandlePlayerCollision( r, c, data );
         data->data.board[r][c] = ICON_SHIPD;
         break;

      case KEY_LEFT:
         c = c - 1;
         if (c < 0)
            c = MAX_GRID_COL - 1;
         HandlePlayerCollision( r, c, data );
         data->data.board[r][c] = ICON_SHIPL;
         break;

      case KEY_RIGHT:
         c = c + 1;
         if (c >= MAX_GRID_COL)
            c = 0;
         HandlePlayerCollision( r, c, data );
         data->data.board[r][c] = ICON_SHIPR;
         break;
   }

   data->data.player.current_row = r;
   data->data.player.current_col = c;

   MovePlayerIcon(data);
}


/******************************************************************************
*  HandleFire - handle player firing photons                                  *
******************************************************************************/
void
HandleFire(MyProgram *data)
{
   int r, c;

   if (data->score.ammo > 0)
   {
      UpdateStatus( "Firing photons", data );
      AdjustValue( ICON_PHOTON, DECR_AMMO, data );

      data->data.photon.enable_anim = TRUE;
      data->data.photon.erase_trail = TRUE;
      data->data.photon.hit_target = FALSE;
      data->data.photon.frame_count = 0;

      r = data->data.player.current_row;
      c = data->data.player.current_col;

      data->data.photon.direction = data->data.board[r][c];

      data->data.photon.current_row = r;
      data->data.photon.current_col = c;

      data->anim.enable_anim = TRUE;
      EnableNextAnimFrame( data );
   }
   else
   {
      UpdateStatus( "You don't have any ammo!", data );
   }
}


/******************************************************************************
*  HandleWarp - handle player warping                                         *
******************************************************************************/
void
HandleWarp(MyProgram *data)
{
   if (data->score.warp > 0)
   {
      UpdateStatus( "Engaging warp drive", data );
      InitBoard( data );
      UpdateDisplay( data );
      PlacePlayerIcon( MAX_GRID_ROW/2, MAX_GRID_COL/2, ICON_SHIPU, data );
      AdjustValue( ICON_WARP, DECR_WARP, data );
   }
   else
   {
      UpdateStatus( "You don't have any warp cores!", data );
   }
}


/******************************************************************************
*  HandleSlammer - handle player using planet slammer                         *
******************************************************************************/
void
HandleSlammer(MyProgram *data)
{
   if (data->score.slammer > 0)
   {
      UpdateStatus( "Engaging planet slammer", data );
 
      AdjustValue( ICON_SLAMMER, DECR_SLAMMER, data );
   }
   else
   {
      UpdateStatus( "You don't have a planet slammer!", data );
   }
}


/******************************************************************************
*  HandleKeyPress - handle key press                                          *
******************************************************************************/
void
HandleKeyPress(char key, MyProgram *data)
{
   switch(key)
   {
      case KEY_UP:
      case KEY_DOWN:
      case KEY_LEFT:
      case KEY_RIGHT:
         HandlePlayerMove( key, data );
         break;

      case KEY_FIRE:
         HandleFire( data );
         break;

      case KEY_WARP:
         HandleWarp( data );
         break;

      case KEY_SLAMMER:
         HandleSlammer( data );
         break;

      case KEY_NEWGAME:
         UpdateStatus( "Starting new game", data );
         PopupNewGame( data );
         break;

      case KEY_OPENGAME:
         UpdateStatus( "Loading game", data );
         HandleLoadGame( data );
         break;

      case KEY_SAVEGAME:
         UpdateStatus( "Saving game", data );
         HandleSaveGame( data );
         break;

      case KEY_QUITGAME:
         UpdateStatus( "Quitting game", data );
         PopupQuit();
         break;

      case KEY_EXITGAME:
         exit(0);
         break;

      case KEY_MULTI:
         PopupMultiPlayer( data );
         break;

      case KEY_ANIM:
         ToggleAnim( data );
         break;

      case KEY_INVENTORY:
         PopupInventory( data );
         break;

      default:
         break;
   }

   UpdateScore( data );

   if (data->score.health <= 0)
   {
      PopupGameOver( data );
   }
}



/* end of move.c */
