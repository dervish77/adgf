/*****************************************************************************
 *
 *	Main Loop Demo program routines.
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

#ifndef _MLOOP_H
#include "mloop.h"
#endif

#ifndef _DEMO_H
#include "demo.h"
#endif


#define DEBUG


/*
 *  GLOBALS
 */
DATABASE_S_T *data;


/*
 *  STATICS
 */
static void dummy( void *args );
static void dummygetid( void *args );
static void dummysuspend( void *args );

static ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};


char *getstr (char *string) 
{
  char *sptr = string;
  char chr;

  while (TRUE) {
    chr = getchar();

    if (chr == '\r') {
      *sptr = ' ';
      *(sptr+1) = '\0';
      return (string);
    } /* Remove LF */

    *(sptr++) = chr;

  }  /* while (TRUE) */
} /* gets */


/*  DemoInit	- initializes demo database
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to  database
 *
 *  Returns:
 *
 */
void 
DemoInit( DATABASE_S_T *mdata )
{
   int	taskid;

   InitTasking();

   taskid = CreateTask( "dummy1", &dummy, &dummyargs, 16 );
   if (!taskid)
   {
      printf("DemoInit: create task dummy1 failed!\n");
   }

   taskid = CreateTask( "dummy2", &dummy, &dummyargs, 1 );
   if (!taskid)
   {
      printf("DemoInit: create task dummy1 failed!\n");
   }

   taskid = CreateTask( "getid", &dummygetid, &dummyargs, 1024 );
   if (!taskid)
   {
      printf("DemoInit: create task getid failed!\n");
   }

   taskid = CreateTask( "suspend", &dummysuspend, &dummyargs, 128 );
   if (!taskid)
   {
      printf("DemoInit: create task suspend failed!\n");
   }

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
void 
DemoClose( DATABASE_S_T *mdata )
{
   FreeTasking();
}


/*  DemoRun		- runs canned demo
 *
 *  Parameters:
 *	DATABASE_S_T *mdata	- pointer to sim database
 *
 *  Returns:
 *
 */
void 
DemoRun( DATABASE_S_T *mdata )
{
   SequenceTaskList();
}


/*  DemoHelp		- displays demo help
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *
 */
void 
DemoHelp( void )
{
   printf("\nAvailable commands:\n");
   printf("  run              - run tasking demo\n");
   printf("  list             - display task list\n");
   printf("  loop [#]         - loop for count or forever\n");
   printf("  create <name>    - create task\n");
   printf("  delete #         - delete task\n");
   printf("  suspend #        - suspend task\n");
   printf("  resume #         - resume task\n");
   printf("  block #          - block task\n");
   printf("  unblock #        - unblock task\n");
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
void 
DemoInteractive( DATABASE_S_T *mdata )
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
      getstr( cmd );
//	  printf("You typed cmd - %s\n", cmd);     
	  strncpy( cmdstring, cmd, LONG_BUFF_LEN );
//	  printf("You typed cmdstring - %s\n", cmdstring);  
//	  printf("strlen cmdstring - %d\n", strlen(cmdstring));
     
      /* parse command string */
      buffer = &cmdstring[0];
      cmdstring[LONG_BUFF_LEN - 1] = '\0';
      argcount = ParseString( buffer, cmdargs );

// 	  printf("You typed %d cmdargs[0] - %s %s\n", argcount, cmdargs[0], cmdargs[1]);
      
	  if ( strcmp( cmdargs[0], "run" ) == 0 )
      {
         DemoRun( mdata );
      }
      else if ( strcmp( cmdargs[0], "loop" ) == 0 )
      {
         if (argcount == 1)
         {
            for ( ;; )
               DemoRun( mdata );
         }
         else if (argcount == 2)
         {
            for (i=0; i < atoi(cmdargs[1]); i++)
               DemoRun( mdata );
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
            id = CreateTask( cmdargs[1], &dummy, &dummyargs, 1 );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "delete" ) == 0 )
      {
         if (argcount == 2)
         {
            id = atoi( cmdargs[1] );
            DeleteTask( id );
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
            SuspendTask( id );
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
            ResumeTask( id );
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
            BlockTask( id );
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
            UnBlockTask( id );
         }
         else
         {
            DemoHelp();            
         }
      }
      else if ( strcmp( cmdargs[0], "list" ) == 0 )
      {
         DisplayTaskList( );
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
         printf("\nError - unknown command!\n");
      }
   }
}


void
dummy( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   printf("dummy task running, args %d %d %d\n", my->arg1, my->arg2, my->arg3);
}


void
dummygetid( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   id = GetTaskId( "getid" );
   printf("getid task running, args %d %d %d, id = %d\n", 
	my->arg1, my->arg2, my->arg3, id);
}


void
dummysuspend( void *args )
{
   int id;
   ARG_STRUCT *my;

   my = args;

   id = GetTaskId( "suspend" );
   SuspendTask( id );
   printf("suspend task running, args %d %d %d, id = %d\n", 
	my->arg1, my->arg2, my->arg3, id);
}


/*  ErrorUsage		- output usage error message and exit 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
ErrorUsage( void )
{
   printf("Usage: mainloop [-i | -l]\n");
//   exit(1);
}


/*  ErrorOpenFile	- output open file error message and exit 
 *
 *  Parameters:
 *	string		- pointer to character string
 *
 *  Returns:
 *	none
 */
void 
ErrorOpenFile( char *string )
{
   printf("Error:  opening %s as list file\n", string);
//   exit(1);
}

/* end of demo.c */
