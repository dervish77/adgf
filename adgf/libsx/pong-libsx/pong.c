/***********************************************************************

 The classic game of Pong.

   File:  	pong.c

   Author: 	Brian Lingard

   Date:	10/29/98

   Revisions:
	0.0	10/29/98	Originated

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
#include "main.h"		/* already includes "pong.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif


/*
#define PONG_DEBUG
*/




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

   data->score.player1_color = PLAYER_1_COLOR;
   data->score.player1_score = 2;

   data->score.plyr1_label.x = 50;
   data->score.plyr1_label.y = (data->screen.score_y_size / 3) * 2;

   data->score.box1_top_left.x = 5;
   data->score.box1_top_left.y = 5;

   data->score.player2_color = PLAYER_2_COLOR;
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
      data->data.skill_level = SKILL_1;
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
*  pong                                                                       *
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

   if ( strncmp( string, "pong", 7) == 0)
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

   fprintf(outfile, "pong\n");

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


   game_is_over = FALSE;


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
   ClearScreenDisplay(data->draw_area_widget);

   DrawGrid(data);


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
            DrawPiece(data, r, c);

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

   DrawScore(data);
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
   UpdateDisplay(data);
}


/******************************************************************************
*  HandleNewGame  - handle processing for new game                            *
******************************************************************************/
void
HandleNewGame(MyProgram *me)
{
   InitDatabase(me);
   UpdateDisplay(me);

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
      new_file_name = PopupFileRequest("Enter file name to load as (file.osg)\n");

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
      new_file_name = PopupFileRequest("Enter file name to save as (file.osg)\n");

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
   int count;


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

   }

   if (!legal_move)
   {
      printf("Illegal move (%d,%d) for player - %d !!\n", 
	pr, pc, data->data.current_player);
   }

   return(legal_move);
}


/******************************************************************************
*  HandleComputerMove - handle computer's move                                *
******************************************************************************/
void
HandleComputerMove(MyProgram *data)
{
   switch(data->data.skill_level)
   {
      default:
         break;
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
   return(2.0*(rand() / (float)RAND_MAX) - 1.0);
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



/* end of othello.c */
