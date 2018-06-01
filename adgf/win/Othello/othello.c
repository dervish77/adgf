/***********************************************************************

 The classic game of Othello.

   File:  	othello.c

   Author: 	Brian Lingard

   Date:	3/29/96

   Revisions:
	0.6	11/10/97	added keyboard commands
	0.5	09/11/97	added corners skill level code
	0.4	08/09/97	added random skill level code
	0.3	04/03/96	added demo mode
	0.2	04/02/96	added flipping logic and simple 
				computer algorithm
	0.1	04/01/96	added support for board scanning
	0.0	03/29/96	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>

#ifndef _MAIN_H
#include "main.h"		/* already includes "othello.h" */
#endif



/*
#define OTHELLO_DEBUG
*/

#define COUNT_DEBUG



/* 
 *  LOCAL STATIC GLOBALS
 */
BOOLEAN_T init_once = FALSE;	/* init control flag */



/******************************************************************************
*  InitScreen - initializes screen attributes                                 *
******************************************************************************/
void
InitScreen(MyProgram *data)
{
   data->screen.screen_x_size = SCREEN_X_SIZE;
   data->screen.screen_y_size = SCREEN_Y_SIZE;
   data->screen.score_x_size = SCORE_X_SIZE;
   data->screen.score_y_size = SCORE_Y_SIZE;
   data->screen.max_grid_row = MAX_GRID_ROW;
   data->screen.max_grid_col = MAX_GRID_COL;
   data->screen.piece_diameter = PIECE_DIAMETER;
   data->screen.grid_size = GRID_SIZE;
   data->screen.total_num_pieces = TOTAL_NUM_PIECES;
}


/******************************************************************************
*  InitBoard - initializes game board                                         *
******************************************************************************/
void
InitBoard(MyProgram *data)
{
   int half_r, half_c;
   int r, c;

   half_r = data->screen.max_grid_row / 2;
   half_c = data->screen.max_grid_col / 2;

   for (r = 0; r < data->screen.max_grid_row; r++)
   {
      for (c = 0; c < data->screen.max_grid_col; c++)
      {
          if ( ((r == (half_r - 1)) && (c == (half_c - 1))) 
			|| ((r == (half_r)) && (c == (half_c))) )
          {
             data->data.board[r][c] = PIECE_PLAYER_1;
          }
          else if ( ((r == (half_r - 1)) && (c == (half_c))) 
			|| ((r == (half_r)) && (c == (half_c - 1))) )
          {
             data->data.board[r][c] = PIECE_PLAYER_2;
          }
          else
          {
             data->data.board[r][c] = PIECE_EMPTY;
          }
      }
   }
}


/******************************************************************************
*  InitGrid - initializes grid                                                *
******************************************************************************/
void
InitGrid(MyProgram *data)
{
   int r, c;


   /*  init grid items 
    */
   data->grid.draw_grid_flag = TRUE;
   data->grid.size.x = data->screen.screen_x_size / data->screen.max_grid_col;
   data->grid.size.y = data->screen.screen_y_size / data->screen.max_grid_row;

   /* init bounding box points */
   for (r = 0; r < data->screen.max_grid_row; r++)
   {
      for (c = 0; c < data->screen.max_grid_col; c++)
      {
         data->grid.top_left[r][c].x = data->grid.size.x * c;
         data->grid.top_left[r][c].y = data->grid.size.y * r;

         data->grid.bot_right[r][c].x = data->grid.top_left[r][c].x 
							+ data->grid.size.x;
         data->grid.bot_right[r][c].y = data->grid.top_left[r][c].y 
							+ data->grid.size.y;
      }
   }
}


/******************************************************************************
*  InitScore - initializes score                                              *
******************************************************************************/
void
InitScore(MyProgram *data)
{

   data->score.player1_color = 0;
   data->score.player1_score = 2;

   data->score.plyr1_label.x = 50;
   data->score.plyr1_label.y = (data->screen.score_y_size / 3) * 2;

   data->score.box1_top_left.x = 5;
   data->score.box1_top_left.y = 5;

   data->score.player2_color = 0;
   data->score.player2_score = 2;

   data->score.plyr2_label.x = (data->screen.score_x_size / 2) + 50;
   data->score.plyr2_label.y = (data->screen.score_y_size / 3) * 2;

   data->score.box2_top_left.x = (data->screen.score_x_size / 2) + 5;
   data->score.box2_top_left.y = 5;
}


