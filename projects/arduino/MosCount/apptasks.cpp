/*****************************************************************************
 *
 *	MOS app test program - tasks
 *
 *	File:	apptasks.cpp
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
#include <stdlib.h>
#include <string.h>

#include "mos.h"

#include "apptasks.h"


static int count = 0;


ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};

// task that increments counter and send message to print task
void counttask( void *args )
{
   int id, bytes, error;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];
   
   mosTraceToggle(12, 100);
   
   my = (ARG_STRUCT *) args;

   // get id of receiver task
   id = mosGetTaskId( "printtask" );
   
   // increment counter
   count++;
   
   // create count message
   sprintf(buf, "%d", count);
   
   // send count message to print task
   bytes = mosSendMessage( id, buf, sizeof(buf) );
   
   if (bytes == 0)
   {
      mosTraceToggle(13, 100);
      //mosPrint("Error - count msg failed!");
   }
}

// task that prints count message to debug console
void printtask( void *args )
{
   int i, myid, msgcount, bytes, datacount;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];
      
   //mosTraceToggle(13, 100);
      
   my = (ARG_STRUCT *) args;

   myid = mosGetTaskId( "printtask" );

   // check our message queue for messages from count task
   msgcount = mosCheckMessageQueue( myid );

   if (msgcount)
   {
      mosTraceToggle(13, 100);
      
      // process each message   
      for (i = 0; i < msgcount; i++)
      {
         // read a count data message
         bytes = mosReadMessage( myid, i, &buf[0] );
         
         // output count data to debug console
         datacount = atoi( buf );
         mosPrint("%d\n", datacount);
         
         // delay a bit
         mosSleep(500);
      }
   }
   
   mosSleep(300);
}

/* end of apptasks.cpp */
