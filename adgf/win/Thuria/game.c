/*****************************************************************************
 *
 *	Source code for main game engine routines.
 *
 *	File:	game.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.0 	12/04/96  originated
 *
 *****************************************************************************/


#include <stdio.h>
#include <string.h>

#ifndef MAIN_H
#include "main.h"
#endif




/*
 *  GLOBALS
 */
extern void HandleLetterCmd(GAME_S_T *game);
extern void HandleSingleCmd(GAME_S_T *game);
extern void HandleMultiCmd(GAME_S_T *game);




/*  ParseString	- general purpose string parser
 *
 *  Parameters:
 *	string	- pointer to string to be parsed
 *	args	- pointer to parsed array of strings
 *
 *  Returns:
 *	count	- count of substrings in array
 */
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



/* HaveObject() - test if carrying specified object
 *
 */
BOOLEAN_T HaveObject(GAME_S_T *game, INDEX_T obj, INDEX_T *index)
{
   int i;

   for (i = 0; i < game->inventory.count; i++)
   {
      if (game->inventory.list[i] == obj)
      {
         *index = i;
         return(TRUE);
      }
   }

   return(FALSE);
}


/* DescribeRoom() - show full room description
 *
 */
void DescribeRoom(GAME_S_T *game)
{
   int c, r;
   BOOLEAN_T found;


   found = FALSE;
   c = game->current_room;
   r = 0;

   map[c].beenhere = TRUE;

   while ( room[r].roomnum > RM_NULL )
   {
      if ( room[r].roomnum == c )
      {
         found = TRUE;
         break;
      }
      r++;
   }
   
   if (found) 
   {
      while ( (room[r].roomnum == c) && (room[r].linenum > -1) )
      {
         printf("  %s\n", room[r].roomline);
         r++;
      }
   }
   else
   {
      printf("Error - room description not found!\n");
      exit(0);
   }
}


/* DescribeObject() - show object description
 *
 */
void DescribeObject(GAME_S_T *game)
{
   INDEX_T	obj;
   int 		i;

   if (game->current_room == RM_MAIN_CHAMBER)
   {
      if (game->chest.count == 0)
      {
         printf("  %s\n", special[SE_CHEST_EMPTY].phrase);
      }
      else
      {
         printf("  %s\n", special[SE_CHEST_FULL].phrase);
         for (i = 0; i < game->chest.count; i++)
         {
            printf("    %s\n", object[game->chest.list[i]].name);
         }
      }
   }
   else
   {
      obj = map[game->current_room].object;

      if (obj > OBJ_NULL)
      {
         printf("  There %s %s here!\n", 
		object[obj].prep, object[obj].name); 
      }
   }
}


/* DescribeSpecial() - show special effect description
 *
 */
void DescribeSpecial(GAME_S_T *game)
{
   INDEX_T	sp;

   sp = map[game->current_room].special;

   if (sp > SE_NULL)
   {
      printf("  %s\n", special[sp].phrase); 
   }
}


/* ShowScore() - show score and rank description
 *
 */
void ShowScore(GAME_S_T *game)
{
   int rk;

   printf("\nYour score is %d out of %d in %d moves.\n", 
		game->score, MAX_SCORE, game->moves);

   if ( game->score >= MIN_SCORE && game->score < RANK_0_MAX )
      rk = RK_RANK0;
   else if ( game->score >= RANK_0_MAX && game->score < RANK_1_MAX )
      rk = RK_RANK1;
   else if ( game->score >= RANK_1_MAX && game->score < RANK_2_MAX )
      rk = RK_RANK2;
   else if ( game->score >= RANK_2_MAX && game->score < RANK_3_MAX )
      rk = RK_RANK3;
   else if ( game->score >= RANK_3_MAX && game->score < RANK_4_MAX )
      rk = RK_RANK4;
   else
      rk = RK_RANK5;

   printf("\nYour rank is %s.  %s\n", rank[rk].title, rank[rk].phrase);
}


/* PlayerDied() - handle player's death
 *
 */