/******************************************************************************
*  InitDatabase - initializes pointers to global database arrays              *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{

   /*  init general items 
    */
   data->game_loaded = FALSE;
   data->game_saved = FALSE;
   data->load_file_name[0] = '\0';
   data->save_file_name[0] = '\0';
   data->load_file = (FILE *) NULL;
   data->save_file = (FILE *) NULL;
   data->mouse_pick.x = 0;
   data->mouse_pick.y = 0;


   /*  init game items 
    */
   data->data.game_in_progress = FALSE;
   data->data.network_game = FALSE;
   data->data.current_player = PIECE_PLAYER_1;


   /*  init these items only if first time through
    */
   if (init_once == FALSE) 
   { 
      data->data.player_mode = PLAYER_SINGLE;
      data->data.skill_level = SKILL_NONE;
      init_once = TRUE;
   }

   InitBoard(data);

   InitGrid(data);

   InitScore(data);
}


/******************************************************************************
*  LoadGame - loads saved game file                                           *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*  othello                                                                    *
*  p_mode                                                                     *
*  skill_level                                                                *
*  current_player                                                             *
*  plyr_1_score                                                               *
*  plyr_2_score                                                               *
*  bd0-0 bd0-1 ... bd0-c                                                      *
*  ...                                                                        *
*  bdr-0 bdr-1 ... bdr-c                                                      *
*                                                                             *
******************************************************************************/
void
LoadGame(MyProgram *data)
{
   FILE *infile;
   int r, c;
   BUFFER_T string;


   infile = data->load_file;

   fscanf(infile, "%s\n", string);

   if ( strncmp( string, "othello", 7) == 0)
   {
      fscanf(infile, "%d\n", &(data->data.player_mode));
      fscanf(infile, "%d\n", &(data->data.skill_level));
      fscanf(infile, "%d\n", &(data->data.current_player));
      fscanf(infile, "%d\n", &(data->score.player1_score));
      fscanf(infile, "%d\n", &(data->score.player2_score));

      for (r = 0; r < data->screen.max_grid_row; r++)
      {
         for (c = 0; c < data->screen.max_grid_col; c++)
         {
            fscanf(infile, "%d ", &(data->data.board[r][c]));
         }
         fscanf(infile, "\n");
      }

      UpdateDisplay(data);
   }
   else
   {
      fprintf(stderr, "LoadGame:  unknown file format\n");
      exit(1);
   }
}


/******************************************************************************
*  SaveGame - saves current game to file                                      *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*  othello                                                                    *
*  p_mode                                                                     *
*  skill_level                                                                *
*  current_player                                                             *
*  plyr_1_score                                                               *
*  plyr_2_score                                                               *
*  bd0-0 bd0-1 ... bd0-c                                                      *
*  ...                                                                        *
*  bdr-0 bdr-1 ... bdr-c                                                      *
*                                                                             *
******************************************************************************/
void
SaveGame(MyProgram *data)
{
   FILE *outfile;
   int r, c;


   outfile = data->save_file;

   fprintf(outfile, "othello\n");

   fprintf(outfile, "%d\n", data->data.player_mode);
   fprintf(outfile, "%d\n", data->data.skill_level);
   fprintf(outfile, "%d\n", data->data.current_player);
   fprintf(outfile, "%d\n", data->score.player1_score);
   fprintf(outfile, "%d\n", data->score.player2_score);

   for (r = 0; r < data->screen.max_grid_row; r++)
   {
      for (c = 0; c < data->screen.max_grid_col; c++)
      {
         fprintf(outfile, "%d ", data->data.board[r][c]);
      }
      fprintf(outfile, "\n");
   }
}


