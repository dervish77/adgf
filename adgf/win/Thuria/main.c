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

#ifndef MAIN_H
#include "main.h"
#endif




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
   printf("DUNGEONS of THURIA\n");
   printf("Copyright 1998, by Brian S. Lingard.  All rights reserved.\n");
   printf("Version %s  %s  Whirling Dervish Software.\n", 
	VERSION, VERSIONDATE);
   printf("\n");
   printf("\n");
}


/* LoadGame() - load saved game file
 *
 */
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


/* SaveGame() - save current game to file
 *
 */
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


/* InitGame() - initialize current game 
 *
 */
void InitGame(GAME_S_T *game)
{
   int i;

   game->play_game = TRUE;
   game->suppress_instructions = FALSE;
   game->adult_enabled = FALSE;
   game->adult_count = 0;
   game->debug_enabled = FALSE;
   game->verbose = TRUE;
   game->have_lamp = TRUE;
   game->lamp_is_on = FALSE;

   game->load_game = FALSE;
   game->save_game = FALSE;
   game->game_loaded = FALSE;
   game->game_saved = FALSE;
   game->load_file_name[0] = '\0';
   game->save_file_name[0] = '\0';
   game->load_file_fp = (FILE *) NULL;
   game->save_file_fp = (FILE *) NULL;

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
}


/* CloseAll() - close all open files 
 *
 */
void CloseAll(GAME_S_T *game)
{

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
int 
main(int argc, char **argv)
{
   GAME_S_T game;
   int i;


   /*  initialize game
    */
   InitGame(&game);


   /*  parse cli arguments
    */
   switch (argc)
   {
      case 1:
         break;

      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'h':
                     fprintf(stderr, 
			"Usage:  %s [-h] [-n] [-s file.sav]\n", 
			argv[0]);
                     fprintf(stderr,"   -h            show help\n");
                     fprintf(stderr,"   -n            suppress introduction\n");
                     fprintf(stderr,"   -s file.sav   load saved game\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'n':
                     suppress_intro = TRUE;
                     break;

                  case 'a':
                     game.adult_enabled = TRUE;
                     break;

                  case 'd':
                     game.debug_enabled = TRUE;
                     break;

                  case 's':
                     strcpy(game.load_file_name, argv[i+1]);
                     game.load_file_fp = fopen(game.load_file_name, "r");
                     if (game.load_file_fp == (FILE *)NULL)
                     {
                        fprintf(stderr, 
				"Couldn't open %s as input\n", 
				game.load_file_name);
                        exit(1);
                     }
                     i++;
                     game.load_game = TRUE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-n] [-s file.sav]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
      default:
         fprintf(stderr, 
		"Usage:  %s [-h] [-n] [-s file.sav]\n", argv[0]);
         exit(1);
   } /* end of outer switch */



   /*  prompt for introduction
    */
   if ( !suppress_intro )
   {
      DisplayIntroduction();
   }


   /*  display title block
    */
   DisplayTitle();


   /*  start playing the game
    */
   if (game.load_game) 
   {
      LoadGame(&game);
   }


   /*  start playing the game
    */
   PlayGame(&game);


   /*  close all files
    */
   CloseAll(&game);

   exit(0);
}


/* end of main.c */
