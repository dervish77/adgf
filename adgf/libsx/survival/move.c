/***********************************************************************

 Movement game routines for Survival.

   File:  	move.c

   Author: 	Brian Lingard

   Date:	10/15/97

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
#include "main.h"		/* already includes "survival.h" */
#endif




/******************************************************************************
*  MovePlayerIcon - move icon                                                 *
******************************************************************************/
void
MovePlayerIcon(MyProgram *data)
{
   int r, c;
   int idx;
   ICON_S_T *icon;

   /*  draw map as background
    */
   r = data->data.previous_row;
   c = data->data.previous_col;
   idx = data->data.map[r][c];
   icon = &data->icons[idx];
   DrawIcon(data, icon, r, c);

   /*  draw board as foreground
    */
   r = data->data.current_row;
   c = data->data.current_col;
   idx = data->data.board[r][c];
   icon = &data->icons[idx];
   DrawIcon(data, icon, r, c);
}


/******************************************************************************
*  HandleCollision - handle collision detection                               *
******************************************************************************/
void
HandleCollision(int r, int c, MyProgram *data)
{
   if ( data->data.map[r][c] == ICON_NONE )
   {
      UpdateStatus( "Grasslands", data );
      AdjustValue( ICON_NONE, DECR_WATER, data );
      AdjustValue( ICON_NONE, DECR_FOOD, data );
   }
   else
   {
      switch( data->data.map[r][c] )
      {
         case ICON_WATER:
            UpdateStatus( "Walked into some water", data );
            AdjustValue( ICON_WATER, INCR_WATER, data );
            AdjustValue( ICON_WATER, INCR_FOOD, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_FOOD:
            UpdateStatus( "Walked into some food", data );
            AdjustValue( ICON_FOOD, INCR_WATER, data );
            AdjustValue( ICON_FOOD, INCR_FOOD, data );
            data->data.map[r][c] = ICON_NONE;
            break;

         case ICON_FOREST:
            UpdateStatus( "You are in the forest", data );
            AdjustValue( ICON_FOREST, DECR_WATER, data );
            AdjustValue( ICON_FOREST, DECR_FOOD, data );
            break;

         case ICON_DESERT:
            UpdateStatus( "You are in the desert", data );
            AdjustValue( ICON_DESERT, DECR_WATER, data );
            AdjustValue( ICON_DESERT, DECR_FOOD, data );
            break;

         case ICON_MOUNTAIN:
            UpdateStatus( "You are in the mountains", data );
            AdjustValue( ICON_MOUNTAIN, DECR_WATER, data );
            AdjustValue( ICON_MOUNTAIN, DECR_FOOD, data );
            break;

         case ICON_TRAIL:
            UpdateStatus( "You are on a trail", data );
            AdjustValue( ICON_TRAIL, DECR_WATER, data );
            AdjustValue( ICON_TRAIL, DECR_FOOD, data );
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

   data->data.previous_row = r = data->data.current_row;
   data->data.previous_col = c = data->data.current_col;

   switch(key)
   {
      case KEY_UP:
         data->data.board[r][c] = ICON_NONE;
         r = r - 1;
         if (r < 0)
            r = MAX_GRID_ROW - 1;
         HandleCollision( r, c, data );
         data->data.board[r][c] = ICON_PLAYU;
         break;

      case KEY_DOWN:
         data->data.board[r][c] = ICON_NONE;
         r = r + 1;
         if (r >= MAX_GRID_ROW)
            r = 0;
         HandleCollision( r, c, data );
         data->data.board[r][c] = ICON_PLAYD;
         break;

      case KEY_LEFT:
         data->data.board[r][c] = ICON_NONE;
         c = c - 1;
         if (c < 0)
            c = MAX_GRID_COL - 1;
         HandleCollision( r, c, data );
         data->data.board[r][c] = ICON_PLAYL;
         break;

      case KEY_RIGHT:
         data->data.board[r][c] = ICON_NONE;
         c = c + 1;
         if (c >= MAX_GRID_COL)
            c = 0;
         HandleCollision( r, c, data );
         data->data.board[r][c] = ICON_PLAYR;
         break;
   }

   data->data.current_row = r;
   data->data.current_col = c;

   MovePlayerIcon(data);
}


/******************************************************************************
*  HandleTaunt - handle sending taunt messages                                *
******************************************************************************/
void
HandleTaunt(MyProgram *data)
{
   printf("taunting\n");
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

      case KEY_NEWGAME:
         UpdateStatus( "Starting new game", data );
         HandleNewGame( data );
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

      case KEY_MULTI:
         PopupMultiPlayer( data );
         break;

      case KEY_TAUNT:
         HandleTaunt( data );
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