/******************************************************************************
*  GameIsOver - determine if game is over and who is the winner               *
******************************************************************************/
BOOLEAN_T
GameIsOver(MyProgram *data)
{
   int 		sum;		/* sum of both player's scores */
   BOOLEAN_T 	game_is_over;	/* flag for game is over */

#if 0
   int		r, c, count_1, count_2;

   count_1 = count_2 = 0;

   for (r = 0 ; r < data->screen.max_grid_row ; r++)
   {
      for (c = 0 ; c < data->screen.max_grid_col ; c++)
      {
         if (data->data.board[r][c] == PIECE_PLAYER_1)
         {
            count_1++;
         }
         else if (data->data.board[r][c] == PIECE_PLAYER_2)
         {
            count_2++;
         }
      }
   }

   data->score.player1_score = count_1;
   data->score.player2_score = count_2;
#endif

   game_is_over = FALSE;

   sum = data->score.player1_score + data->score.player2_score;

   if (sum == data->screen.total_num_pieces)
   {
      game_is_over = TRUE;

      if (data->score.player1_score > data->score.player2_score)
      {
         data->data.winning_player = PIECE_PLAYER_1;
      }
      else if (data->score.player1_score < data->score.player2_score)
      {
         data->data.winning_player = PIECE_PLAYER_2;
      }
      else	/* it's a tie! */
      {
         data->data.winning_player = PIECE_EMPTY;
      }
   }
   else if ( data->score.player2_score == 0 )
   {
      data->data.winning_player = PIECE_PLAYER_1;
      game_is_over = TRUE;
   }
   else if ( data->score.player1_score == 0 )
   {
      data->data.winning_player = PIECE_PLAYER_2;
      game_is_over = TRUE;
   }

   return(game_is_over);
}


/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{
   int r, c;			/* loop indices */
   int count_1, count_2;	/* counts of each player's pieces */


   /*  clear screen and redraw grid
    */
//   ClearScreenDisplay(data->draw_area_widget);

//   DrawGrid(data);


   /*  scan through the board array and draw each piece 
    *  if a position is not empty
    */
   count_1 = count_2 = 0;

   for (r = 0; r < data->screen.max_grid_row; r++)
   {
      for (c = 0; c < data->screen.max_grid_col; c++)
      {
         if (data->data.board[r][c] != PIECE_EMPTY)
         {
//           DrawPiece(data, r, c);

            if (data->data.board[r][c] == PIECE_PLAYER_1)
               count_1++;
            else
               count_2++;
         }
      }
   }


   /*  update scores and update display 
    */
   data->score.player1_score = count_1;
   data->score.player2_score = count_2;

//   DrawScore(data);
}


/******************************************************************************
*  HandleBoard  - handle processing for board size change                     *
******************************************************************************/
void
HandleBoard(MyProgram *data, int size)
{
   data->screen.max_grid_row = size;
   data->screen.max_grid_col = size;
   data->screen.grid_size = data->screen.screen_x_size / size;
   data->screen.piece_diameter = data->screen.grid_size - 4;
   data->screen.total_num_pieces = size * size;

   InitDatabase(data);
//   UpdateDisplay(data);
}


/******************************************************************************
*  HandleNewGame  - handle processing for new game                            *
******************************************************************************/
void
HandleNewGame(MyProgram *me)
{
   InitDatabase(me);
//   UpdateDisplay(me);

   printf("New Game\n");
}


/******************************************************************************
*  HandleLoadGame  - handle processing for load game                          *
******************************************************************************/
void
HandleLoadGame(MyProgram *me)
{
   char *new_file_name;
   int okay;


   if (strlen(me->load_file_name) == 0)
   {
//      new_file_name = PopupFileRequest("Enter file name to load as (file.osg)\n");

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->load_file_name, new_file_name);
         else 
         {
            strncpy(me->load_file_name, new_file_name, FILE_STRING_LEN);
            me->load_file_name[FILE_STRING_LEN - 1] = '\0';
         }

         okay = TRUE;
      }
   }
   else
   {
      okay = TRUE;
   }

   if (okay)
   {
      me->load_file = fopen(me->load_file_name, "r");
      if (me->load_file == (FILE *) NULL)
      {
         fprintf(stderr, 
		"file_load: can't open '%s' as game save file\n", 
		me->load_file_name);
         exit(1);
      }

      LoadGame(me);

      me->game_loaded = TRUE;

      fclose(me->load_file);

      printf("done loading\n");
   }
   else
   {
      printf("load cancelled\n");
   }
}


