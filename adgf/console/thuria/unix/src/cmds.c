/*****************************************************************************
 *
 *	Source code for handling commands.
 *
 *	File:	cmds.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.4	04/05/98  added proper new game function
 *	  0.0 	12/04/96  originated
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
extern void LoadGame(GAME_S_T *game);
extern void SaveGame(GAME_S_T *game);
extern void InitGame(GAME_S_T *game);
extern void DescribeRoom(GAME_S_T *game);
extern void DescribeSpecial(GAME_S_T *game);
extern void DescribeObject(GAME_S_T *game);
extern void PlayerDied(GAME_S_T *game);
extern BOOLEAN_T CheckLamp(GAME_S_T *game);
extern void DisplayTitle(void);
extern BOOLEAN_T HaveObject(GAME_S_T *game, INDEX_T obj, INDEX_T *index);
extern void HandleDebug(GAME_S_T *game);
extern void ShowScore(GAME_S_T *game);



/* HandleHelp() - show help text
 *
 */
void HandleHelp()
{
   printf("\nHelpful commands:\n");

   printf("  quit                  - quit game\n");
   printf("  help                  - show command help\n");
   printf("  inv                   - list inventory\n");
   printf("  look                  - repeat room description\n");
   printf("  brief                 - toggle to brief mode\n");
   printf("  verbose               - toggle to verbose mode\n");
   printf("  load                  - load saved game\n");
   printf("  save                  - save current game\n");
   printf("  diagnose              - show health status\n");
   printf("  n,s,e,w,u,d           - travel directions\n");

   printf("\nOther verbs:\n");

   printf("  take, drop, enter, exit, open, read, examine, on, off\n");

   printf("\n");
}


/* HandleInventory() - show inventory
 *
 */
void HandleInventory(GAME_S_T *game)
{
   int i;

   printf("\nYou are carrying");

   if (game->inventory.count == 0)
   {
      printf(" nothing.\n");
   }
   else
   {
      printf(":\n");
      for (i = 0; i < game->inventory.count; i++)
      {
         printf("   %s\n", object[game->inventory.list[i]].name);
      }
   }
}


/* HandleLoad() - handle load game
 *
 */
void HandleLoad(GAME_S_T *game)
{
   strcpy( game->load_file_name, "thuria.sav" );
   game->load_file_fp = fopen(game->load_file_name, "r");

   if (game->load_file_fp == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", game->load_file_name);
   }
   else
   {
      printf("\nLoading saved game ... ");
      LoadGame( game );
      printf("done.\n");
      fclose( game->load_file_fp );
   }
}


/* HandleSave() - handle save game
 *
 */
void HandleSave(GAME_S_T *game)
{
   strcpy( game->save_file_name, "thuria.sav" );
   game->save_file_fp = fopen(game->save_file_name, "w");

   if (game->save_file_fp == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", game->save_file_name);
   }
   else
   {
      printf("\nSaving current game ... ");
      SaveGame( game );
      printf("done.\n");
      fclose( game->save_file_fp );
   }
}


/* HandleNew() - handle new game
 *
 */
void HandleNew(GAME_S_T *game)
{
   SHORT_BUFFER_T result;

   printf("\nStarting new game.  Are you sure (y/n)? ");

   if (fgets( result, SHORT_BUFF_LEN, stdin ) == NULL)
   {
      fprintf(stderr,"fgets error");
      exit(1);
   }

   if ( result[0] == 'y' || result[0] == 'Y' )
   {
      printf("\nOkay...\n\n");
      strcpy( game->load_file_name, "init.sav" );
      game->load_file_fp = fopen(game->load_file_name, "r");

      if (game->load_file_fp == (FILE *)NULL)
      {
         fprintf(stderr, "Couldn't open %s as input\n", game->load_file_name);
      }
      else
      {
         LoadGame( game );
         fclose( game->load_file_fp );
      }
   }
}


/* HandleMagic() - handle magic words
 *
 */
BOOLEAN_T HandleMagic(GAME_S_T *game)
{
   BOOLEAN_T found = FALSE;
   int i = 0, mg = 0;
   INDEX_T cr;

   cr = game->current_room;

   i = 0;
   while ( magic[i].mgnum > MG_NULL )
   {
      if ( strcmp( magic[i].word, game->list[0].cmd ) == 0 )
      {
         mg = i;
         found = TRUE;
         break;
      }
      i++;
   }

   if (found)
   {
      if ( mg == MG_XYZZY )
      {
         printf("\n%s\n", magic[mg].phrase);
         game->score += magic[mg].score;
      }
      else if ( cr == magic[mg].fromroom )
      {
         printf("\n%s\n", magic[mg].phrase);
         game->score += magic[mg].score;
         game->current_room = magic[mg].toroom;
      }
      else if ( cr == magic[mg].toroom )
      {
         printf("\n%s\n", magic[mg].phrase);
         game->score += magic[mg].score;
         game->current_room = magic[mg].fromroom;
      }
      else
      {
         printf("\nApparently, you are in the wrong room.\n");
      }
   }

   if ( cr != game->current_room ) printf("\n");

   return(found);
}


/* HandleLook() - handle look command
 *
 */
void HandleLook(GAME_S_T *game)
{
   printf("%s\n", map[game->current_room].roomname);
   DescribeRoom(game);
   DescribeSpecial(game);
   DescribeObject(game);
}


/* HandleOn() - handle (lamp) on command
 *
 */
void HandleOn(GAME_S_T *game)
{
   if (game->have_lamp && !game->lamp_is_on )
   {
      if (game->oil > 0)
      {
         game->lamp_is_on = TRUE;
         printf("\nThe lamp is now on.\n");
      }
      else
      {
         printf("\nYour lamp has no more oil.\n");
      }
   }
   else if (game->have_lamp && game->lamp_is_on)
   {
      printf("\nThe lamp is already on.\n");
   }
   else
   {
      printf("\nYou don't have the lamp!\n");
   }
}


/* HandleOff() - handle (lamp) off command
 *
 */
void HandleOff(GAME_S_T *game)
{
   if (game->have_lamp && game->lamp_is_on)
   {
      game->lamp_is_on = FALSE;
      printf("\nThe lamp is now off.\n");
   }
   else if (game->have_lamp && !game->lamp_is_on)
   {
      printf("\nThe lamp is already off.\n");
   }
   else
   {
      printf("\nYou don't have the lamp!\n");
   }
}


/* HandleEnter() - handle enter command
 *
 */
void HandleEnter(GAME_S_T *game)
{
   INDEX_T cr;

   cr = game->current_room;

   switch( cr )
   {
      case RM_OUTSIDE_MAIN:
         switch(map[cr].special)
         {
            case SE_ODOOR_LOCKED:
               printf("\nThe door is padlocked.\n");
               break;
            case SE_ODOOR_CLOSED:
               printf("\nThe door is shut tight.\n");
               break;
            case SE_ODOOR_OPEN:
               game->current_room = RM_MAIN_CHAMBER;
               break;
         }
         break;

      default:
         printf("\nI don't see an entrance!\n");
   }
}


/* HandleExit() - handle exit command
 *
 */
void HandleExit(GAME_S_T *game)
{
   INDEX_T cr;

   cr = game->current_room;

   switch( cr )
   {
      case RM_MAIN_CHAMBER:
         switch(map[cr].special)
         {
            case SE_IDOOR_CLOSED:
               printf("\nThe door is shut tight.\n");
               break;
            case SE_IDOOR_OPEN:
               game->current_room = RM_OUTSIDE_MAIN;
               break;
         }
         break;

      default:
         printf("\nI don't see an entrance!\n");
   }
}