void PlayerDied(GAME_S_T *game)
{
   SHORT_BUFFER_T	response;

   printf("\nYou have died a horrible death.\n");
   ShowScore(game);
   printf("\nHit any key to quit... ");
   gets( response );
   exit(0);
}


/* CheckLamp() - handle lamp state, returns TRUE if lamp is on
 *
 */
BOOLEAN_T CheckLamp(GAME_S_T *game)
{
   if (game->lamp_is_on)
   {
      if (game->oil < LOW_OIL)
      {
         printf("\nYour lamp is low on oil.\n");
      }
      else if (game->oil < 1)
      {
         game->lamp_is_on = FALSE;
         printf("\nYour lamp has run out of oil.\n");
         printf("It is dark.  If you proceed, it is likely that you\n");
         printf("will take a nasty fall and hurt yourself.\n");
      }
   }
   else
   {
      if (map[game->current_room].inside)
      {
         if ( game->health <= 0)
         {
            PlayerDied( game );
         }
         else
         {
            printf("\nIt is dark.  If you proceed, it is likely that you\n");
            printf("will take a nasty fall and hurt yourself.\n");
            game->health -= DAMAGE_FALL;
         }
         return(FALSE);
      }
   }

   return(TRUE);
}


/* ReadCommand() - read user command string
 *
 */
BOOLEAN_T ReadCommand(GAME_S_T *game)
{
   LONG_BUFFER_T	cmd;

   printf("\n%s", PROMPT);
   fgets( cmd, LONG_BUFF_LEN, stdin );
   strncpy( game->cmdstring, cmd, LONG_BUFF_LEN );

   return(FALSE);
}


/* ParseCommand() - read user command string
 *
 */
BOOLEAN_T ParseCommand(GAME_S_T *game)
{
   char 	*buffer;
   char		*cmdargs[MAX_CMD_ARGS];
   int		i, argcount;

   buffer = &game->cmdstring[0];
   game->cmdstring[LONG_BUFF_LEN - 1] = '\0';

   argcount = ParseString( buffer, cmdargs );
   game->argcount = argcount;

   for (i = 0; i < game->argcount; i++)
   {
      game->list[i].type = 0;
      game->list[i].length = strlen( cmdargs[i] );
      strcpy( game->list[i].cmd, cmdargs[i] );
   }

   return(FALSE);
}


/* GetCommand() - get user command string, and handle it
 *
 */
BOOLEAN_T GetCommand(GAME_S_T *game)
{
   SHORT_BUFFER_T	response;


   /*  read and parse command from player
    */
   ReadCommand( game );
   ParseCommand( game );


   /*  for single word commands 
    */
   if (game->argcount == 1)
   {
      if ( strcmp( game->list[0].cmd, "quit" ) == 0 
		|| strcmp( game->list[0].cmd, "q" ) == 0 )
      {
         ShowScore(game);
         printf("\nQuitting, are you sure? ");
         gets( response );
         if ( response[0] == 'y' || response[0] == 'Y' )
            return(TRUE);
      }
      else if ( strcmp( game->list[0].cmd, "x" ) == 0 )
      {
         return(TRUE);
      }
      else
      {
         if ( strlen( game->list[0].cmd ) == 1 )
            HandleLetterCmd( game );
         else
            HandleSingleCmd( game );
      }
   }
   else /* else, multi-word commands */
   {
      HandleMultiCmd( game );
   }

   return(FALSE);
}


/* PlayGame() - play the game, i.e. main game loop
 *
 */
void PlayGame(GAME_S_T *game)
{
   BOOLEAN_T	quit = FALSE; 
   INDEX_T	current;

   current = game->current_room;

   while ( !quit )
   {
      printf("%s\n", map[current].roomname);

      if ( game->verbose && (map[current].beenhere == FALSE) )
      {
         DescribeRoom(game);
         DescribeSpecial(game);
      }

      DescribeObject(game);

      while ( !quit && (current == game->current_room) )
      {
         quit = GetCommand( game );
         game->moves++;
         if (game->lamp_is_on) 
            game->oil--;
         if (game->health < MAX_HEALTH)
            game->health++;
      }

      current = game->current_room;
   }
}


/* end of game.c */
