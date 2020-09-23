/*****************************************************************************
 *
 *	MOS Demo program routines.
 *
 *	File:	demo.c
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

#include "demo.h"

#include "tasks.h"



#define DEBUG



/*
 *  GLOBALS
 */
DATABASE_S_T *data;


/*
 *  STATICS
 */


/*  DemoInit	- initializes demo database
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to  database
 *
 *  Returns:
 *
 */
void DemoInit( DATABASE_S_T *mdata )
{
   int	taskid;

   mosInitTasking();
   
   taskid = mosCreateTask( "dummy1", &dummy, &dummyargs, 16 );
   taskid = mosCreateTask( "dummy2", &dummy, &dummyargs, 0 );
   taskid = mosCreateTask( "getid", &dummygetid, &dummyargs, 64 );
   taskid = mosCreateTask( "suspend", &dummysuspend, &dummyargs, 128 );
   taskid = mosCreateTask( "memory", &dummymemory, &dummyargs, 256 );
   taskid = mosCreateTask( "msg1", &dummymsg1, &dummyargs, 32 );
   taskid = mosCreateTask( "msg2", &dummymsg2, &dummyargs, 32 );

   mdata->temp1 = 0;
   mdata->temp2 = 0;
}


/*  DemoClose	- closes demo
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to database
 *
 *  Returns:
 *
 */
void DemoClose( DATABASE_S_T *mdata )
{
   mosFreeTasking();
}


/*  DemoRun		- runs canned demo
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to sim database
 *
 *  Returns:
 *
 */
void DemoRun( DATABASE_S_T *mdata )
{
   mosSequenceTaskListOnce();
}


/*  DemoVersion		- displays version of MOS lui
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *
 */
void DemoVersion( void )
{
   char version[10];
   char platform[10];

   mosGetVersion( version );
   mosGetPlatform( platform );

   mosPrint("MOS %s on %s\n", version, platform);
}


/*  DemoHelp		- displays demo help
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *
 */
void DemoHelp( void )
{
   printf("Available commands:\n");
   printf("  run              - run tasking demo\n");
   printf("  list             - display task list\n");
   printf("  loop [#]         - loop for count or forever\n");
   printf("  create <name>    - create 'dummy' task\n");
   printf("  delete #         - delete task\n");
   printf("  suspend #        - suspend task\n");
   printf("  resume #         - resume task\n");
   printf("  block #          - block task\n");
   printf("  unblock #        - unblock task\n");
   printf("  broadcast        - create 'broadcast' task\n");
   printf("  version          - display version\n");
   printf("  help             - display help\n");
   printf("  exit             - exit demo\n");
}


/*  DemoInteractive	- runs interactive demo
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to database
 *
 *  Returns:
 *
 */
void DemoInteractive( DATABASE_S_T *mdata )
{
   LONG_BUFFER_T	cmd, cmdstring;	
   BOOLEAN_T		exit = FALSE;
   char 		*buffer;
   char			*cmdargs[MAX_CMD_ARGS];
   int			i, argcount;
   int			id;


   /* loop while not exit */
   while (!exit)
   {
      /* get command string */
      printf("\n%s ", PROMPT);
      fgets( cmd, LONG_BUFF_LEN, stdin );
      strncpy( cmdstring, cmd, LONG_BUFF_LEN );

      /* parse command string */
      buffer = &cmdstring[0];
      cmdstring[LONG_BUFF_LEN - 1] = '\0';
      argcount = ParseString( buffer, cmdargs );

      if ( strcmp( cmdargs[0], "run" ) == 0 )
      {
         DemoRun( mdata );
      }
      else if ( strcmp( cmdargs[0], "loop" ) == 0 )
      {
         if (argcount == 1)
         {
            for ( ;; )
            {
               DemoRun( mdata );
            }
         }
         else if (argcount == 2)
         {
            for (i=0; i < atoi(cmdargs[1]); i++)
            {
               DemoRun( mdata );
            }
         }
         else
         {
            DemoHelp();            
         }

      }
      else if ( strcmp( cmdargs[0], "create" ) == 0 )
      {
         if (argcount == 2)
         {
            id = mosCreateTask( cmdargs[1], &dummy, &dummyargs, 1 );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "broadcast" ) == 0 )
      {
         id = mosCreateTask( "broadcast", &dummybroadcast, &dummyargs, 1 );
      }
      else if ( strcmp( cmdargs[0], "delete" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            mosDeleteTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "suspend" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            mosSuspendTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "resume" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            mosResumeTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "block" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            mosBlockTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "unblock" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            mosUnBlockTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "list" ) == 0 )
      {
         mosDisplayTaskList( );
      }
      else if ( strcmp( cmdargs[0], "version" ) == 0 )
      {
         DemoVersion();
      }
      else if ( strcmp( cmdargs[0], "help" ) == 0 )
      {
         DemoHelp();
      }
      else if ( strcmp( cmdargs[0], "h" ) == 0 )
      {
         DemoHelp();
      }
      else if ( strcmp( cmdargs[0], "?" ) == 0 )
      {
         DemoHelp();
      }
      else if ( strcmp( cmdargs[0], "exit" ) == 0 )
      {
         printf("exit\n");
         exit = TRUE;
      }
      else if ( strcmp( cmdargs[0], "ex" ) == 0 )
      {
         printf("exit\n");
         exit = TRUE;
      }
      else
      {
         printf("Error - unknown command!\n");
      }
   }
}


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
   fprintf(stderr, "Usage: mosdemo [-d | -h | -i | -l]\n");
}


/* end of demo.c */
