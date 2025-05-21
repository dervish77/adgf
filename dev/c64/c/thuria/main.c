/*****************************************************************************
 *
 *	Main source code for Dungeons of Thuria Game.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *
 *	Usage:
 *		thuria [-h] [-n] [-s file.sav] 
 *
 *              -h            show help
 *              -n            suppress introduction
 *              -s file.save  load saved game
 *
 *	Date:	12/12/96
 *
 *	Revs:
 *	  0.4   04/05/98  added proper save, load, and new game functions
 *	  0.0 	12/12/96  originated
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


#include "peekpoke.h"
#define USE_COLOR 1



/*
 *  GLOBALS
 */
BOOLEAN_T suppress_intro;

extern INTRO_S_T intro[];

extern void PlayGame(GAME_S_T *game);



/* DisplayIntroduction() - show instructions
 *
 *
 */
void DisplayIntroduction(void)
{
   int i = 0;

   printf("\n");

   while( intro[i].linenum > -1 )
   {
      printf("%s\n", intro[i++].introline);
   }

   printf("\n");
}


/* DisplayTitle() - show game titles and credits
 *
 *
 */
void DisplayTitle(void)
{
   printf("\n");
   printf("DUNGEONS of THURIA C64\n");
   printf("Version %s  %s \n", 
	VERSION, VERSIONDATE);
   printf("\n");
   printf("\n");
}

/* LoadGame() - load saved game file
 *
 */
#ifdef SUPPORT_SAVES
void LoadGame(GAME_S_T *game)
{
   SHORT_BUFFER_T string;
   FILE *fp;
   int i, count, a, b, c, d;

   fp = game->load_file_fp;

   fscanf(fp, "%s\n", string);
   if ( strcmp(string, "thuria") == 0 )
   {
      fscanf(fp, "%d\n", &a); game->verbose = a;
      fscanf(fp, "%d\n", &a); game->have_lamp = a;
      fscanf(fp, "%d\n", &a); game->lamp_is_on = a;
      fscanf(fp, "%d\n", &a); game->current_room = a;
      fscanf(fp, "%d\n", &a); game->score = a;
      fscanf(fp, "%d\n", &a); game->health = a;
      fscanf(fp, "%d\n", &a); game->moves = a;
      fscanf(fp, "%d\n", &a); game->oil = a;

      fscanf(fp, "%s %d\n", string, &a); game->inventory.count = a;
      if ( strcmp(string, "inv") == 0 )
      {
         for (i = 0; i < game->inventory.count; i++)
         {
            fscanf(fp, "%d\n", &a); game->inventory.list[i] = a;
         }
      }

      fscanf(fp, "%s %d\n", string, &a); game->chest.count = a;
      if ( strcmp(string, "chest") == 0 )
      {
         for (i = 0; i < game->chest.count; i++)
         {
            fscanf(fp, "%d\n", &a); game->chest.list[i] = a;
         }
      }
   
      fscanf(fp, "%s %d\n", string, &count);
      if ( strcmp(string, "map") == 0 )
      {
         for (i = 0; i < count; i++)
         {
            fscanf(fp, "%d %d %d %d\n", &a, &b, &c, &d);
            map[i].beenhere = b;
            map[i].special = c;
            map[i].object = d;
         }
      }
   }
   else
   {
      printf("Unknown file type detected during load of %s\n",
		game->load_file_name);
   }
}
#endif

/* SaveGame() - save current game to file
 *
 */