/******************************************************************************
*  HandleSaveGame  - handle processing for save game                          *
******************************************************************************/
void
HandleSaveGame(MyProgram *me)
{
   char *new_file_name;
   int okay;

   if (strlen(me->save_file_name) == 0)
   {
//      new_file_name = PopupFileRequest("Enter file name to save as (file.osg)\n");

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->save_file_name, new_file_name);
         else 
         {
            strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
            me->save_file_name[FILE_STRING_LEN - 1] = '\0';
         }

         okay = TRUE;
      }
   }
   else
   {
      okay = TRUE;
   }

   if (okay)
   {
      me->save_file = fopen(me->save_file_name, "w");
      if (me->save_file == (FILE *) NULL)
      {
         fprintf(stderr, 
		"file_save: can't open '%s' as game save file\n", 
		me->save_file_name);
         exit(1);
      }

      SaveGame(me);

      me->game_saved = TRUE;

      fclose(me->save_file);

      printf("done saving\n");
   }
   else
   {
      printf("save cancelled\n");
   }
}


/******************************************************************************
*  HandlePlayerMove - handle player's move                                    *
******************************************************************************/
BOOLEAN_T
HandlePlayerMove(MyProgram *data, int pr, int pc)
{
   BOOLEAN_T legal_move;	/* flag for if player's move is legal */


   legal_move = FALSE;

#ifdef OTHELLO_DEBUG
   printf("Player %d is moved to %d,%d\n\n", 
	data->data.current_player, pr, pc);
#endif

   /*  if picked cell is empty, scan the board to  
    *  determine if it is a legal move
    */
   if (data->data.board[pr][pc] == PIECE_EMPTY)
   {
      if ( ScanBoard(data, pr, pc) == TRUE )	/* if legal move */
      {
         /* mark this position as current player */
         data->data.board[pr][pc] = data->data.current_player;

         /* flip enemies' pieces */
         HandleFlip(data, pr, pc);

         legal_move = TRUE;
      }
   }

   if (!legal_move)
   {
      printf("Illegal move (%d,%d) for player - %d !!\n", 
	pr, pc, data->data.current_player);
   }

   return(legal_move);
}


/******************************************************************************
*  HandleGetMoveList - searches board for list of legal moves                 *
*
*  returns number of moves found
******************************************************************************/
int
HandleGetMoveList(MyProgram *data, int row[], int col[], int max_moves)
{
   int 		num_moves = 0;	     /* number of computer moves */
   int 		r, c;	 	     /* loop indices */

   /*  scan through board array until max_moves legal move(s) are found 
    */
   for (r = 0; r < data->screen.max_grid_row; r++)
   {
      for (c = 0; c < data->screen.max_grid_col; c++)
      {
         if ( (data->data.board[r][c] == PIECE_EMPTY)
		&& (ScanBoard(data, r, c) == TRUE) )	/* if legal move */
         {
            row[num_moves] = r;
            col[num_moves] = c;

            num_moves++;

            if (num_moves > max_moves)
            {
               num_moves = max_moves;
               break;
            }
         }
      }

      if (num_moves == max_moves)
      {
         break;
      }
   }

   return( num_moves );
}


/******************************************************************************
*  HandleHint - handle showing the player a hint                              *
*                                                                             *
*    Note:  current algorithm just looks for first valid move                 *
*                                                                             *
******************************************************************************/
void
HandleHint(MyProgram *data)
{
   int		mvrow, mvcol;
   int		row[MAX_MOVES];      /* array of row moves */
   int 		col[MAX_MOVES];      /* array of col moves */

   /*  get move list of first legal move 
    */
   if (HandleGetMoveList( data, row, col, 1) == 0)
   {
      printf("No move found for player - %d !\n", data->data.current_player);
//      PopupNoMoveFound(data);
   }
   else
   {
      mvrow = row[0];
      mvcol = col[0];
      printf("Found hint at %d,%d\n", mvrow, mvcol);
//      DrawHint(data, mvrow, mvcol);
   }
}


