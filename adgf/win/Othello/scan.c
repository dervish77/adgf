/***********************************************************************

 Board scan logic for Othello game.

   File:  	scan.c

   Author: 	Brian Lingard

   Date:	3/29/96

   Revisions:
	0.1	04/01/96	added support for board scanning
	0.0	03/29/96	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>

#ifndef _MAIN_H
#include "main.h"		/* already includes "othello.h" */
#endif



/*
#define SCAN_DEBUG 1
*/


/******************************************************************************
*  ScanBoard - scans board for current player's legal moves                   *
******************************************************************************/
BOOLEAN_T
ScanBoard(MyProgram *data, int pr, int pc)
{
   NEIGHBOR_A_T neighbors;


   /*  scan picked cell's neighbors and if any are not all empty scan
    *  each direction until find a legal move in a given direction
    */
   if ( ScanNeighbors(data, pr, pc, neighbors) )
   {
      if ( neighbors[0][0] != PIECE_EMPTY )
      {
         if ( ScanDiag(data, pr, pc, DIR_NW) )
            return(TRUE);
      }

      if ( neighbors[0][1] != PIECE_EMPTY )
      {
         if ( ScanColumn(data, pr, pc, DIR_N) )
            return(TRUE);
      }

      if ( neighbors[0][2] != PIECE_EMPTY )
      {
         if ( ScanDiag(data, pr, pc, DIR_NE) )
            return(TRUE);
      }

      if ( neighbors[1][0] != PIECE_EMPTY )
      {
         if ( ScanRow(data, pr, pc, DIR_W) )
            return(TRUE);
      }

      if ( neighbors[1][2] != PIECE_EMPTY )
      {
         if ( ScanRow(data, pr, pc, DIR_E) )
            return(TRUE);
      }

      if ( neighbors[2][0] != PIECE_EMPTY )
      {
         if ( ScanDiag(data, pr, pc, DIR_SW) )
            return(TRUE);
      }

      if ( neighbors[2][1] != PIECE_EMPTY )
      {
         if ( ScanColumn(data, pr, pc, DIR_S) )
            return(TRUE);
      }

      if ( neighbors[2][2] != PIECE_EMPTY )
      {
         if ( ScanDiag(data, pr, pc, DIR_SE) )
            return(TRUE);
      }
   }

   return(FALSE);
}


