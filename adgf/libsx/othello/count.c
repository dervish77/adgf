/***********************************************************************

 Count flip logic for Othello game.

   File:  	count.c

   Author: 	Brian Lingard

   Date:	09/17/97

   Revisions:
	0.0	09/17/97	Originated, based on flip.c

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




/******************************************************************************
*  CountRow - counts number of flips in a row                                 *
******************************************************************************/
int
CountRow(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */
   int		count;		/* flip count */

   current = data->data.board[pr][pc];

   found_end = FALSE;
   ec = 0;
   count = 0;

   switch(dir)
   {
      case DIR_E:
         for (c = (pc + 1); c < data->screen.max_grid_col; c++)
         {
printf("row e, c = %d, player = %d\n", c, data->data.board[pr][c]);
            if (data->data.board[pr][c] == current)
            {
               found_end = TRUE;
               ec = c - 1;
               break;
            }
            else if (data->data.board[pr][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("row e, pc = %d, ec = %d\n", pc, ec);
            for (c = (pc + 1); c < ec; c++)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      case DIR_W:
         for (c = (pc - 1); c >= 0; c--)
         {
printf("row w, c = %d, player = %d\n", c, data->data.board[pr][c]);
            if (data->data.board[pr][c] == current)
            {
               found_end = TRUE;
               ec = c + 1;
               break;
            }
            else if (data->data.board[pr][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("row w, pc = %d, ec = %d\n", pc, ec);
            for (c = (pc - 1); c > ec; c--)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      default:
         break;
   }

   return(count);
}


/******************************************************************************
*  CountColumn - counts number of flips in a column                           *
******************************************************************************/
int
CountColumn(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */
   int		count;		/* flip count */


   current = data->data.board[pr][pc];

   found_end = FALSE;
   er = 0;
   count = 0;

   switch(dir)
   {
      case DIR_S:
         for (r = (pr + 1); r < data->screen.max_grid_row; r++)
         {
printf("col s, r = %d, player = %d\n", r, data->data.board[pr][c]);
            if (data->data.board[r][pc] == current)
            {
               found_end = TRUE;
               er = r - 1;
               break;
            }
            else if (data->data.board[r][pc] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("col s, pr = %d, er = %d\n", pr, er);
            for (r = (pr + 1); r < er; r++)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      case DIR_N:
         for (r = (pr - 1); r >= 0; r--)
         {
printf("col n, r = %d, player = %d\n", r, data->data.board[pr][c]);
            if (data->data.board[r][pc] == current)
            {
               found_end = TRUE;
               er = r + 1;
               break;
            }
            else if (data->data.board[r][pc] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("col n, pr = %d, er = %d\n", pr, er);
            for (r = (pr - 1); r > er; r--)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      default:
         break;
   }

   return(count);
}


/******************************************************************************
*  CountDiag - counts number of flips on a diagonal line                      *
******************************************************************************/
int
CountDiag(MyProgram *data, int pr, int pc, DIRECTION_T dir)
{
   int 		r, c;		/* loop indices */
   int 		er, ec;		/* end row and end column */
   PIECE_T	current;	/* current player piece at pick r,c */
   BOOLEAN_T	found_end;	/* flag for found end of line */
   int		count; 		/* flip count */


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
printf("diag ne, r = %d, c = %d, player = %d\n", r, c, data->data.board[pr][c]);
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r + 1;
               ec = c - 1;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("diag ne, pr = %d, pc = %d, er = %d, ec = %d\n", pr, pc, er, ec);
            for (r = (pr - 1), c = (pc + 1); 
		((r > er) && (c < ec)); r--, c++)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      case DIR_SE:
         for (r = (pr + 1), c = (pc + 1); 
		((r < data->screen.max_grid_row) && (c < data->screen.max_grid_col)); r++, c++)
         {
printf("diag se, r = %d, c = %d, player = %d\n", r, c, data->data.board[pr][c]);
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r - 1;
               ec = c - 1;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("diag se, pr = %d, pc = %d, er = %d, ec = %d\n", pr, pc, er, ec);
            for (r = (pr + 1), c = (pc + 1); 
		((r < er) && (c < ec)); r++, c++)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      case DIR_SW:
         for (r = (pr + 1), c = (pc - 1); 
		((r < data->screen.max_grid_row) && (c >= 0)); r++, c--)
         {
printf("diag sw, r = %d, c = %d, player = %d\n", r, c, data->data.board[pr][c]);
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r - 1;
               ec = c + 1;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("diag sw, pr = %d, pc = %d, er = %d, ec = %d\n", pr, pc, er, ec);
            for (r = (pr + 1), c = (pc - 1); 
		((r < er) && (c > ec)); r++, c--)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      case DIR_NW:
         for (r = (pr - 1), c = (pc - 1); 
		((r >= 0) && (c >= 0)); r--, c--)
         {
printf("diag nw, r = %d, c = %d, player = %d\n", r, c, data->data.board[pr][c]);
            if (data->data.board[r][c] == current)
            {
               found_end = TRUE;
               er = r + 1;
               ec = c + 1;
               break;
            }
            else if (data->data.board[r][c] == PIECE_EMPTY)
            {
               break;
            }
         }
         if (found_end)
         {
printf("diag nw, pr = %d, pc = %d, er = %d, ec = %d\n", pr, pc, er, ec);
            for (r = (pr - 1), c = (pc - 1); 
		((r > er) && (c > ec)); r--, c--)
            {
               count += 1;
            } 
printf("count = %d\n", count);
         }
         break;

      default:
         break;
   }

   return(count);
}


/* end of count.c */
