/***********************************************************************

 Flip logic for Othello game.

   File:  	flip.c

   Author: 	Brian Lingard

   Date:	3/29/96

   Revisions:
	0.2	04/02/96	added flipping logic
	0.1	04/01/96	added support for board scanning
	0.0	03/29/96	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "othello.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif


/*
#define FLIP_DEBUG 1
*/


/******************************************************************************
*  FlipRow - flip a row of pieces to opposite color                           *
******************************************************************************/
void
FlipRow(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */


   current = data->data.board[pr][pc];

   found_end = FALSE;
   ec = 0;

   switch(dir)
   {
      case DIR_E:
         for (c = (pc + 1); c < data->screen.max_grid_col; c++)
         {
            if (data->data.board[pr][c] == current)
            {
               found_end = TRUE;
               ec = c;
               break;
            }
            else if (data->data.board[pr][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (c = (pc + 1); c < ec; c++)
            {
               data->data.board[pr][c] = TOGGLE_PLAYER(data->data.board[pr][c]);
            } 
         }
         break;

      case DIR_W:
         for (c = (pc - 1); c >= 0; c--)
         {
            if (data->data.board[pr][c] == current)
            {
               found_end = TRUE;
               ec = c;
               break;
            }
            else if (data->data.board[pr][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (c = (pc - 1); c > ec; c--)
            {
               data->data.board[pr][c] = TOGGLE_PLAYER(data->data.board[pr][c]);
            } 
         }
         break;

      default:
         break;
   }
}


/******************************************************************************
*  FlipColumn - flip a column of pieces to opposite color                     *
******************************************************************************/
void
FlipColumn(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */


   current = data->data.board[pr][pc];

   found_end = FALSE;
   er = 0;

   switch(dir)
   {
      case DIR_S:
         for (r = (pr + 1); r < data->screen.max_grid_row; r++)
         {
            if (data->data.board[r][pc] == current)
            {
               found_end = TRUE;
               er = r;
               break;
            }
            else if (data->data.board[r][pc] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr + 1); r < er; r++)
            {
               data->data.board[r][pc] = TOGGLE_PLAYER(data->data.board[r][pc]);
            } 
         }
         break;

      case DIR_N:
         for (r = (pr - 1); r >= 0; r--)
         {
            if (data->data.board[r][pc] == current)
            {
               found_end = TRUE;
               er = r;
               break;
            }
            else if (data->data.board[r][pc] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr - 1); r > er; r--)
            {
               data->data.board[r][pc] = TOGGLE_PLAYER(data->data.board[r][pc]);
            } 
         }
         break;

      default:
         break;
   }
}


/******************************************************************************
*  FlipDiag - flip a diagonal line of pieces to opposite color                *
******************************************************************************/
void
FlipDiag(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */


   current = data->data.board[pr][pc];

   found_end = FALSE;
   er = 0;
   ec = 0;

   switch(dir)
   {
      case DIR_NE:
         for (r = (pr - 1), c = (pc + 1); 
		((r >= 0) && (c < data->screen.max_grid_col)); r--, c++)
         {
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r;
               ec = c;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr - 1), c = (pc + 1); 
		((r > er) && (c < ec)); r--, c++)
            {
               data->data.board[r][c] = TOGGLE_PLAYER(data->data.board[r][c]);
            } 
         }
         break;

      case DIR_SE:
         for (r = (pr + 1), c = (pc + 1); 
		((r < data->screen.max_grid_row) && (c < data->screen.max_grid_col)); r++, c++)
         {
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r;
               ec = c;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr + 1), c = (pc + 1); 
		((r < er) && (c < ec)); r++, c++)
            {
               data->data.board[r][c] = TOGGLE_PLAYER(data->data.board[r][c]);
            } 
         }
         break;

      case DIR_SW:
         for (r = (pr + 1), c = (pc - 1); 
		((r < data->screen.max_grid_row) && (c >= 0)); r++, c--)
         {
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r;
               ec = c;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr + 1), c = (pc - 1); 
		((r < er) && (c > ec)); r++, c--)
            {
               data->data.board[r][c] = TOGGLE_PLAYER(data->data.board[r][c]);
            } 
         }
         break;

      case DIR_NW:
         for (r = (pr - 1), c = (pc - 1); 
		((r >= 0) && (c >= 0)); r--, c--)
         {
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r;
               ec = c;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
            for (r = (pr - 1), c = (pc - 1); 
		((r > er) && (c > ec)); r--, c--)
            {
               data->data.board[r][c] = TOGGLE_PLAYER(data->data.board[r][c]);
            } 
         }
         break;

      default:
         break;
   }
}


/* end of flip.c */