#ifdef SUPPORT_SAVES
void SaveGame(GAME_S_T *game)
{
   FILE *fp;
   int i, count;

   fp = game->save_file_fp;

   fprintf(fp, "thuria\n");
   fprintf(fp, "%d\n", game->verbose );
   fprintf(fp, "%d\n", game->have_lamp );
   fprintf(fp, "%d\n", game->lamp_is_on );
   fprintf(fp, "%d\n", game->current_room );
   fprintf(fp, "%d\n", game->score );
   fprintf(fp, "%d\n", game->health );
   fprintf(fp, "%d\n", game->moves );
   fprintf(fp, "%d\n", game->oil );

   fprintf(fp, "inv %d\n", game->inventory.count );
   for (i = 0; i < game->inventory.count; i++)
   {
      fprintf(fp, "%d\n", game->inventory.list[i] );
   }

   fprintf(fp, "chest %d\n", game->chest.count );
   for (i = 0; i < game->chest.count; i++)
   {
      fprintf(fp, "%d\n", game->chest.list[i] );
   }

   count = 0;
   while ( map[count].roomnum > -1 )
   {
      count++;
   }

   fprintf(fp, "map %d\n", count);
   for (i = 0; i < count; i++)
   {
      fprintf(fp, "%d %d %d %d\n", 
	map[i].roomnum, map[i].beenhere, map[i].special, map[i].object );
   }
}
#endif

/* InitGame() - initialize current game 
 *
 */
void InitGame(GAME_S_T *game)
{
   int i;

   game->play_game = TRUE;
#ifdef SUPPORT_EXTRA_CMDS
   game->suppress_instructions = FALSE;
   game->adult_enabled = FALSE;
   game->adult_count = 0;
#endif
   game->debug_enabled = FALSE;
   game->verbose = TRUE;
   game->have_lamp = TRUE;
   game->lamp_is_on = FALSE;

#ifdef SUPPORT_SAVES
   game->load_game = FALSE;
   game->save_game = FALSE;
   game->game_loaded = FALSE;
   game->game_saved = FALSE;
   game->load_file_name[0] = '\0';
   game->save_file_name[0] = '\0';
   game->load_file_fp = (FILE *) NULL;
   game->save_file_fp = (FILE *) NULL;
#endif

   game->current_room = RM_START;

   game->inventory.count = 1;
   game->inventory.list[0] = OBJ_LAMP;
   for (i = 1; i < MAX_INV_OBJS; i++)
   {
      game->inventory.list[i] = OBJ_NULL;
   }

   game->chest.count = 0;
   for (i = 0; i < MAX_CHEST_OBJS; i++)
   {
      game->chest.list[i] = OBJ_NULL;
   }

   game->score = 0;
   game->health = MAX_HEALTH;
   game->moves = 0;
   game->oil = MAX_OIL;
   game->cmdstring[0] = '\0';

   i = 0;
   while ( map[i].roomnum > RM_NULL )
   {
      map[i].beenhere = FALSE;
      i++;
   }

#ifdef SUPPORT_SAVES
   strcpy( game->save_file_name, "init.sav" );
   game->save_file_fp = fopen(game->save_file_name, "w");

   if (game->save_file_fp == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", game->save_file_name);
   }
   else
   {
      SaveGame( game );
      fclose( game->save_file_fp );
   }
#endif
}


/* CloseAll() - close all open files 
 *
 */
void CloseAll(GAME_S_T *game)
{
   game->play_game = FALSE;
}



  
/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
void main(void)
{
   GAME_S_T game;

#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to black */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

   /*  initialize game
    */
   InitGame(&game);

#ifdef SUPPORT_EXTRA_CMDS
   /* options from command line */
   suppress_intro = TRUE;
   game.adult_enabled = TRUE;
   game.debug_enabled = TRUE;
#endif

   /*  prompt for introduction
    */
   if ( !suppress_intro )
   {
      DisplayIntroduction();
   }


   /*  display title block
    */
   DisplayTitle();

#ifdef SUPPORT_SAVES
   /*  start playing the game
    */
   if (game.load_game) 
   {
      LoadGame(&game);
   }
#endif

#if 1
   /*  start playing the game
    */
   PlayGame(&game);
#endif

   /*  close all files
    */
   CloseAll(&game);

   exit(0);
}


/* end of main.c */