/******************************************************************************
*  HandlePass - handle player passing this move                               *
******************************************************************************/
void
HandlePass(MyProgram *data)
{
   if (data->data.player_mode == PLAYER_SINGLE)
   {
      data->data.current_player = TOGGLE_PLAYER(data->data.current_player);
      UpdateDisplay(data);

      HandleComputerMove(data);

      data->data.current_player = TOGGLE_PLAYER(data->data.current_player);
      UpdateDisplay(data);

      if ( GameIsOver(data) )
      {
//         PopupWinner(data);
      }
   }
   else
   {
      data->data.current_player = TOGGLE_PLAYER(data->data.current_player);
      UpdateDisplay(data);
   }
}


/******************************************************************************
*  HandleSkillNone - handle computer's move at skill level 0                  *
*                                                                             *
*    Note:  current algorithm just looks for first valid move and takes it.   *
*                                                                             *
******************************************************************************/
void
HandleSkillNone(MyProgram *data)
{
   int		mvrow, mvcol;
   int		row[MAX_MOVES];      /* array of row moves */
   int 		col[MAX_MOVES];      /* array of col moves */

   /*  get move list of first legal move 
    */
   if (HandleGetMoveList( data, row, col, 1) == 0)
   {
      printf("No move found for computer!\n");
   }
   else
   {
      mvrow = row[0];
      mvcol = col[0];
      HandlePlayerMove(data, mvrow, mvcol); /* handle computer move */
   }
}


/******************************************************************************
*  HandleSkillRandom - handle computer's move at skill level 1                *
******************************************************************************/
void
HandleSkillRandom(MyProgram *data)
{
   int 		num_moves = 0;	     /* number of computer moves */
   int		random_move;         /* random computer move */
   int		mvrow, mvcol;
   int		row[MAX_MOVES];      /* array of row moves */
   int 		col[MAX_MOVES];      /* array of col moves */

   /*  get move list of legal moves 
    */
   num_moves = HandleGetMoveList( data, row, col, MAX_MOVES);

   if ( num_moves == 0 )
   {
      printf("No move found for computer!\n");
   }
   else
   {
      random_move = int_random(1, num_moves);
      mvrow = row[random_move - 1];
      mvcol = col[random_move - 1];
      HandlePlayerMove(data, mvrow, mvcol); /* handle computer move */
   }
}

/******************************************************************************
*  PickMinDistance - pick move with shortest distance to corner               *
******************************************************************************/
int
PickMinDistance( float dist[], int count )
{
   float num1;
   int   idx1;
   int   i;

   num1 = dist[0];
   idx1 = 0;

   for (i = 1; i < count; i++)
   {
      if ( dist[i] < num1 )
      {
         num1 = dist[i];
         idx1 = i;
      }
   }

   return(idx1);
}


/******************************************************************************
*  CalcDistance2Corner - calculate distance to nearest corner                 *
******************************************************************************/
float
CalcDistance2Corner(MyProgram *data, int r, int c)
{
   float dist[4], temp;
   int   index;

   /* distance to 0,0 */
   temp = (float) ((r) * (r)) + ((c) * (c));
   dist[0] = (float) SQRT_FUNC(temp);

   /* distance to 0,C */
   temp = (float) ((r) * (r)) + ((c - data->screen.max_grid_col) * (c - data->screen.max_grid_col));
   dist[1] = (float) SQRT_FUNC(temp);

   /* distance to R,0 */
   temp = (float) ((r - data->screen.max_grid_row) * (r - data->screen.max_grid_row)) + ((c) * (c));
   dist[2] = (float) SQRT_FUNC(temp);

   /* distance to R,C */
   temp = (float) ((r - data->screen.max_grid_row) * (r - data->screen.max_grid_row)) 
		+ ((c - data->screen.max_grid_col) * (c - data->screen.max_grid_col));
   dist[3] = (float) SQRT_FUNC(temp);

   /* pick shortest distance */
   index = PickMinDistance( dist, 4 );

   return(dist[index]);
}


