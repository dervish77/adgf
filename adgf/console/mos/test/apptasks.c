/*****************************************************************************
 *
 *	MOS app test program - tasks
 *
 *	File:	apptasks.c
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


int terminalIsOpen = 0;


ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};


void getid( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   // pretend to do some work
   id = mosGetTaskId( "getid" );
}


void cmdtask( void *args )
{
   int done = 0;
   int i, myid, count, bytes;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];

   my = args;

   myid = mosGetTaskId( "cmdtask" );

   // check our message queue for messages from kbd task
   count = mosCheckMessageQueue( myid );

   // if we have messages, then process them
   if ( count )
   {
      // process each message   
      for (i=0; i<count; i++)
      {
         // read a command message, then parse it
         bytes = mosReadMessage( myid, i, &buf[0] );

         if ( strcmp(buf, "exit") == 0 )
         {
             mosPrint(" - goodbye!");
             done = 1;
         }
         else if ( strcmp(buf, "quit") == 0 )
         {
             mosPrint(" - can't quit, must 'exit'");
         }
         else if ( strcmp(buf, "hi") == 0 )
         {
             mosPrint(" - hi yourself!");
         }
         else if ( strcmp(buf, "start") == 0 )
         {
             mosPrint(" - starting!");
         }
         else if ( strcmp(buf, "stop") == 0 )
         {
             mosPrint(" - stopping!");
         }
         else if ( strcmp(buf, "reset") == 0 )
         {
             mosPrint(" - resetting!");
         }
         else if ( strcmp(buf, "kill") == 0 )
         {
             mosPrint(" - killing 02 ...\n");
             mosDeleteTask( 2 );
         }
         else if ( strcmp(buf, "list") == 0 )
         {
             mosPrint(" - listing...\n");
             mosDisplayTaskList();
         }
         else if ( strcmp(buf, "help") == 0 )
         {
             mosPrint(" - help is not available");
         }
         else
         {
             mosPrint(" - unknown command entered");
         }
      }

      // clear the message queue since we're done here
      mosClearMessageQueue( myid );
   }
   mosPrint("\n");

   // quit the app if we got "exit" command
   if (done) 
   {
       if ( terminalIsOpen ) mosCloseTerminal();
       exit(0);
   }
}


void kbdtask( void *args )
{
   int bytes, error;
   int cmd, kbd;
   ARG_STRUCT *my;
   char buf[MAX_MSG_SIZE - 1];

   my = args;

   cmd = mosGetTaskId( "cmdtask" );
   kbd = mosGetTaskId( "kbdtask" );

   // read commands from terminal if it's open
   if ( terminalIsOpen )
   {
       // show prompt, and get command string
       mosPrint("> ");
       error = mosReadTerminal( buf );

       if ( error == -1 )
       {
           mosPrint("kbdtask task, send msg failed\n");
       }
       else
       {
           // send command string message to cmd task
           bytes = mosSendMessage( cmd, buf, sizeof(buf) );
       }
   }
   else // open the terminal interface
   {
       mosOpenTerminal();
       terminalIsOpen = 1;
   }
}


/* end of apptasks.c */
