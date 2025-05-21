/*****************************************************************************
 *
 *	Source code for handling debug commands.  Note can be enabled 
 *	player entering password of "hpl".
 *
 *
 *	File:	debug.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.0 	12/04/96  originated
 *
 *	
 *	debug commands:
 *	
 *		debug help
 *		debug status
 *
 *		debug list <room_num>
 *		debug goto <room_num>
 *
 *		debug score <new_score>
 *		debug health <new_health>
 *		debug oil <new_oil>
 *		debug invcnt <new_count>
 *
 *		debug special <room_num> <special>
 *		debug object <room_num> <object>
 *	
 *		debug show map
 *		debug show room
 *		debug show object <obj_num>
 *		debug show special <spec_num>
 *		debug show magic <mg_num>
 *		debug show rank <rk_num>
 *		debug show verb <vb_num>
 *	
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAIN_H
#include "main.h"
#endif






/* HandleDebugCmd() - handle multi-word command
 *
 */
void HandleDebugCmd(GAME_S_T *game)
{
#ifdef SUPPORT_DUNGEON_DEBUG
   INDEX_T index;
   int i;

  if (game->debug_enabled)
  {

   if ( strcmp( game->list[1].cmd, "help" ) == 0 )
   {
      printf("\ndebug help\n");
      printf("debug status\n");
      printf("\n");
      printf("debug list <room_num>\n");
      printf("debug goto <room_num>\n");
      printf("\n");
      printf("debug score <new_score>\n");
      printf("debug health <new_health>\n");
      printf("debug oil <new_oil>\n");
      printf("debug invcnt <new_count>\n");
      printf("\n");
      printf("debug special <room_num> <special>\n");
      printf("debug object <room_num> <object>\n");
      printf("\n");
      printf("debug show map\n");
      printf("debug show room\n");
      printf("debug show object <obj_num>\n");
      printf("debug show special <spec_num>\n");
      printf("debug show magic <mg_num>\n");
      printf("debug show rank <rk_num>\n");
      printf("debug show verb <vb_num>\n");
   }
   else if ( strcmp( game->list[1].cmd, "status" ) == 0 )
   {
      printf("verbose      = %d\n", game->verbose);
      printf("have_lamp    = %d\n", game->have_lamp);
      printf("lamp_is_on   = %d\n", game->lamp_is_on);
      printf("current_room = %d\n", game->current_room);
      printf("score        = %d\n", game->score);
      printf("health       = %d\n", game->health);
      printf("moves        = %d\n", game->moves);
      printf("oil          = %d\n", game->oil);
   }
   else if ( strcmp( game->list[1].cmd, "list" ) == 0 )
   {
      index = atoi( game->list[2].cmd );
      printf("List room #%d\n", index);
      printf("  roomnum   = %d\n", map[index].roomnum);
      printf("  roomname  = %s\n", map[index].roomname);
      printf("  beenhere  = %d\n", map[index].beenhere);
      printf("  inside    = %d\n", map[index].inside);
      printf("  n         = %d\n", map[index].n);
      printf("  s         = %d\n", map[index].s);
      printf("  e         = %d\n", map[index].e);
      printf("  w         = %d\n", map[index].w);
      printf("  d         = %d\n", map[index].d);
      printf("  u         = %d\n", map[index].u);
      printf("  special   = %d\n", map[index].special);
      printf("  object    = %d\n", map[index].object);
   }
   else if ( strcmp( game->list[1].cmd, "special" ) == 0 )
   {
      map[ atoi( game->list[2].cmd ) ].special = atoi( game->list[3].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "object" ) == 0 )
   {
      map[ atoi( game->list[2].cmd ) ].object = atoi( game->list[3].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "score" ) == 0 )
   {
      game->score = atoi( game->list[2].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "health" ) == 0 )
   {
      game->health = atoi( game->list[2].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "oil" ) == 0 )
   {
      game->oil = atoi( game->list[2].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "goto" ) == 0 )
   {
      game->current_room = atoi( game->list[2].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "invcnt" ) == 0 )
   {
      game->inventory.count = atoi( game->list[2].cmd );
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "room" ) == 0 )
   {
      printf("\nCurrent room # is - %d\n", game->current_room);
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "map" ) == 0 )
   {
      i = 0;
      printf("\n");
      while ( map[i].roomnum != RM_NULL )
      {
         printf("Room %2d  %20s \t spec = %2d, obj = %2d\n",
		map[i].roomnum, map[i].roomname, 
		map[i].special, map[i].object);
         i++;
      }
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "object" ) == 0 )
   {
      index = atoi( game->list[3].cmd );
      printf("Object # - %d\n", index );
      printf("  objnum   = %d\n", object[index].objnum);
      printf("  score    = %d\n", object[index].score);
      printf("  key      = %s\n", object[index].key);
      printf("  prep     = %s\n", object[index].prep);
      printf("  name     = %s\n", object[index].name);
      printf("  examine  = %s\n", object[index].examine);
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "special" ) == 0 )
   {
      index = atoi( game->list[3].cmd );
      printf("Special # - %d\n", index );
      printf("  spnum    = %d\n", special[index].spnum);
      printf("  score    = %d\n", special[index].score);
      printf("  phrase   = %s\n", special[index].phrase);
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "magic" ) == 0 )
   {
      index = atoi( game->list[3].cmd );
      printf("Magic # - %d\n", index );
      printf("  mgnum     = %d\n", magic[index].mgnum);
      printf("  score     = %d\n", magic[index].score);
      printf("  fromroom  = %d\n", magic[index].fromroom);
      printf("  toroom    = %d\n", magic[index].toroom);
      printf("  word      = %s\n", magic[index].word);
      printf("  phrase    = %s\n", magic[index].phrase);
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "rank" ) == 0 )
   {
      index = atoi( game->list[3].cmd );
      printf("Rank # - %d\n", index );
      printf("  rnum      = %d\n", rank[index].rnum);
      printf("  title     = %s\n", rank[index].title);
      printf("  phrase    = %s\n", rank[index].phrase);
   }
   else if ( strcmp( game->list[1].cmd, "show" ) == 0 
		&& strcmp( game->list[2].cmd, "verb" ) == 0 )
   {
      index = atoi( game->list[3].cmd );
      printf("Verb # - %d\n", index );
      printf("  vnum      = %d\n", verb[index].vnum);
      printf("  word      = %s\n", verb[index].word);
      printf("  type      = %d\n", verb[index].type);
   }
   else
   {
      printf("\nI don't know how to - debug %s\n", game->list[1].cmd);
   }
  }
  else
  {
   printf("\nSorry, debug is not enabled.\n");
  }
#endif
}


/* HandleDebug() - handle debug command
 *
 */
void HandleDebug(GAME_S_T *game)
{
#ifdef SUPPORT_DUNGEON_DEBUG
   HandleDebugCmd( game );
#else
   printf("\nI don't know how to - %s\n", game->list[0].cmd);
#endif
}


/* end of debug.c */