/******************************************************************************
*  HandleSkillCorners - handle computer's move at skill level 2               *
******************************************************************************/
void
HandleSkillCorners(MyProgram *data)
{
   int 		num_moves = 0;	     /* number of computer moves */
   int		min_dist_idx;	     /* index of move with min distance */
   int 		i;	             /* loop indices */

   float	dist[MAX_MOVES];     /* array of distance to corner */

   int		mvrow, mvcol;
   int		row[MAX_MOVES];      /* array of row moves */
   int 		col[MAX_MOVES];      /* array of col moves */

   /*  get move list of legal moves 
    */
   num_moves = HandleGetMoveList( data, row, col, MAX_MOVES);

   if ( num_moves == 0)
   {
      printf("No move found for computer!\n");
   }
   else
   {
      for (i = 0; i < num_moves; i++)
      {
         dist[i] = CalcDistance2Corner( data, row[i], col[i] );
#ifdef OTHELLO_DEBUG
         printf("  move %d,%d dist %f\n", row[i], col[i], dist[i]);
#endif
      }

      min_dist_idx = PickMinDistance( dist, num_moves );
#ifdef OTHELLO_DEBUG
      printf("  min_dist_idx = %d\n", min_dist_idx);
#endif

      mvrow = row[min_dist_idx];
      mvcol = col[min_dist_idx];
      HandlePlayerMove(data, mvrow, mvcol); /* handle computer move */
   }

}


/******************************************************************************
*  HandleSkillMaxFlip - handle computer's move at skill level 3               *
******************************************************************************/
void
HandleSkillMaxFlip(MyProgram *data)
{
   int		num_moves = 0;        /* number of computer moves */
   int		i;                    /* loop indices */
   int		count;
   
   int 		row[MAX_MOVES];
   int		col[MAX_MOVES];

   /*  get move list of legal moves
    */
   num_moves = HandleGetMoveList( data, row, col, MAX_MOVES);

   if ( num_moves == 0 )
   {
      printf("No move found for computer!\n");
   }
   else
   {
      printf("\n");
      for (i = 0; i < num_moves; i++)
      {
         count = HandleCount( data, row[i], col[i] );

         printf("Move %d,%d count = %d\n", row[i], col[i], count);
      }
   }

   HandleSkillNone(data);
}


/******************************************************************************
*  BadMove - returns TRUE if move is (1,1), (1,C-1), etc.                     *
******************************************************************************/
BOOLEAN_T
BadMove(MyProgram *data, int r, int c)
{
   BOOLEAN_T retval = FALSE;

   if ( r == 1 && c == 1 ) 
      retval = TRUE;
   else if ( r == 1 && c == (data->screen.max_grid_col - 1) ) 
      retval = TRUE;
   else if ( r == (data->screen.max_grid_row - 1) && c == 1 ) 
      retval = TRUE;
   else if ( r == (data->screen.max_grid_row - 1) && c == (data->screen.max_grid_col - 1) ) 
      retval = TRUE;

printf("bad move = %d\n", retval);

   return(retval);
}


/******************************************************************************
*  HandleSkillAI - handle computer's move at skill level 4                    *
******************************************************************************/
void
HandleSkillAI(MyProgram *data)
{
   int 		num_moves = 0;	     /* number of computer moves */
   int		min_dist_idx;	     /* index of move with min distance */
   int 		i;	             /* loop indices */

   float	dist[MAX_MOVES];     /* array of distance to corner */

   int		random_move;         /* random computer move */
   int		mvrow, mvcol;
   int		row[MAX_MOVES];      /* array of row moves */
   int 		col[MAX_MOVES];      /* array of col moves */

   /*  get move list of legal moves 
    */
   num_moves = HandleGetMoveList( data, row, col, MAX_MOVES);

   if ( num_moves == 0)
   {
      printf("No move found for computer!\n");
   }
   else
   {
      for (i = 0; i < num_moves; i++)
      {
         dist[i] = CalcDistance2Corner( data, row[i], col[i] );
#ifdef OTHELLO_DEBUG
         printf("  move %d,%d dist %f\n", row[i], col[i], dist[i]);
#endif
      }

      min_dist_idx = PickMinDistance( dist, num_moves );
#ifdef OTHELLO_DEBUG
      printf("  min_dist_idx = %d\n", min_dist_idx);
#endif

      mvrow = row[min_dist_idx];
      mvcol = col[min_dist_idx];

      if ( BadMove(data, mvrow, mvcol) )
      {
         random_move = int_random(1, num_moves);
         mvrow = row[random_move - 1];
         mvcol = col[random_move - 1];
      }

      HandlePlayerMove(data, mvrow, mvcol); /* handle computer move */
   }
}


