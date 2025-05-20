/*****************************************************************************
 *
 *	MOS test program - tasks
 *
 *	File:	tasks.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/


#include <stdio.h>
#include <string.h>

#include "mos.h"

#include "tasks.h"



ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};


void dummy( void *args )
{
   ARG_STRUCT *my;

   my = args;

   mosPrint("dummy task, args %d %d %d\n", my->arg1, my->arg2, my->arg3);
}


void dummygetid( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   id = mosGetTaskId( "getid" );
   mosPrint("getid task, args %d %d %d, id = %d\n", my->arg1, my->arg2, my->arg3, id);
}


void dummysuspend( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   id = mosGetTaskId( "suspend" );
   mosSuspendTask( id );
   mosPrint("suspend task, args %d %d %d, id = %d\n", my->arg1, my->arg2, my->arg3, id);
}


void dummymemory( void *args )
{
   int error = 0;
   int i, id, size;
   ARG_STRUCT *my;
   char *memptr;

   my = args;

   id = mosGetTaskId( "memory" );
   size = mosGetTaskMemSize( id );
   memptr = mosGetTaskMemPtr( id );

   mosPrint("memory task, id = %d, mem size = %d", id, size);

   if ( *memptr == 0 )
   {
      mosPrint(", memory is empty, filling\n");
      for (i=0; i<size; i++)
      {
         *memptr = 0xAA;
         memptr++;
      }
   }
   else
   {
      mosPrint(", memory is full, clearing\n");
      for (i=0; i<size; i++)
      {
         *memptr = 0x00;
         memptr++;
      }
   }
}


void dummymsg1( void *args )
{
   int i, id1, count, bytes;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];

   my = args;

   id1 = mosGetTaskId( "msg1" );

   mosPrint("msg1 task, id = %d", id1);

   count = mosCheckMessageQueue( id1 );
   if ( count )
   {
      mosPrint(", cnt = %d", count);
      for (i=0; i<count; i++)
      {
         bytes = mosReadMessage( id1, i, &buf[0] );
         mosPrint(", bytes = %d, msg = %s", bytes, &buf[0] );
      }
   }
   mosPrint("\n");
   if (count >= 2)
   { 
      mosClearMessageQueue( id1 );
   }
}


void dummymsg2( void *args )
{
   int id1, id2;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];

   my = args;

   id1 = mosGetTaskId( "msg1" );
   id2 = mosGetTaskId( "msg2" );

   mosPrint("msg2 task, id = %d, dest = %d", id2, id1);

   sprintf( buf, "hi from msg2" );
   if ( mosSendMessage( id1, buf, sizeof(buf) ) )
   {
      mosPrint(", sent = %s\n", buf);
   }
   else 
   {
      mosPrint("msg2 task, send msg failed\n");
   }
}


void dummybroadcast( void *args )
{
   int id;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];

   /* this task broadcast's a message and then suspends itself */

   my = args;

   id = mosGetTaskId( "broadcast" );

   mosPrint("broadcast task, id = %d", id);

   sprintf( buf, "hi from broadcast" );
   if ( mosSendBroadcast( buf, sizeof(buf) ) )
   {
      mosPrint(", sent = %s\n", buf);
   }
   else 
   {
      mosPrint("broadcast task, send broadcast failed\n");
   }

   mosSuspendTask( id );
}


/* end of tasks.c */