/* HandleSwim() - handle swim command
 *
 */
void HandleSwim(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   switch(cr)
   {
      case RM_BEAVER_DAM:
         printf("\nThe current exiting the dam is gentle enough for swimming but you\n");
         printf("find that bottom very rocky with pockets of mud which try to suck\n");
         printf("you down.  You scramble back to the bank and rest awhile.\n");
         break;

      case RM_SWIFT_RIVER:
         if (map[cr].special == SE_SWIFT_WARN1)
         {
            printf("\nYou approach the river, but think better of it after reading\n");
            printf("the warning sign again.\n");
            map[cr].special = SE_SWIFT_WARN2;
         }
         else if (map[cr].special == SE_SWIFT_WARN2)
         {
            printf("\nIgnoring the warning sign, you jump into the swiftly flowing\n");
            printf("current and are swept away downstream.  Where a hundred foot\n");
            printf("waterfall carries you to your death on the rocks below.\n");
            PlayerDied( game );
         }
         break;

      case RM_BEAVER_POND:
         printf("\nYou swim out into the pond several feet from shore and realize\n");
         printf("that it is well over your head.  You just make it back to safety\n");
         printf("after swallowing a few mouthfuls of water.\n");
         break;

      case RM_MISTY_VALLEY:
         printf("\nThe tiny stream is far too small for swimming.\n");
         break;

      case RM_BROOK:
         printf("\nYou wade into the babbling brook and discover that though it is\n");
         printf("indeed refreshing, it also pointless.\n");
         break;

      default:
         printf("\nThere is no water visible.\n");
         break;
   }
}


/* HandleJump() - handle jump command
 *
 */
