/***********************************************************************

 Main game routines for StarFire.

   File:  	starfire.c

   Author: 	Brian Lingard

   Date:	10/05/97

   Revisions:
	0.0	10/05/97	Originated

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

#ifndef _CALLBACK_H
#include "callback.h"
#endif




/* 
 *  LOCAL STATIC GLOBALS
 */
BOOLEAN_T init_once = FALSE;	/* init control flag */



/******************************************************************************
*  InitBoard - initializes game board structure                               *
******************************************************************************/
void
InitBoard(MyProgram *data)
{
   int r, c;

   printf("Initializing board ...\n");

   seed_random();

   /* clear the board */
   for (r = 0; r < MAX_GRID_ROW; r++)
   {
      for (c = 0; c < MAX_GRID_COL; c++)
      {
         data->data.map[r][c] = ICON_NONE;
         data->data.board[r][c] = ICON_NONE;      
      }
   }

   /* place obstructions */
   printf("   placing obstructions ...\n");
   PlaceIcon( ICON_UFO, MAX_UFOS, data );
   PlaceIcon( ICON_PLANET, MAX_PLANETS, data );
   PlaceIcon( ICON_ROID, MAX_ROIDS, data );
   PlaceIcon( ICON_BHOLE, MAX_BHOLES, data );
   PlaceIcon( ICON_WORM, MAX_WORM, data );

   /* place power ups */
   printf("   placing power ups ...\n");
   PlaceIcon( ICON_AMMO, MAX_AMMO, data );
   PlaceIcon( ICON_HEALTH, MAX_HEALTH, data );
   PlaceIcon( ICON_WARP, MAX_WARP, data );
   PlaceIcon( ICON_SLAMMER, MAX_SLAMMER, data );

   /* place player's ship */
   printf("   placing player's ship ...\n");
   PlacePlayerIcon( MAX_GRID_ROW/2, MAX_GRID_COL/2, ICON_SHIPU, data );
}


/******************************************************************************
*  InitGrid - initializes grid structure                                      *
******************************************************************************/
void
InitGrid(int xsize, int ysize, MyProgram *data)
{
   int r, c;
   int x, y;

   printf("Initializing grid ...\n");

   data->grid.screen_size.x = xsize;
   data->grid.screen_size.y = ysize;

   data->grid.grid_size.x = xsize / MAX_GRID_COL;
   data->grid.grid_size.y = ysize / MAX_GRID_ROW;

   /* init bounding box points */
   for (r = 0; r < MAX_GRID_ROW; r++)
   {
      for (c = 0; c < MAX_GRID_COL; c++)
      {
         x = data->grid.grid_size.x * c;
         y = data->grid.grid_size.y * r;
         data->grid.top_left[r][c].x = x;
         data->grid.top_left[r][c].y = y;
      }
   }
}


/******************************************************************************
*  InitScore - initializes score structure                                    *
******************************************************************************/
void
InitScore(int xsize, int ysize, 
          int score, int health, int ammo, 
          MyProgram *data)
{
   printf("Initializing score ...\n");

   data->score.screen_size.x = xsize;
   data->score.screen_size.y = ysize;

   data->score.score = score;
   data->score.health = health;
   data->score.ammo = ammo;
   data->score.warp = 0;
   data->score.slammer = 0;

   data->score.score_label.x = 20;
   data->score.score_label.y = (ysize / 3) * 2;

   data->score.health_label.x = (xsize / 3) + 40;
   data->score.health_label.y = (ysize / 3) * 2;

   data->score.ammo_label.x = (xsize / 3) + (xsize / 3) + 40;
   data->score.ammo_label.y = (ysize / 3) * 2;

   data->score.warp_label.x = xsize - 20;
   data->score.warp_label.y = (ysize / 3);

   data->score.slammer_label.x = xsize - 20;
   data->score.slammer_label.y = ysize - 5;
}


/******************************************************************************
*  InitStatus - initializes status structure                                  *
******************************************************************************/
void
InitStatus(int xsize, int ysize, char *msg, MyProgram *data)
{
   printf("Initializing status ...\n");

   data->status.screen_size.x = xsize;
   data->status.screen_size.y = ysize;

   data->status.msg  = msg;

   data->status.status_label.x = 20;
   data->status.status_label.y = (ysize / 3) * 2;
}


/******************************************************************************
*  InitAnim - initializes anim structure                                      *
******************************************************************************/
void
InitAnim(int frame_rate, MyProgram *data)
{
   printf("Initializing animation ...\n");

   data->anim.enable_anim = FALSE;
   data->anim.frame_rate = frame_rate;
   data->anim.frame_count = 0;
   data->anim.frame_interval = (int) ((1.0 / (float)frame_rate) * (1000));

   printf("   calculated frame interval of %d ms\n", data->anim.frame_interval);

   data->anim.callback = (void *)next_frame;
}