/******************************************************************************
*  HandleComputerMove - handle computer's move                                *
******************************************************************************/
void
HandleComputerMove(MyProgram *data)
{
   switch(data->data.skill_level)
   {
      case SKILL_NONE:
         HandleSkillNone(data);
         break;
      case SKILL_RANDOM:
         HandleSkillRandom(data);
         break;
      case SKILL_CORNERS:
         HandleSkillCorners(data);
         break;
      case SKILL_MAXFLIP:
         HandleSkillMaxFlip(data);
         break;
      case SKILL_AI:
         HandleSkillAI(data);
         break;
      default:
         break;
   }
}


/******************************************************************************
*  HandleFlip - handle flipping enemies' pieces                               *
******************************************************************************/
void
HandleFlip(MyProgram *data, int pr, int pc)
{
   FlipRow(data, pr, pc, DIR_E);
   FlipRow(data, pr, pc, DIR_W);

   FlipColumn(data, pr, pc, DIR_N);
   FlipColumn(data, pr, pc, DIR_S);

   FlipDiag(data, pr, pc, DIR_NE);
   FlipDiag(data, pr, pc, DIR_SE);
   FlipDiag(data, pr, pc, DIR_SW);
   FlipDiag(data, pr, pc, DIR_NW);
}


/******************************************************************************
*  HandleCount - handle counting number of flips                              *
******************************************************************************/
int
HandleCount(MyProgram *data, int pr, int pc)
{
   int count;	/* total flip count */
   int e, w, n, s, ne, se, sw, nw;

   e = CountRow(data, pr, pc, DIR_E);
   w = CountRow(data, pr, pc, DIR_W);

   n = CountColumn(data, pr, pc, DIR_N);
   s = CountColumn(data, pr, pc, DIR_S);

   ne = CountDiag(data, pr, pc, DIR_NE);
   se = CountDiag(data, pr, pc, DIR_SE);
   sw = CountDiag(data, pr, pc, DIR_SW);
   nw = CountDiag(data, pr, pc, DIR_NW);

   count = e + w + n + s + ne + se + sw + nw;

   return(count);
}


/******************************************************************************
*  HandleKeyPress - handle key press                                          *
******************************************************************************/
void
HandleKeyPress(char key, MyProgram *data)
{
   switch(key)
   {
      case KEY_NEWGAME:
         HandleNewGame( data );
         break;

      case KEY_OPENGAME:
         HandleLoadGame( data );
         break;

      case KEY_SAVEGAME:
         HandleSaveGame( data );
         break;

      case KEY_QUITGAME:
         exit(0);
         break;

      case KEY_EXITGAME:
         exit(0);
         break;

      case KEY_HINT:
         HandleHint( data );
         break;

      case KEY_PASS:
         HandlePass( data );
         break;

      default:
         break;
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


/* 
 * nrand() - normalized rand(), returns floating point random number
 *		between -1.0 and 1.0
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	rand	- normalized random number
 *
 */
float nrand(void)
{
   return( (float) (2.0*(rand() / (float)RAND_MAX) - 1.0) );
}


/* 
 * int_random() - scaled integer random number 
 *
 * PARAMETERS
 *	min_value	- minimum value
 *	max_value	- maximum value
 *
 * RETURNS
 *	int_rand_num	- scaled random number
 *
 */
int int_random(int min_value, int max_value)
{
   float rand_raw, rand_num;
   int int_rand_num;

   /*  set seed value to current time in seconds
    */
   srand((unsigned int)time(NULL));

   /*  get raw random number
    */
   rand_raw = nrand();

   /*  make it positive
    */
   if (rand_raw < 0)
   {
      rand_raw = rand_raw * (-1);
   }
 
   /*  scale by min and max values
    */
   rand_num = ((max_value - min_value) * rand_raw) + min_value;

   /*  convert to integer and output
    */
   int_rand_num = (int) rand_num;

   return(int_rand_num);
}

#if 0
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
#endif


/* end of othello.c */