void HandleJump(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   switch(cr)
   {
      case RM_SWIFT_RIVER:
         printf("\nThe river is far too wide to safely jump across.\n");
         break;

      case RM_MISTY_VALLEY:
         printf("\nWhy jump across the stream when walking is much simpler.\n");
         break;

      case RM_BROOK:
         printf("\nYou gleefully jump across the babbling brook and back several times,\n");
         printf("but nothing extraordinary happens.\n");
         break;

      case RM_NARROW_CAVE:
         switch(map[RM_LARGE_CAVE].special)
         {
            case SE_BRIDGE_NO:
               printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
               break;
            case SE_BRIDGE_NO2:
               printf("\nForegoing all common sense, you plunge headlong into the\ngaping and bottomless fissure.\n");
               PlayerDied(game);
               break;
            case SE_BRIDGE_YES:
               printf("\nYou carefully cross the delicate crystal bridge.  But just as you\n make it to the other side, the bridge shatters behind you.\n\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_BRK;
               game->current_room = RM_LARGE_CAVE;
               break;
            case SE_BRIDGE_BRK:
               printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
               break;
            }
         break;

      case RM_LARGE_CAVE:
         switch(map[cr].special)
         {
            case SE_BRIDGE_NO:
               printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
               break;
            case SE_BRIDGE_NO2:
               printf("\nForegoing all common sense, you plunge headlong into the\ngaping and bottomless fissure.\n");
               PlayerDied(game);
               break;
            case SE_BRIDGE_YES:
               printf("\nYou carefully cross the delicate crystal bridge.  But just as you\n make it to the other side, the bridge shatters behind you.\n\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_BRK;
               game->current_room = RM_NARROW_CAVE;
               break;
            case SE_BRIDGE_BRK:
               printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
               map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
               break;
            }
         break;

      default:
         printf("\nThere is nothing here to jump.\n");
         break;
   }
}


/* HandleSpecialDirection() - handle special direction traveled
 *
 *  {note return TRUE if handled by this function}
 */
BOOLEAN_T HandleSpecialDirection(GAME_S_T *game, char dir)
{
   INDEX_T	cr;
   BOOLEAN_T	retval = FALSE;


   cr = game->current_room;

   switch( cr )
   {
      case RM_OUTSIDE_MAIN:
         if (dir == 'n')
         {
            switch(map[cr].special)
            {
               case SE_ODOOR_LOCKED:
                  printf("\nThe door is padlocked.\n");
                  break;
               case SE_ODOOR_CLOSED:
                  printf("\nThe door is shut tight.\n");
                  break;
               case SE_ODOOR_OPEN:
                  game->current_room = RM_MAIN_CHAMBER;
                  break;
            }
            retval = TRUE;
         }
         break;

      case RM_MAIN_CHAMBER:
         if (dir == 's')
         {
            switch(map[cr].special)
            {
               case SE_IDOOR_CLOSED:
                  printf("\nThe door is shut tight.\n");
                  break;
               case SE_IDOOR_OPEN:
                  game->current_room = RM_OUTSIDE_MAIN;
                  break;
            }
            retval = TRUE;
         }
         break;

      case RM_THRONE:
         switch(map[cr].special)
         {
            case SE_SKEL_SITS:
               printf("\nThe decaying skeleton rises to prevent your escape and then attacks.\n");
               map[cr].special = SE_SKEL_ATTACK;
               retval = TRUE;
               break;
            case SE_SKEL_ATTACK:
               printf("\nThe attacking skeleton prevents your escape.\n");
               printf("\nThe skeleton stabs at you and hits!\n");
               game->health -= DAMAGE_SKEL;
               retval = TRUE;
               break;
         }
         break;

      case RM_STATUE:
         if ( (dir == 'n' && map[cr].special == SE_STATUE_NORTH)
		|| (dir == 's' && map[cr].special == SE_STATUE_SOUTH) )
         {
            printf("\nAs you reach the doorway, the indian statue releases an arrow \nwhich passes straight through your heart.\n");
            PlayerDied( game );
         }
         break;

      case RM_DIMLY_LIT:
         if ( dir == 'e' )
         {
            if ( game->inventory.count > 1 )
            {
               printf("\nYou cannot fit through the narrow slit with everything that you\nare carrying.  You must drop something first.\n");
            }
            else
            {
               printf("\nYou just barely squeezed through the narrow slit.\n\n");
               game->current_room = RM_GREEN;
            }
            retval = TRUE;
         }
         break;

      case RM_GREEN:
         if ( dir == 'w' )
         {
            if ( game->inventory.count > 1 )
            {
               printf("\nYou cannot fit through the narrow slit with everything that you\nare carrying.  You must drop something first.\n");
            }
            else
            {
               printf("\nYou just barely squeezed through the narrow slit.\n\n");
               game->current_room = RM_DIMLY_LIT;
            }
            retval = TRUE;
         }
         break;

      case RM_CREVICE:
         if ( dir == 'd' )
         {
            switch(map[cr].special)
            {
               case SE_GRATE_LOCKED:
                  printf("\nThe grate is locked.\n");
                  break;
               case SE_GRATE_CLOSED:
                  printf("\nThe grate is closed.\n");
                  break;
               case SE_GRATE_OPEN:
                  game->current_room = RM_LIBRARY;
                  break;
            }
            retval = TRUE;
         }
         break;

      case RM_NARROW_CAVE:
         if ( dir == 'e' )
         {
            switch(map[cr].special)
            {
               case SE_SLAB_CLOSED:
                  printf("\nThe stone slab blocks any possible eastern exit.\n");
                  break;
               case SE_SLAB_OPEN:
                  printf("\nYou manage to struggle through the tight opening.\n\n");
                  game->current_room = RM_ANSWER;
                  break;
            }
            retval = TRUE;
         }
         if ( dir == 's' )
         {
            switch(map[RM_LARGE_CAVE].special)
            {
               case SE_BRIDGE_NO:
                  printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
                  break;
               case SE_BRIDGE_NO2:
                  printf("\nForegoing all common sense, you plunge headlong into the\ngaping and bottomless fissure.\n");
                  PlayerDied(game);
                  break;
               case SE_BRIDGE_YES:
                  printf("\nYou carefully cross the delicate crystal bridge.  But just as you\n make it to the other side, the bridge shatters behind you.\n\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_BRK;
                  game->current_room = RM_LARGE_CAVE;
                  break;
               case SE_BRIDGE_BRK:
                  printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
                  break;
            }
            retval = TRUE;
         }
         break;

      case RM_ANSWER:
         if ( dir == 'w' )
         {
            printf("\nYou find that way back is confusing.  You eventually find a passage out.\n\n");
            game->current_room = RM_LARGE_CAVE;
            retval = TRUE;
         }
         break;

      case RM_LARGE_CAVE:
         if ( dir == 'n' )
         {
            switch(map[cr].special)
            {
               case SE_BRIDGE_NO:
                  printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
                  break;
               case SE_BRIDGE_NO2:
                  printf("\nForegoing all common sense, you plunge headlong into the\ngaping and bottomless fissure.\n");
                  PlayerDied(game);
                  break;
               case SE_BRIDGE_YES:
                  printf("\nYou carefully cross the delicate crystal bridge.  But just as you\nmake it to the other side, the bridge shatters behind you.\n\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_BRK;
                  game->current_room = RM_NARROW_CAVE;
                  break;
               case SE_BRIDGE_BRK:
                  printf("\nIt would be suicide to attempt such a foolhardy endeavor.\n");
                  map[RM_LARGE_CAVE].special = SE_BRIDGE_NO2;
                  break;
            }
            retval = TRUE;
         }
         break;

      case RM_STRANGE:
         if ( dir == 'u' )
         {
            if ( map[RM_STRANGE].special == SE_ROPE_RISEN )
            {
               printf("\nSurprising yourself with your agility, you easily climb up\nthe strong rope.\n\n");
               game->current_room = RM_EGG_ROOM;
            }
            else
            {
               printf("\nThere is no way to climb up to the small hole.\n");
            }
            retval = TRUE;
         }
         break;

      case RM_NORTH_SIDE_LAKE:
         if ( dir == 's' )
         {
            if ( map[RM_NORTH_SIDE_LAKE].special == SE_BOOTS_ON )
            {
               printf("\nAmazingly you are indeed able to walk on water, and you quickly\ncross to the other side.\n\n");
               game->current_room = RM_SOUTH_SIDE_LAKE;
            }
            else
            {
               printf("\nThe lake is far too deep for wading.\n");
            }
            retval = TRUE;
         }
         break;

      case RM_SOUTH_SIDE_LAKE:
         if ( dir == 'n' )
         {
            if ( map[RM_SOUTH_SIDE_LAKE].special == SE_BOOTS_ON )
            {
               printf("\nAmazingly you are indeed able to walk on water, and you quickly\ncross to the other side.\n\n");
               game->current_room = RM_NORTH_SIDE_LAKE;
            }
            else
            {
               printf("\nThe lake is far too deep for wading.\n");
            }
            retval = TRUE;
         }
         break;

      case RM_QUESTION:
         if ( dir == 'n' )
         {
            switch(map[cr].special)
            {
               case SE_ANSWER_0:
                  printf("\nThe strange hooded little man rises and blocks your path.\n");
                  break;
               case SE_ANSWER_1:
                  printf("\nThe strange man rises and threatens you with his blade.\n");
                  break;
               case SE_ANSWER_2:
                  printf("\nApparently fed up with your insolence, the strange man rises\nand then cuts you cleanly in half with his scythe.\n");
                  PlayerDied(game);
                  break;
               case SE_ANSWER_3:
                  printf("\nThe strange man ignores you as you pass through the doorway.\n\n");
                  game->current_room = RM_PYRAMID;
                  break;
            }
            retval = TRUE;
         }
   }

   return(retval);
}


/* HandleDirection() - handle direction traveled
 *
 */
void HandleDirection(GAME_S_T *game, char dir)
{
   INDEX_T	room;


   if ( HandleSpecialDirection(game, dir) )
      return;

   room = game->current_room;

   switch( dir )
   {
      case 'n':
         if ( map[room].n > RM_NULL )
         {
            game->current_room = map[room].n;
         }
         else
         {
            printf("\nThere is no way to go north!\n");
         }
         break;

      case 's':
         if ( map[room].s > RM_NULL )
         {
            game->current_room = map[room].s;
         }
         else
         {
            printf("\nThere is no way to go south!\n");
         }
         break;

      case 'e':
         if ( map[room].e > RM_NULL )
         {
            game->current_room = map[room].e;
         }
         else
         {
            printf("\nThere is no way to go east!\n");
         }
         break;

      case 'w':
         if ( map[room].w > RM_NULL )
         {
            game->current_room = map[room].w;
         }
         else
         {
            printf("\nThere is no way to go west!\n");
         }
         break;

      case 'u':
         if ( map[room].u > RM_NULL )
         {
            game->current_room = map[room].u;
         }
         else
         {
            printf("\nThere is no way to go up!\n");
         }
         break;

      case 'd':
         if ( map[room].d > RM_NULL )
         {
            game->current_room = map[room].d;
         }
         else
         {
            printf("\nThere is no way to go down!\n");
         }
         break;

      default:
         printf("\nUnknown direction.\n");
         break;
   }
}


/* HandleLetterCmd() - handle single letter command
 *
 */
void HandleLetterCmd(GAME_S_T *game)
{
   switch( game->list[0].cmd[0] )
   {
      case 'n':
      case 's':
      case 'e':
      case 'w':
      case 'u':
      case 'd':
         if ( CheckLamp(game) )
            HandleDirection(game, game->list[0].cmd[0]);
         break;
      case 'l':
         HandleLook(game);
         break;
      case 'i':
         HandleInventory(game);
         break;
      case 'b':
         game->verbose = FALSE;
         printf("\nBrief mode\n");
         break;
      case 'v':
         game->verbose = TRUE;
         printf("\nVerbose mode\n");
         break;
      case 'h':
         HandleHelp();
         break;
      default:
         printf("\nI don't know how to - %s\n", game->list[0].cmd);
         break;
   }
}


/* HandleSingleCmd() - handle single word command
 *
 */
void HandleSingleCmd(GAME_S_T *game)
{
   if ( strcmp( game->list[0].cmd, "help" ) == 0 )
   {
      HandleHelp();
   }
   else if ( strcmp( game->list[0].cmd, "look" ) == 0 )
   {
      HandleLook(game);
   }
   else if ( strcmp( game->list[0].cmd, "north" ) == 0
		|| strcmp( game->list[0].cmd, "south" ) == 0
		|| strcmp( game->list[0].cmd, "east" ) == 0
		|| strcmp( game->list[0].cmd, "west" ) == 0
		|| strcmp( game->list[0].cmd, "up" ) == 0
		|| strcmp( game->list[0].cmd, "down" ) == 0 )
   {
      if ( CheckLamp(game) )
         HandleDirection(game, game->list[0].cmd[0]);
   }
   else if ( strcmp( game->list[0].cmd, "inv" ) == 0 )
   {
      HandleInventory(game);
   }
   else if ( strcmp( game->list[0].cmd, "load" ) == 0 )
   {
      HandleLoad(game);
   }
   else if ( strcmp( game->list[0].cmd, "save" ) == 0 )
   {
      HandleSave(game);
   }
   else if ( strcmp( game->list[0].cmd, "new" ) == 0 )
   {
      HandleNew(game);
   }
   else if ( strcmp( game->list[0].cmd, "on" ) == 0 )
   {
      HandleOn(game);
   }
   else if ( strcmp( game->list[0].cmd, "off" ) == 0 )
   {
      HandleOff(game);
   }
   else if ( strcmp( game->list[0].cmd, "enter" ) == 0 )
   {
      HandleEnter(game);
   }
   else if ( strcmp( game->list[0].cmd, "exit" ) == 0 )
   {
      HandleExit(game);
   }
   else if ( strcmp( game->list[0].cmd, "swim" ) == 0 )
   {
      HandleSwim(game);
   }
   else if ( strcmp( game->list[0].cmd, "jump" ) == 0 )
   {
      HandleJump(game);
   }
   else if ( strcmp( game->list[0].cmd, "brief" ) == 0 )
   {
      game->verbose = FALSE;
      printf("\nBrief mode\n");
   }
   else if ( strcmp( game->list[0].cmd, "verbose" ) == 0 )
   {
      game->verbose = TRUE;
      printf("\nVerbose mode.\n");
   }
   else if ( strcmp( game->list[0].cmd, "wait" ) == 0 )
   {
      game->moves++;
      printf("\nTime passes.\n");
   }
   else if ( strcmp( game->list[0].cmd, "score" ) == 0 )
   {
      ShowScore(game);
   }
   else if ( strcmp( game->list[0].cmd, "health" ) == 0
		|| strcmp( game->list[0].cmd, "diagnose" ) == 0 )
   {
      printf("\nYour health is %d out of %d.\n",
		game->health, MAX_HEALTH);
   }
   else if ( strcmp( game->list[0].cmd, "about" ) == 0 )
   {
      DisplayTitle();
   }
   else if ( strcmp( game->list[0].cmd, "hpl" ) == 0 )
   {
      game->debug_enabled = TRUE;
      printf("\nOkay.\n");
   }
   else if ( strcmp( game->list[0].cmd, "whoami" ) == 0 )
   {
      printf("\nYou are a poor slub who got can't even get to work on time.\n");
   }
   else if ( strcmp( game->list[0].cmd, "amiga" ) == 0 )
   {
      printf("\nLong live the Amiga!!!!\n");
   }
   else if ( strcmp( game->list[0].cmd, "thuria" ) == 0 )
   {
      printf("\nThuria is a mystical land where dreams oft come true.  But in your \ncase think of it as a pain in the butt.\n");
   }
   else if ( strcmp( game->list[0].cmd, "teh" ) == 0 )
   {
      printf("\nType much?\n");
   }
   else if ( strcmp( game->list[0].cmd, "take" ) == 0
		|| strcmp( game->list[0].cmd, "drop" ) == 0
		|| strcmp( game->list[0].cmd, "wave" ) == 0
		|| strcmp( game->list[0].cmd, "open" ) == 0
		|| strcmp( game->list[0].cmd, "close" ) == 0
		|| strcmp( game->list[0].cmd, "play" ) == 0
		|| strcmp( game->list[0].cmd, "pick" ) == 0
		|| strcmp( game->list[0].cmd, "feed" ) == 0
		|| strcmp( game->list[0].cmd, "drink" ) == 0
		|| strcmp( game->list[0].cmd, "eat" ) == 0
		|| strcmp( game->list[0].cmd, "kill" ) == 0
		|| strcmp( game->list[0].cmd, "wear" ) == 0
		|| strcmp( game->list[0].cmd, "read" ) == 0
		|| strcmp( game->list[0].cmd, "move" ) == 0
		|| strcmp( game->list[0].cmd, "answer" ) == 0
		|| strcmp( game->list[0].cmd, "break" ) == 0
		|| strcmp( game->list[0].cmd, "unlock" ) == 0
		|| strcmp( game->list[0].cmd, "examine" ) == 0 )
   {
      printf("\nWhat do you wish to %s?\n", game->list[0].cmd);
   }
   else if ( strcmp( game->list[0].cmd, "ls" ) == 0
		|| strcmp( game->list[0].cmd, "dir" ) == 0
		|| strcmp( game->list[0].cmd, "reboot" ) == 0
		|| strcmp( game->list[0].cmd, "ps" ) == 0 )
   {
      printf("\nThis is not a computer, so cut out the geek lingo!\n");
   }
   else if ( strcmp( game->list[0].cmd, "jesus" ) == 0
		|| strcmp( game->list[0].cmd, "damn" ) == 0
		|| strcmp( game->list[0].cmd, "hell" ) == 0
		|| strcmp( game->list[0].cmd, "fuck" ) == 0 )
   {
      if (game->adult_enabled)
         printf("\nCursing will not help your situation.\n");
      else
      {
         game->adult_count++;
         if ( (game->adult_count % ATRG) == 0 )
         {
            printf("\nBoy, you really are obsessed!\n");
         }
         else
         {
            printf("\nI don't know how to - %s\n", game->list[0].cmd);
         }
      }
   }
   else if ( strcmp( game->list[0].cmd, "shit" ) == 0
		|| strcmp( game->list[0].cmd, "piss" ) == 0
		|| strcmp( game->list[0].cmd, "puke" ) == 0 )
   {
      if (game->adult_enabled)
         printf("\nDon't %s in my dungeon!\n", game->list[0].cmd);
      else
      {
         game->adult_count++;
         if ( (game->adult_count % ATRG) == 0 )
         {
            printf("\nBoy, you really are obsessed!\n");
         }
         else
         {
            printf("\nI don't know how to - %s\n", game->list[0].cmd);
         }
      }
   }
   else if ( strcmp( game->list[0].cmd, "xxx" ) == 0
		|| strcmp( game->list[0].cmd, "sex" ) == 0 )
   {
      game->adult_count++;
      if ( (game->adult_count % ATRG) == 0 )
      {
         printf("\nBoy, you really are obsessed!\n");
      }
      else
      {
         printf("\nI don't know how to - %s\n", game->list[0].cmd);
      }
   }
   else if ( strcmp( game->list[0].cmd, "cock" ) == 0
		|| strcmp( game->list[0].cmd, "cunt" ) == 0
		|| strcmp( game->list[0].cmd, "pussy" ) == 0
		|| strcmp( game->list[0].cmd, "dick" ) == 0
		|| strcmp( game->list[0].cmd, "penis" ) == 0
		|| strcmp( game->list[0].cmd, "vagina" ) == 0
		|| strcmp( game->list[0].cmd, "tit" ) == 0 )
   {
      if (game->adult_enabled)
         printf("\nYou want me to touch your %s?\n", game->list[0].cmd);
      else
      {
         game->adult_count++;
         if ( (game->adult_count % ATRG) == 0 )
         {
            printf("\nBoy, you really are obsessed!\n");
         }
         else
         {
            printf("\nI don't know how to - %s\n", game->list[0].cmd);
         }
      }
   }
   else
   {
      if ( ! HandleMagic( game ) )
      {
         printf("\nI don't know how to - %s\n", game->list[0].cmd);
      }
   }
}


/* HandleTake() - handle take object command
 *
 */
void HandleTake(GAME_S_T *game)
{
   BOOLEAN_T	found = FALSE;
   INDEX_T	obj;
   INDEX_T	invcount;
   int		i;

   if (game->current_room == RM_MAIN_CHAMBER)
   {
      for (i = 0; i < game->chest.count; i++)
      {
         obj = game->chest.list[i];
         if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
         {
            found = TRUE;
            break;
         }
      }

      if (found)
      {
         /* remove item from chest */
         game->chest.list[i] = game->chest.list[game->chest.count - 1];
         game->chest.count--;
         /* add item to inventory */
         game->inventory.list[game->inventory.count] = obj;
         game->inventory.count++;
         /* lower score for this item */
         game->score -= object[obj].score;
         printf("\nTaken from treasure chest.\n");
      }
      else
      {
         printf("\nThe treasure chest doesn't have - %s.\n", game->list[1].cmd);
      }
   }
   else
   {
      obj = map[game->current_room].object;
      invcount = game->inventory.count;

      if (obj > OBJ_NULL)
      {
         if ( strcmp( object[obj].key, game->list[1].cmd ) == 0)
         {
            if ( (invcount + 1) < MAX_INV_OBJS )
            {
               if ( obj == OBJ_RUG
			&& map[game->current_room].special == SE_BEAR_HUNGRY)
               {
                  printf("\nThe sleeping bear prevents you from taking the rug.\n");
               }
               else if ( obj == OBJ_RUG
			&& map[game->current_room].special == SE_BEAR_DEAD)
               {
                  printf("\nThe dead bear prevents you from taking the rug.\n");
               }
               else if ( obj == OBJ_OIL )
               {
                  printf("\nYour lamp is now glowing brighter than ever.\n");
                  game->oil += CAN_OIL;
                  map[game->current_room].object = -1;
                  game->score += object[obj].score;
                  printf("\nTaken.\n");
               }
               else
               {
                  /* add item to inventory */
                  game->inventory.list[invcount] = obj;
                  game->inventory.count = invcount + 1;
                  /* remove item from room */
                  map[game->current_room].object = -1;
                  /* bump score for this item */
                  game->score += object[obj].score;
                  printf("\nTaken.\n");
               }
            }
            else
            {
               printf("\nYou are carrying too many things.\n");
            }
         }
         else
         {
            printf("\nI don't see any %s here!\n", game->list[1].cmd);
         }
      }
      else
      {
         printf("\nThere is nothing here to take!\n");
      }
   }
}


/* HandleDrop() - handle drop object command
 *
 */
void HandleDrop(GAME_S_T *game)
{
   BOOLEAN_T	found = FALSE;
   INDEX_T	obj;
   int		i, count;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if (found)
   {
      switch(game->current_room)
      {
         case RM_MAIN_CHAMBER:	/* drop into treasure chest */
            if (game->chest.count < MAX_CHEST_OBJS)
            {
               /* add item to chest */
               game->chest.list[game->chest.count] = obj;
               game->chest.count++;
               /* remove item from inventory */
               count = game->inventory.count;
               game->inventory.list[i] = game->inventory.list[count - 1];
               game->inventory.count = count - 1;
               /* bump score for this item */
               game->score += object[obj].score;
               printf("\nDropped into treasure chest.\n");
            }
            else
            {
               printf("\nSorry, the treasure chest is full.\n");
            }
            break;

         case RM_STATUE:	/* drop into statue */
            if (obj == OBJ_COINS)
            {
               if (map[game->current_room].special == SE_STATUE_NORTH)
               {
                  printf("(into coin sized slot)\n");
                  printf("\nSlowly the statue of the indian turns to face the southern doorway.\n");
                  map[game->current_room].special = SE_STATUE_SOUTH;
                  game->score += special[SE_STATUE_SOUTH].score;
                  /* remove item from inventory */
                  count = game->inventory.count;
                  game->inventory.list[i] = game->inventory.list[count - 1];
                  game->inventory.count = count - 1;
               }
            }
            else
            {
               printf("\nYou can't fit the %s into the slot!\n", object[obj].name);
            }
            break;

         default:		/* drop into empty room */
            if (map[game->current_room].object > -1)
            {
               printf("\nYou cannot drop that here.  Find an empty room.\n");
            }
            else
            {
               /* place object in room */
               map[game->current_room].object = obj;
               /* remove item from inventory */
               count = game->inventory.count;
               game->inventory.list[i] = game->inventory.list[count - 1];
               game->inventory.count = count - 1;
               printf("\nDropped.\n");
            }
            break;
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleOpen() - handle open object command
 *
 */
void HandleOpen(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   switch(cr)
   {
      case RM_OUTSIDE_MAIN:
         if ( strcmp( game->list[1].cmd, "door" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_ODOOR_LOCKED:
                  printf("\nThe door is padlocked.\n");
                  break;
               case SE_ODOOR_CLOSED:
                  printf("\nThe door swings open with a creaking sound.\n");
                  map[cr].special = SE_ODOOR_OPEN;
                  map[RM_MAIN_CHAMBER].special = SE_IDOOR_OPEN;
                  break;
               case SE_ODOOR_OPEN:
                  printf("\nThe door is already open.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_MAIN_CHAMBER:
         if ( strcmp( game->list[1].cmd, "door" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_IDOOR_CLOSED:
                  printf("\nThe door swings open with a creaking sound.\n");
                  map[cr].special = SE_IDOOR_OPEN;
                  map[RM_OUTSIDE_MAIN].special = SE_ODOOR_OPEN;
                  break;
               case SE_IDOOR_OPEN:
                  printf("\nThe door is already open.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_CREVICE:
         if ( strcmp( game->list[1].cmd, "grate" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_GRATE_LOCKED:
                  printf("\nThe grate is locked.\n");
                  break;
               case SE_GRATE_CLOSED:
                  printf("\nThe grate swings open with a creaking sound.\n");
                  map[cr].special = SE_GRATE_OPEN;
                  break;
               case SE_GRATE_OPEN:
                  printf("\nThe grate is already open.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to open!\n");
         break;
   }
}


/* HandleClose() - handle close object command
 *
 */
void HandleClose(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   switch(cr)
   {
      case RM_OUTSIDE_MAIN:
         if ( strcmp( game->list[1].cmd, "door" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_ODOOR_OPEN:
                  printf("\nThe door swings closed with a creaking sound.\n");
                  map[cr].special = SE_ODOOR_CLOSED;
                  map[RM_MAIN_CHAMBER].special = SE_IDOOR_CLOSED;
                  break;
               case SE_ODOOR_CLOSED:
                  printf("\nThe door is already closed.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_MAIN_CHAMBER:
         if ( strcmp( game->list[1].cmd, "door" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_IDOOR_OPEN:
                  printf("\nThe door swings closed with a creaking sound.\n");
                  map[cr].special = SE_IDOOR_CLOSED;
                  map[RM_OUTSIDE_MAIN].special = SE_ODOOR_CLOSED;
                  break;
               case SE_IDOOR_CLOSED:
                  printf("\nThe door is already closed.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_CREVICE:
         if ( strcmp( game->list[1].cmd, "grate" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_GRATE_OPEN:
                  printf("\nThe grate swings closed with a creaking sound.\n");
                  map[cr].special = SE_GRATE_CLOSED;
                  break;
               case SE_GRATE_CLOSED:
                  printf("\nThe grate is already closed.\n");
                  break;
            }
         }
         else
         {
            printf("\nYou can't open a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to close!\n");
         break;
   }
}


/* HandleWave() - handle wave object command
 *
 */
void HandleWave(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      if ( obj == OBJ_ROD )
      {
         if ( cr == RM_LARGE_CAVE
		&& map[RM_LARGE_CAVE].special == SE_BRIDGE_NO )
         {
            printf("\nAs you wave the strange black rod over your head, a crystal bridge\ngrows from one side of the fissure to other.\n");
            map[RM_LARGE_CAVE].special = SE_BRIDGE_YES;
            game->score += special[SE_BRIDGE_YES].score;
         }
         else if ( cr == RM_LARGE_CAVE
		&& map[RM_LARGE_CAVE].special == SE_BRIDGE_BRK )
         {
            printf("\nAs you wave the strange black rod over your head, a crystal bridge\ngrows from one side of the fissure to other.\n");
            map[RM_LARGE_CAVE].special = SE_BRIDGE_YES;
         }
         else if ( cr == RM_NARROW_CAVE
		&& map[RM_LARGE_CAVE].special == SE_BRIDGE_NO )
         {
            printf("\nAs you wave the strange black rod over your head, a crystal bridge\ngrows from one side of the fissure to other.\n");
            map[RM_LARGE_CAVE].special = SE_BRIDGE_YES;
         }
         else if ( cr == RM_NARROW_CAVE
		&& map[RM_LARGE_CAVE].special == SE_BRIDGE_BRK )
         {
            printf("\nAs you wave the strange black rod over your head, a crystal bridge\ngrows from one side of the fissure to other.\n");
            map[RM_LARGE_CAVE].special = SE_BRIDGE_YES;
         }
         else
         {
            printf("\nWaving the rod has no effect.\n");
         }
      }
      else
      {
         printf("\nYou can't wave that!\n");
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandlePlay() - handle play object command
 *
 */
void HandlePlay(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      if ( obj == OBJ_FLUTE )
      {
         if ( cr == RM_STRANGE
		&& map[RM_STRANGE].special == SE_ROPE_COILED )
         {
            printf("\nAs you play, the rope climbs slowly out of the basket and eventually\nreaches all the way up to the small opening.\n");
            game->score += special[SE_ROPE_RISEN].score;
            map[RM_STRANGE].special = SE_ROPE_RISEN;
         }
         else if ( cr == RM_STRANGE
		&& map[RM_STRANGE].special == SE_ROPE_RISEN )
         {
            printf("\nAs you play, the rope slowly coils itself back inside of the basket.\n");
            map[RM_STRANGE].special = SE_ROPE_COILED;
         }
         else
         {
            printf("\nPlaying the flute has no effect.\n");
         }
      }
      else
      {
         printf("\nYou can't play that!\n");
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleDrink() - handle drink object command
 *
 */
void HandleDrink(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      switch(cr)
      {
         default:
            printf("\nDrinking the %s has no effect.\n", game->list[1].cmd);
            break;
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleEat() - handle eat object command
 *
 */
void HandleEat(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i, count;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      switch(obj)
      {
         case OBJ_TWINKIES:
            printf("\nYou gobble down the twinkies only to realize that they are quite stale.\n");
            /* remove item from inventory */
            count = game->inventory.count;
            game->inventory.list[i] = game->inventory.list[count - 1];
            game->inventory.count = count - 1;
            break;

         default:
            printf("\nEating the %s has no effect.\n", game->list[1].cmd);
            break;
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleAnswer() - handle answer command
 *
 */
void HandleAnswer(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   if ( cr == RM_QUESTION )
   {
      switch(map[cr].special)
      {
         case SE_ANSWER_0:	/* accept player's name */
            map[cr].special = SE_ANSWER_1;
            printf("\n%s\n", special[map[cr].special].phrase);
            break;
         case SE_ANSWER_1:	/* accept "home" */
            if ( strcmp( game->list[1].cmd, "home" ) == 0 )
            {
               map[cr].special = SE_ANSWER_2;
               printf("\n%s\n", special[map[cr].special].phrase);
            }
            else
            {
               map[cr].special = SE_ANSWER_0;
               printf("\n%s\n", special[map[cr].special].phrase);
            }
            break;
         case SE_ANSWER_2:	/* accept "marcus" */
            if ( strcmp( game->list[1].cmd, "marcus" ) == 0 )
            {
               map[cr].special = SE_ANSWER_3;
               game->score += special[SE_ANSWER_3].score;
               printf("\n%s\n", special[map[cr].special].phrase);
            }
            else
            {
               map[cr].special = SE_ANSWER_0;
               printf("\n%s\n", special[map[cr].special].phrase);
            }
            break;
         case SE_ANSWER_3:
            printf("\n%s\n", special[map[cr].special].phrase);
            break;
      }
   }
   else
   {
      printf("\nWho are you talking to?\n");
   }
}


/* HandleBreak() - handle break object command
 *
 */
void HandleBreak(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i, count;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      switch(obj)
      {
         case OBJ_EGG:
            printf("\nThe golden is fragile and breaks quite easily, revealing a %s.\n", object[OBJ_KEY].name);
            map[cr].object = OBJ_KEY;
            /* remove item from inventory */
            count = game->inventory.count;
            game->inventory.list[i] = game->inventory.list[count - 1];
            game->inventory.count = count - 1;
            break;

         default:
            printf("\nBreaking the %s has no effect.\n", game->list[1].cmd);
            break;
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleKill() - handle kill object command
 *
 */
void HandleKill(GAME_S_T *game)
{
   INDEX_T	cr, index;

   cr = game->current_room;

   if ( HaveObject(game, OBJ_SWORD, &index) )
   {
      printf("(with %s)\n", object[OBJ_SWORD].name);
      switch(cr)
      {
         case RM_THRONE:
            if ( strcmp( object[OBJ_SKELETON].key, game->list[1].cmd ) == 0 )
            {
               printf("\nYou stab at where the skeleton's heart used to be and it \ncrumples to the floor.\n");
               game->score += special[SE_SKEL_DEAD].score;
               map[cr].special = SE_SKEL_DEAD;
            }
            else
            {
               printf("\nYou can't kill that.\n");
            }
            break;

         case RM_BEAVER_POND:
            if ( strcmp( object[OBJ_BEAVER].key, game->list[1].cmd ) == 0 )
            {
               printf("\nYou cut the poor defenseless beaver cleanly in half.\n");
               map[cr].special = SE_BEAV_DEAD;
            }
            else
            {
               printf("\nYou can't kill that.\n");
            }
            break;

         case RM_RUG_ROOM:
            if ( strcmp( object[OBJ_BEAR].key, game->list[1].cmd ) == 0 )
            {
               printf("\nYou attack the sleeping bear, killing it after several blows.\n");
               map[cr].special = SE_BEAR_DEAD;
            }
            else
            {
               printf("\nYou can't kill that.\n");
            }
            break;

         case RM_QUESTION:
            if ( strcmp( object[OBJ_MAN].key, game->list[1].cmd ) == 0)
            {
               printf("\nYou try to attack the strange man, but he is surprisingly quick \nand cuts you cleanly in half with his scythe.\n");
               PlayerDied(game);
            }
            else
            {
               printf("\nYou can't kill that.\n");
            }
            break;

         default:
            printf("\nThere is nothing to kill here.\n");
            break;
      }
   }
   else
   {
      printf("\nYou are not carrying a weapon.\n");
   }
}


/* HandleWear() - handle wear object command
 *
 */
void HandleWear(GAME_S_T *game)
{
   BOOLEAN_T    found = FALSE;
   INDEX_T	obj;
   INDEX_T	cr;
   int		i;

   cr = game->current_room;

   for (i = 0; i < game->inventory.count; i++)
   {
      obj = game->inventory.list[i];
      if ( strcmp(object[obj].key, game->list[1].cmd) == 0 )
      {
         found = TRUE;
         break;
      }
   }

   if ( found )
   {
      if ( obj == OBJ_BOOTS )
      {
         if ( cr == RM_NORTH_SIDE_LAKE
		&& map[RM_NORTH_SIDE_LAKE].special == SE_BOOTS_OFF )
         {
            printf("\nAs you finish lacing up the rotting boots, you suddenly feel like\nyou could walk on water.\n");
            map[RM_NORTH_SIDE_LAKE].special = SE_BOOTS_ON;
            map[RM_SOUTH_SIDE_LAKE].special = SE_BOOTS_ON;
            game->score += special[SE_BOOTS_ON].score;
         }
         else if ( cr == RM_SOUTH_SIDE_LAKE
		&& map[RM_SOUTH_SIDE_LAKE].special == SE_BOOTS_OFF )
         {
            printf("\nAs you finish lacing up the rotting boots, you suddenly feel like\nyou could walk on water.\n");
            map[RM_NORTH_SIDE_LAKE].special = SE_BOOTS_ON;
            map[RM_SOUTH_SIDE_LAKE].special = SE_BOOTS_ON;
         }
         else
         {
            printf("\nWearing the boots has no effect.\n");
         }
      }
      else
      {
         printf("\nYou can't wear that!\n");
      }
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleMove() - handle move object command
 *
 */
void HandleMove(GAME_S_T *game)
{
   INDEX_T	cr;

   cr = game->current_room;

   switch(cr)
   {
      case RM_NARROW_CAVE:
         if ( strcmp( game->list[1].cmd, "slab" ) == 0 )
         {
            switch(map[cr].special)
            {
               case SE_SLAB_CLOSED:
                  printf("\nAfter some major effort, you manage to move the slab a few inches.\n");
                  map[cr].special = SE_SLAB_OPEN;
                  game->score += special[SE_SLAB_OPEN].score;
                  break;
               case SE_SLAB_OPEN:
                  printf("\nAfter some major effort, you manage to move the slab back.\n");
                  map[cr].special = SE_SLAB_CLOSED;
                  break;
            }
         }
         else
         {
            printf("\nYou can't move a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to move.\n");
         break;
   }
}


/* HandlePick() - handle pick object command
 *
 */
void HandlePick(GAME_S_T *game)
{
   INDEX_T	cr, index;

   cr = game->current_room;

   switch(cr)
   {
      case RM_OUTSIDE_MAIN:
         if ( strcmp( game->list[1].cmd, "lock" ) == 0
		|| strcmp( game->list[1].cmd, "padlock" ) == 0 )
         {
            if ( HaveObject(game, OBJ_NAIL, &index) )
            {
               printf("(with %s)\n", object[game->inventory.list[index]].name);
               switch(map[cr].special)
               {
                  case SE_ODOOR_LOCKED:
                     printf("\nAfter some effort, the padlock clicks open.\n");
                     map[cr].special = SE_ODOOR_CLOSED;
                     game->score += special[SE_ODOOR_CLOSED].score;
                     break;
                  case SE_ODOOR_CLOSED:
                  case SE_ODOOR_OPEN:
                     printf("\nThe padlock is already unlocked.\n");
                     break;
               }
            }
            else
            {
               printf("\nYou aren't carrying anything to pick with.\n");
            }
         }
         else
         {
            printf("\nYou can't pick a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_CREVICE:
         if ( strcmp( game->list[1].cmd, "lock" ) == 0
		|| strcmp( game->list[1].cmd, "grate" ) == 0 )
         {
            if ( HaveObject(game, OBJ_NAIL, &index) )
            {
               printf("(with %s)\n", object[game->inventory.list[index]].name);
               switch(map[cr].special)
               {
                  case SE_GRATE_LOCKED:
                     printf("\nAfter some effort, the lock clicks open.\n");
                     map[cr].special = SE_GRATE_CLOSED;
                     game->score += special[SE_GRATE_CLOSED].score;
                     break;
                  case SE_GRATE_CLOSED:
                  case SE_GRATE_OPEN:
                     printf("\nThe grate is already unlocked.\n");
                     break;
               }
            }
            else
            {
               printf("\nYou aren't carrying anything to pick with.\n");
            }
         }
         else
         {
            printf("\nYou can't pick a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to pick!\n");
         break;
   }
}


/* HandleUnlock() - handle unlock object command
 *
 */
void HandleUnlock(GAME_S_T *game)
{
   INDEX_T	cr, index;

   cr = game->current_room;

   switch(cr)
   {
      case RM_CREVICE:
         if ( strcmp( game->list[1].cmd, "lock" ) == 0
		|| strcmp( game->list[1].cmd, "grate" ) == 0 )
         {
            if ( HaveObject(game, OBJ_KEY, &index) )
            {
               printf("(with %s)\n", object[game->inventory.list[index]].name);
               switch(map[cr].special)
               {
                  case SE_GRATE_LOCKED:
                     printf("\nAfter some effort, the lock clicks open.\n");
                     map[cr].special = SE_GRATE_CLOSED;
                     game->score += special[SE_GRATE_CLOSED].score;
                     break;
                  case SE_GRATE_CLOSED:
                  case SE_GRATE_OPEN:
                     printf("\nThe grate is already unlocked.\n");
                     break;
               }
            }
            else
            {
               printf("\nYou aren't carrying a key.\n");
            }
         }
         else
         {
            printf("\nYou can't unlock a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to unlock!\n");
         break;
   }
}


/* HandleFeed() - handle feed object command
 *
 */
void HandleFeed(GAME_S_T *game)
{
   INDEX_T	cr;
   INDEX_T	index;
   int 		count;

   cr = game->current_room;

   switch(cr)
   {
      case RM_BEAVER_POND:
         if ( strcmp( game->list[1].cmd, "beaver" ) == 0 )
         {
            if ( HaveObject(game, OBJ_TWINKIES, &index) )
            {
               printf("(the %s)\n", object[OBJ_TWINKIES].name);
               switch(map[cr].special)
               {
                  case SE_BEAV_HUNGRY:
                     printf("\nThe beaver waddles up, sniffs the twinkies, and then bites your leg.\n");
                     map[cr].special = SE_BEAV_BITES;
                     game->health -= DAMAGE_BEAVER;
                     break;
                  case SE_BEAV_BITES:
                     printf("\nThe beaver has ignored your offering, and bites you again.\n");
                     game->health -= DAMAGE_BEAVER;
                     break;
                  case SE_BEAV_DEAD:
                     printf("\nWhy you would try to feed a dead beaver is beyond me.\n");
                     break;
               }
            }
            else
            {
               printf("\nYou aren't carrying any food item.\n");
            }
         }
         else
         {
            printf("\nYou can't feed a %s.\n", game->list[1].cmd);
         }
         break;

      case RM_RUG_ROOM:
         if ( strcmp( game->list[1].cmd, "bear" ) == 0 )
         {
            if ( HaveObject(game, OBJ_TWINKIES, &index) )
            {
               printf("(the %s)\n", object[OBJ_TWINKIES].name);
               switch(map[cr].special)
               {
                  case SE_BEAR_HUNGRY:
                     printf("\nThe bear wakes up, eagerly gobbles down your twinkies, then wanders away.\n");
                     map[cr].special = SE_BEAR_GONE;
                     game->score += special[SE_BEAR_GONE].score;
                     /* remove item from inventory */
                     count = game->inventory.count;
                     game->inventory.list[index] = game->inventory.list[count - 1];
                     game->inventory.count = count - 1;
                     break;
                  case SE_BEAR_GONE:
                     printf("\nThe bear is long gone, having fed on your twinkies.\n");
                     break;
                  case SE_BEAR_DEAD:
                     printf("\nFeeding twinkies to a dead bear is just plain twisted.\n");
                     break;
               }
            }
            else
            {
               printf("\nYou aren't carrying any food item.\n");
            }
         }
         else
         {
            printf("\nYou can't feed a %s.\n", game->list[1].cmd);
         }
         break;

      default:
         printf("\nThere is nothing here to feed!\n");
         break;
   }
}


/* HandleRead() - handle read (examine) object command
 *
 */
void HandleRead(GAME_S_T *game)
{
   INDEX_T	obj;
   INDEX_T	exm;
   INDEX_T	invcount;
   INDEX_T	cr;
   int		i;

   invcount = game->inventory.count;
   cr = game->current_room;
   exm = EX_NULL;

   switch(cr)
   {
      case RM_MAIN_CHAMBER:
         if ( strcmp( game->list[1].cmd, "chest" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_CHEST].examine);
            return;
         }
         break;

      case RM_THRONE:
         if ( strcmp( game->list[1].cmd, "skeleton" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_SKELETON].examine);
            return;
         }
         break;

      case RM_BEAVER_POND:
         if ( strcmp( game->list[1].cmd, "beaver" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_BEAVER].examine);
            return;
         }
         break;

      case RM_OUTSIDE_MAIN:
         if ( strcmp( game->list[1].cmd, "padlock" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_PADLOCK].examine);
            return;
         }
         else if ( strcmp( game->list[1].cmd, "door" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_DOOR].examine);
            return;
         }
         break;

      case RM_STATUE:
         if ( strcmp( game->list[1].cmd, "statue" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_STATUE].examine);
            return;
         }
         break;

      case RM_PILLOW:
         if ( strcmp( game->list[1].cmd, "pillows" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_PILLOWS].examine);
            return;
         }
         break;

      case RM_CREVICE:
         if ( strcmp( game->list[1].cmd, "grate" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_GRATE].examine);
            return;
         }
         break;

      case RM_RUG_ROOM:
         if ( strcmp( game->list[1].cmd, "rug" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_RUG].examine);
            return;
         }
         else if ( strcmp( game->list[1].cmd, "bear" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_BEAR].examine);
            return;
         }
         break;

      case RM_NARROW_CAVE:
         if ( strcmp( game->list[1].cmd, "slab" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_SLAB].examine);
            return;
         }
         break;

      case RM_LIBRARY:
         if ( strcmp( game->list[1].cmd, "book" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_BOOK].examine);
            return;
         }
         break;

      case RM_LARGE_CAVE:
         if ( strcmp( game->list[1].cmd, "fissure" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_FISSURE].examine);
            return;
         }
         break;

      case RM_STRANGE:
         if ( strcmp( game->list[1].cmd, "rope" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_ROPE].examine);
            return;
         }
         else if ( strcmp( game->list[1].cmd, "basket" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_BASKET].examine);
            return;
         }
         break;

      case RM_NORTH_SIDE_LAKE:
      case RM_SOUTH_SIDE_LAKE:
         if ( strcmp( game->list[1].cmd, "lake" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_LAKE].examine);
            return;
         }
         break;

      case RM_QUESTION:
         if ( strcmp( game->list[1].cmd, "man" ) == 0 )
         {
            printf("\n%s\n", object[OBJ_MAN].examine);
            return;
         }
         break;
   }

   for (i = 0; i < invcount; i++)
   {
      obj = game->inventory.list[i];

      if ( strcmp( object[obj].key, game->list[1].cmd ) == 0 )
      {
         exm = obj;
         break;
      }
   }

   if (i < invcount)
   {
      printf("\n%s\n", object[exm].examine);
   }
   else
   {
      printf("\nYou are not carrying - %s\n", game->list[1].cmd);
   }
}


/* HandleMultiCmd() - handle multi-word command
 *
 */
void HandleMultiCmd(GAME_S_T *game)
{
   if ( strcmp( game->list[0].cmd, "take" ) == 0 )
   {
      HandleTake(game);
   }
   else if ( strcmp( game->list[0].cmd, "drop" ) == 0 )
   {
      HandleDrop(game);
   }
   else if ( strcmp( game->list[0].cmd, "wave" ) == 0 )
   {
      HandleWave(game);
   }
   else if ( strcmp( game->list[0].cmd, "open" ) == 0 )
   {
      HandleOpen(game);
   }
   else if ( strcmp( game->list[0].cmd, "close" ) == 0 )
   {
      HandleClose(game);
   }
   else if ( strcmp( game->list[0].cmd, "play" ) == 0 )
   {
      HandlePlay(game);
   }
   else if ( strcmp( game->list[0].cmd, "pick" ) == 0 )
   {
      HandlePick(game);
   }
   else if ( strcmp( game->list[0].cmd, "feed" ) == 0 )
   {
      HandleFeed(game);
   }
   else if ( strcmp( game->list[0].cmd, "drink" ) == 0 )
   {
      HandleDrink(game);
   }
   else if ( strcmp( game->list[0].cmd, "eat" ) == 0 )
   {
      HandleEat(game);
   }
   else if ( strcmp( game->list[0].cmd, "kill" ) == 0 )
   {
      HandleKill(game);
   }
   else if ( strcmp( game->list[0].cmd, "wear" ) == 0 )
   {
      HandleWear(game);
   }
   else if ( strcmp( game->list[0].cmd, "move" ) == 0 )
   {
      HandleMove(game);
   }
   else if ( strcmp( game->list[0].cmd, "answer" ) == 0 )
   {
      HandleAnswer(game);
   }
   else if ( strcmp( game->list[0].cmd, "break" ) == 0 )
   {
      HandleBreak(game);
   }
   else if ( strcmp( game->list[0].cmd, "unlock" ) == 0 )
   {
      HandleUnlock(game);
   }
#ifdef DUNGEON_DEBUG
   else if ( strcmp( game->list[0].cmd, "debug" ) == 0 )
   {
      HandleDebug(game);
   }
#endif
   else if ( strcmp( game->list[0].cmd, "read" ) == 0
		|| strcmp( game->list[0].cmd, "examine" ) == 0
		|| strcmp( game->list[0].cmd, "x" ) == 0 )
   {
      HandleRead(game);
   }
   else if ( (strcmp( game->list[0].cmd, "bill" ) == 0
			&& strcmp( game->list[1].cmd, "gates" ) == 0) )
   {
      printf("\nLogic error 666 -- please reboot system.\n");
   }
   else if ( (strcmp( game->list[0].cmd, "adult" ) == 0
			&& strcmp( game->list[1].cmd, "enabled" ) == 0) )
   {
      printf("\nOkay.\n");
      game->adult_enabled = TRUE;
   }
   else if ( (strcmp( game->list[0].cmd, "fuck" ) == 0)
		|| (strcmp( game->list[0].cmd, "bite" ) == 0
			&& strcmp( game->list[1].cmd, "me" ) == 0) )
   {
      if (game->adult_enabled)
         printf("\nAnd %s %s to you too!\n", game->list[0].cmd, game->list[1].cmd);
      else
      {
         game->adult_count++;
         if ( (game->adult_count % ATRG) == 0 )
         {
            printf("\nBoy, you really are obsessed!\n");
         }
         else
         {
            printf("\nI don't know how to - %s\n", game->list[0].cmd);
         }
      }
   }
   else if ( strcmp( game->list[0].cmd, "jesus" ) == 0
			&& strcmp( game->list[1].cmd, "christ" ) == 0 )
   {
      if (game->adult_enabled)
         printf("\nCursing will not help your situation.\n");
      else
      {
         game->adult_count++;
         if ( (game->adult_count % ATRG) == 0 )
         {
            printf("\nBoy, you really are obsessed!\n");
         }
         else
         {
            printf("\nI don't know how to - %s\n", game->list[0].cmd);
         }
      }
   }
   else
   {
      printf("\nI don't know how to - %s %s\n",
		game->list[0].cmd, game->list[1].cmd);
   }
}


/* end of cmds.c */