/******************************************************************************
*  ScanNeighbors - scans 3x3 region around current r,c position               *
******************************************************************************/
BOOLEAN_T
ScanNeighbors(MyProgram *data, int sr, int sc, NEIGHBOR_A_T nba)
{
   int r,c;

   if (sr == 0)
   {
      if (sc == 0)
      {
         nba[0][0] = PIECE_EMPTY;
         nba[0][1] = PIECE_EMPTY;
         nba[0][2] = PIECE_EMPTY;
         nba[1][0] = PIECE_EMPTY;
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = PIECE_EMPTY;
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = data->data.board[sr + 1][sc + 1];

      }
      else if (sc == (data->screen.max_grid_col - 1))
      {
         nba[0][0] = PIECE_EMPTY;
         nba[0][1] = PIECE_EMPTY;
         nba[0][2] = PIECE_EMPTY;
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = PIECE_EMPTY;
         nba[2][0] = data->data.board[sr + 1][sc - 1];
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = PIECE_EMPTY;
      }
      else
      {
         nba[0][0] = PIECE_EMPTY;
         nba[0][1] = PIECE_EMPTY;
         nba[0][2] = PIECE_EMPTY;
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = data->data.board[sr + 1][sc - 1];
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = data->data.board[sr + 1][sc + 1];
      }
   }
   else if (sr == (data->screen.max_grid_row - 1))
   {
      if (sc == 0)
      {
         nba[0][0] = PIECE_EMPTY;
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = data->data.board[sr - 1][sc + 1];
         nba[1][0] = PIECE_EMPTY;
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = PIECE_EMPTY;
         nba[2][1] = PIECE_EMPTY;
         nba[2][2] = PIECE_EMPTY;
      }
      else if (sc == (data->screen.max_grid_col - 1))
      {
         nba[0][0] = data->data.board[sr - 1][sc - 1];
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = PIECE_EMPTY;
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = PIECE_EMPTY;
         nba[2][0] = PIECE_EMPTY;
         nba[2][1] = PIECE_EMPTY;
         nba[2][2] = PIECE_EMPTY;
      }
      else
      {
         nba[0][0] = data->data.board[sr - 1][sc - 1];
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = data->data.board[sr - 1][sc + 1];
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = PIECE_EMPTY;
         nba[2][1] = PIECE_EMPTY;
         nba[2][2] = PIECE_EMPTY;
      }
   }
   else
   {
      if (sc == 0)
      {
         nba[0][0] = PIECE_EMPTY;
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = data->data.board[sr - 1][sc + 1];
         nba[1][0] = PIECE_EMPTY;
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = PIECE_EMPTY;
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = data->data.board[sr + 1][sc + 1];
      }
      else if (sc == (data->screen.max_grid_col - 1))
      {
         nba[0][0] = data->data.board[sr - 1][sc - 1];
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = PIECE_EMPTY;
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = PIECE_EMPTY;
         nba[2][0] = data->data.board[sr + 1][sc - 1];
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = PIECE_EMPTY;
      }
      else
      {
         nba[0][0] = data->data.board[sr - 1][sc - 1];
         nba[0][1] = data->data.board[sr - 1][sc];
         nba[0][2] = data->data.board[sr - 1][sc + 1];
         nba[1][0] = data->data.board[sr][sc - 1];
         nba[1][1] = data->data.board[sr][sc];
         nba[1][2] = data->data.board[sr][sc + 1];
         nba[2][0] = data->data.board[sr + 1][sc - 1];
         nba[2][1] = data->data.board[sr + 1][sc];
         nba[2][2] = data->data.board[sr + 1][sc + 1];
      }
   }

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanNeighbors: nba\n");
   for (r = 0; r < 3; r++)
   {
      fprintf(stdout, "          ");
      for (c = 0; c < 3; c++)
      {
         fprintf(stdout, "%d ", nba[r][c]);
      }
      fprintf(stdout, "\n");
   }
#endif

   /*  check neighbors for any cells that are not empty 
    */
   for (r = 0; r < 3; r++)
   {
      for (c = 0; c < 3; c++)
      {
         if ( nba[r][c] != PIECE_EMPTY )
         {
            return(TRUE);
         }
      }
   }

   return(FALSE);
}


/******************************************************************************
*  ScanRow - scans specified row for current player's legal moves             *
******************************************************************************/
BOOLEAN_T
ScanRow(MyProgram *data, int sr, int sc, DIRECTION_T dir)
{
   int 		c;			/* loop indices */
   BOOLEAN_T 	found_1, found_2;	/* flags for finding opposite player */
   PIECE_T	player;			/* current player */


   found_1 = FALSE;
   found_2 = FALSE;

   player = data->data.current_player;

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanRow: sr, sc = %d, %d\n", sr, sc);
   fprintf(stdout, "ScanRow: dir = %d\n", dir);
   fprintf(stdout, "ScanRow: player = %d\n", player);
#endif

   switch(dir)
   {
      case DIR_E:
         for (c = (sc + 1); c < data->screen.max_grid_col; c++)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[sr][c] == PIECE_PLAYER_1))
                  return(FALSE);
               else if (found_2 && (data->data.board[sr][c] == PIECE_EMPTY))
                  return(FALSE);
               else if (found_2 && (data->data.board[sr][c] == PIECE_PLAYER_1))
                  return(TRUE);
               else
                  found_2 = TRUE;
            }
            else
            {
               if (!found_1 && (data->data.board[sr][c] == PIECE_PLAYER_2))
                  return(FALSE);
               else if (found_1 && (data->data.board[sr][c] == PIECE_EMPTY))
                  return(FALSE);
               else if (found_1 && (data->data.board[sr][c] == PIECE_PLAYER_2))
                  return(TRUE);
               else
                  found_1 = TRUE;
            }
         }
         break;

      case DIR_W:
         for (c = (sc - 1); c >= 0; c--)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[sr][c] == PIECE_PLAYER_1))
                  return(FALSE);
               else if (found_2 && (data->data.board[sr][c] == PIECE_EMPTY))
                  return(FALSE);
               else if (found_2 && (data->data.board[sr][c] == PIECE_PLAYER_1))
                  return(TRUE);
               else
                  found_2 = TRUE;
            }
            else
            {
               if (!found_1 && (data->data.board[sr][c] == PIECE_PLAYER_2))
                  return(FALSE);
               else if (found_1 && (data->data.board[sr][c] == PIECE_EMPTY))
                  return(FALSE);
               else if (found_1 && (data->data.board[sr][c] == PIECE_PLAYER_2))
                  return(TRUE);
               else
                  found_1 = TRUE;
            }
         }
         break;

      default:
         break;
   }

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanRow: hit edge\n");
#endif
   return(FALSE);	/* return not legal */
}


