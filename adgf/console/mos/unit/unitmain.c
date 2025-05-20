/*****************************************************************************
 *
 *	MOS unit test main program (no CLI).
 *
 *	File:	unitmain.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *	Usage:	
 *              mosunit           loop 5 times 
 *              mosunit -c [#]    loop # times
 *              mosunit -d        display task list
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mos.h"

#include "unittasks.h"


#define DEBUG



/*
 *  GLOBALS
 */



/*
 *  STATICS
 */



/*
 *  EXTERNS
 */






/*  ErrorUsage		- output usage error message and exit 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void ErrorUsage( void )
{
   fprintf(stderr, "Usage: mosunit [ -c # | -d ]\n");
   exit(0);
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
int main(int argc, char **argv)
{
   int	i, taskid, loopcnt = 5;
   char version[10];
   char platform[10];
   char messageout[16];
   char messagein[16];
   int code;

   mosPrint("Unit Test App\n");

   mosInitTasking();
   mosGetVersion( version );
   mosGetPlatform( platform );
   mosSetVerboseState( TRUE );

   mosPrint("MOS %s on %s\n", version, platform);

   mosPrint("testing task sequencing...\n");
   taskid = mosCreateTask( "dummy1", &dummy, &dummyargs, 16 );
   taskid = mosCreateTask( "dummy2", &dummy, &dummyargs, 1 );
   taskid = mosCreateTask( "dummy3", &dummydelete, &dummyargs, 5 );
   taskid = mosCreateTask( "getid", &dummygetid, &dummyargs, 64 );
   taskid = mosCreateTask( "suspend", &dummysuspend, &dummyargs, 128 );
   taskid = mosCreateTask( "block", &dummyblock, &dummyargs, 1 );
   taskid = mosCreateTask( "memory", &dummymemory, &dummyargs, 256 );
   taskid = mosCreateTask( "msg1", &dummymsg1, &dummyargs, 32 );
   taskid = mosCreateTask( "msg2", &dummymsg2, &dummyargs, 32 );

   switch (argc)
   {
      case 1:
         for (i=0; i < loopcnt; i++)
         {
            mosSequenceTaskListOnce();
         }
         break;

      case 2:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'd') )
         {
            mosDisplayTaskList();
         }
         else
         {
            ErrorUsage();
         }
         break;

      case 3:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'c') )
         {
            loopcnt = atoi(argv[2]);
            for (i=0; i < loopcnt; i++)
            {
               mosSequenceTaskListOnce();
            }
         }
         else
         {
            ErrorUsage();
         }
         break;

      default:
         ErrorUsage();
         break;
   }

   mosFreeTasking();
   mosPrint("...done.\n");

   mosPrint("testing error codes...\n");
   code = mosGetErrorCode();
   mosDisplayErrorCode( code );
   mosDisplayErrorCode( ERR_INVALID_TASK_ID );
   mosDisplayErrorCode( ERR_INVALID_TASK_INDEX );
   mosDisplayErrorCode( ERR_SEND_MSG_ERROR );
   mosDisplayErrorCode( ERR_CONTEXT_CREATE_FAIL );
   mosDisplayErrorCode( ERR_TASK_LIST_IS_FULL );
   mosDisplayErrorCode( ERR_ALLOC_MEM_FAIL );
   mosDisplayErrorCode( ERR_BCAST_MSG_ERROR );
   mosDisplayErrorCode( ERR_CONTEXT_CREATE_FAIL );
   mosDisplayErrorCode( ERR_TASK_LIST_IS_FULL );
   mosDisplayErrorCode( ERR_DEVICE_OPEN_FAIL );
   mosDisplayErrorCode( ERR_DEVICE_READ_FAIL );
   mosDisplayErrorCode( ERR_DEVICE_WRITE_FAIL );
   mosDisplayErrorCode( ERR_DEVICE_CLOSE_FAIL );
   mosDisplayErrorCode( ERR_READ_MSG_INDEX_ERROR );
   mosDisplayErrorCode( 1000 );
   mosPrint("...done.\n");

   mosPrint("testing task create...\n");
   mosInitTasking();
   mosSetVerboseState( TRUE );
   taskid = mosCreateTask( "dummy1", &dummy, &dummyargs, 1024 );
   for (i = 0; i < 12; i++)
   {
      taskid = mosCreateTask( "dummy1", &dummy, &dummyargs, 16 );
      code = mosGetErrorCode();
      if (code == ERR_TASK_LIST_IS_FULL) break;
   }
   mosDisplayErrorCode( code );
   mosPrint("...done.\n");

   mosPrint("testing invalid task ids...\n");
   taskid = 99;
   sprintf( messageout, "Fake");
   mosGetTaskId( messageout );
   mosDeleteTask( taskid );
   mosDisplayErrorCode( mosGetErrorCode() );
   mosSuspendTask( taskid );
   mosResumeTask( taskid );
   mosBlockTask( taskid );
   mosUnBlockTask( taskid );
   mosIsTaskValid( taskid );
   mosIsTaskSuspended( taskid );
   mosIsTaskBlocked( taskid );
   mosGetTaskMemPtr( taskid );
   mosGetTaskMemSize( taskid );
   sprintf( messageout, "Testing");
   mosSendMessage( taskid, messageout, 0 );
   mosDisplayErrorCode( mosGetErrorCode() );
   mosCheckMessageQueue( taskid );
   mosReadMessage( taskid, 1, messagein );
   mosReadMessage( mosGetTaskId("dummy1"), 9, messagein );
   mosDisplayErrorCode( mosGetErrorCode() );
   mosClearMessageQueue( taskid );
   mosPrint("...done\n");

   mosPrint("testing platform functions...\n");
   mosOpenKeyboard();
   mosReadKeyboard();
   mosCloseKeyboard();
   mosWriteLcd( messageout );
   mosCloseLcd();
   mosOpenLcd();
   mosOpenTerminal();
   //mosReadTerminal( messagein );
   mosWriteTerminal( messageout );
   mosCloseTerminal();
   code = mosGetErrorCode();
   mosDisplayErrorCode( code );
   mosPrint("...done\n");

   mosPrint("testing broadcast...\n");
   sprintf( messageout, "Hello");
   mosSendBroadcast( messageout, sizeof(messageout) );
   code = mosGetErrorCode();
   mosDisplayErrorCode( code );
   mosPrint("...done.\n");

   exit(0);
}


/* end of unitmain.c */