/******************************************************************************
*  InitDatabase - initializes pointers to global database arrays              *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{
   fprintf(stdout, "Initializing game database...\n");

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
   data->data.player.current_player = PIECE_PLAYER_1;

   InitBoard( data );
   InitScore( SCORE_X_SIZE, SCORE_Y_SIZE, 0, 100, 10, data );
   InitStatus( STATUS_X_SIZE, STATUS_Y_SIZE, "Welcome to StarFire", data );


   /*  init these items only if first time through
    */
   if (init_once == FALSE) 
   { 
      data->data.player_mode = PLAYER_SINGLE;
      init_once = TRUE;

      InitAnim( DEFAULT_FRAME_RATE, data );
      InitGrid( SCREEN_X_SIZE, SCREEN_Y_SIZE, data );
      LoadIconArray( data );
   }
}


/******************************************************************************
*  LoadGame - loads saved game file                                           *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*  starfire                                                                   *
*  p_mode                                                                     *
*  current_player                                                             *
*  score                                                                      *
*  health                                                                     *
*  ammo                                                                       *
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

   if ( strncmp( string, "starfire", 8) == 0)
   {
      fscanf(infile, "%d\n", &(data->data.player_mode));
      fscanf(infile, "%d\n", &(data->data.player.current_player));
      fscanf(infile, "%d\n", &(data->data.player.current_row));
      fscanf(infile, "%d\n", &(data->data.player.current_col));
      fscanf(infile, "%d\n", &(data->score.score));
      fscanf(infile, "%d\n", &(data->score.health));
      fscanf(infile, "%d\n", &(data->score.ammo));

      for (r = 0; r < MAX_GRID_ROW; r++)
      {
         for (c = 0; c < MAX_GRID_COL; c++)
         {
            fscanf(infile, "%d ", &(data->data.map[r][c]));
         }
         fscanf(infile, "\n");
      }

      for (r = 0; r < MAX_GRID_ROW; r++)
      {
         for (c = 0; c < MAX_GRID_COL; c++)
         {
            fscanf(infile, "%d ", &(data->data.board[r][c]));
         }
         fscanf(infile, "\n");
      }

      UpdateDisplay(data);
      UpdateScore(data);
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
*  starfire                                                                   *
*  p_mode                                                                     *
*  current_player                                                             *
*  score                                                                      *
*  health                                                                     *
*  ammo                                                                       *
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

   fprintf(outfile, "starfire\n");

   fprintf(outfile, "%d\n", data->data.player_mode);
   fprintf(outfile, "%d\n", data->data.player.current_player);
   fprintf(outfile, "%d\n", data->data.player.current_row);
   fprintf(outfile, "%d\n", data->data.player.current_col);
   fprintf(outfile, "%d\n", data->score.score);
   fprintf(outfile, "%d\n", data->score.health);
   fprintf(outfile, "%d\n", data->score.ammo);

   for (r = 0; r < MAX_GRID_ROW; r++)
   {
      for (c = 0; c < MAX_GRID_COL; c++)
      {
         fprintf(outfile, "%d ", data->data.map[r][c]);
      }
      fprintf(outfile, "\n");
   }

   for (r = 0; r < MAX_GRID_ROW; r++)
   {
      for (c = 0; c < MAX_GRID_COL; c++)
      {
         fprintf(outfile, "%d ", data->data.board[r][c]);
      }
      fprintf(outfile, "\n");
   }
}


/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{
   int r, c;			/* loop indices */
   int idx;
   ICON_S_T *icon;


   /*  clear screen and redraw grid
    */
   ClearScreenDisplay(data->draw_area_widget);

   /*  scan through the map and board arrays 
    *  and draw each piece 
    *  if a position is not empty
    */
   for (r = 0; r < MAX_GRID_ROW; r++)
   {
      for (c = 0; c < MAX_GRID_COL; c++)
      {
         if (data->data.map[r][c] != PIECE_EMPTY)
         {
            idx = data->data.map[r][c];
            icon = &data->icons[idx];
            DrawIcon(data, icon, r, c);
         }

         if (data->data.board[r][c] != PIECE_EMPTY)
         {
            idx = data->data.board[r][c];
            icon = &data->icons[idx];
            DrawIcon(data, icon, r, c);
         }
      }
   }
}


/******************************************************************************
*  UpdateScore - update score display                                         *
******************************************************************************/
void
UpdateScore(MyProgram *data)
{
   DrawScore(data);
}


/******************************************************************************
*  UpdateStatus  - update status display                                      *
******************************************************************************/
void
UpdateStatus(char *msg, MyProgram *data)
{
   data->status.msg = msg;
/*
   printf("%s\n", msg);
*/
   DrawStatus(data);
}


/******************************************************************************
*  HandleNewGame  - handle processing for new game                            *
******************************************************************************/
void
HandleNewGame(MyProgram *me)
{
   InitDatabase(me);
   UpdateDisplay(me);
   UpdateScore(me);

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
      new_file_name = PopupFileRequest("Enter file name to load as (file.sav)\n");

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
      new_file_name = PopupFileRequest("Enter file name to save as (file.sav)\n");

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
 * seed_random() - seed random number generator 
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
int seed_random()
{
   srand((unsigned int)time(NULL));
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



/* end of starfire.c */