/******************************************************************************
*  ScanColumn - scans column for current player's legal moves                 *
******************************************************************************/
BOOLEAN_T
ScanColumn(MyProgram *data, int sr, int sc, DIRECTION_T dir)
{
   int 		r;			/* loop indices */
   BOOLEAN_T 	found_1, found_2;	/* flags for finding opposite player */
   PIECE_T	player;			/* current player */


   found_1 = FALSE;
   found_2 = FALSE;

   player = data->data.current_player;

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanColumn: sr, sc = %d, %d\n", sr, sc);
   fprintf(stdout, "ScanColumn: dir = %d\n", dir);
   fprintf(stdout, "ScanColumn: player = %d\n", player);
#endif

   switch(dir)
   {
      case DIR_S:
         for (r = (sr + 1); r < data->screen.max_grid_row; r++)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][sc] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][sc] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][sc] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][sc] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][sc] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][sc] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      case DIR_N:
         for (r = (sr - 1); r >= 0; r--)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][sc] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][sc] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][sc] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][sc] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][sc] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][sc] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      default:
         break;
   }

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanColumn: hit edge\n");
#endif
   return(FALSE);	/* return not legal */
}


/******************************************************************************
*  ScanDiag - scans diagonal line for current player's legal moves            *
******************************************************************************/
BOOLEAN_T
ScanDiag(MyProgram *data, int sr, int sc, DIRECTION_T dir)
{
   int 		r, c;			/* loop indices */
   BOOLEAN_T 	found_1, found_2;	/* flags for finding opposite player */
   PIECE_T	player;			/* current player */


   found_1 = FALSE;
   found_2 = FALSE;

   player = data->data.current_player;

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanDiag: sr, sc = %d, %d\n", sr, sc);
   fprintf(stdout, "ScanDiag: dir = %d\n", dir);
   fprintf(stdout, "ScanDiag: player = %d\n", player);
#endif

   switch(dir)
   {
      case DIR_NE:
         for (r = (sr - 1), c = (sc + 1); 
		((r >= 0) && (c < data->screen.max_grid_col)); r--, c++)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      case DIR_SE:
         for (r = (sr + 1), c = (sc + 1); 
		((r < data->screen.max_grid_row) && (c < data->screen.max_grid_col)); r++, c++)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      case DIR_SW:
         for (r = (sr + 1), c = (sc - 1); 
		((r < data->screen.max_grid_row) && (c >= 0)); r++, c--)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      case DIR_NW:
         for (r = (sr - 1), c = (sc - 1); 
		((r >= 0) && (c >= 0)); r--, c--)
         {
            if (player == PIECE_PLAYER_1)
            {
               if (!found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_2 && (data->data.board[r][c] == PIECE_PLAYER_1))
               {
                  return(TRUE);
               }
               else
               {
                  found_2 = TRUE;
               }
            }
            else
            {
               if (!found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_EMPTY))
               {
                  return(FALSE);
               }
               else if (found_1 && (data->data.board[r][c] == PIECE_PLAYER_2))
               {
                  return(TRUE);
               }
               else
               {
                  found_1 = TRUE;
               }
            }
         }
         break;

      default:
         break;
   }

#ifdef SCAN_DEBUG
   fprintf(stdout, "ScanDiag: hit edge\n");
#endif
   return(FALSE);	/* return not legal */
}



/* end of scan.c */
