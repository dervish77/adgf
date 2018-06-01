/*****************************************************************************
 *
 *	Main Loop program routines.
 *
 *	File:	mloop.c
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



#undef DEBUG


/*
 *  GLOBALS
 */
CONTEXT_S_T *gbContext;


/*
 *  STATICS
 */
static int FindTaskIndex( int taskid );



/*  InitTasking		- allocates a context block 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	error		- returns '0' on init fail
 *
 */
int 
InitTasking( void )
{
   CONTEXT_S_T	*context;

   context = (CONTEXT_S_T *)malloc( sizeof(CONTEXT_S_T) );

   if (context == NULL)
   {
      return( 0 );
   }
   else
   {
      gbContext = context;
      gbContext->numtasks = 0;
      gbContext->ticks = 0;
      gbContext->ticktime = DEFAULT_TICK_TIME;
      return( 1 );
   }
}



/*  FreeTasking		- deallocate context block and memory blocks
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
FreeTasking( void )
{
   int i;

   for (i = 0; i < gbContext->numtasks; i++)
   {
      if ( gbContext->tasklist[i].valid )
         free( gbContext->tasklist[i].mem.ptr );
   }

   free( gbContext );
}


/*  CreateTask		- create task entry 
 *
 *  Parameters:
 *	*name		- pointer to task name string
 *	*proc		- pointer to task function
 *	*args		- pointer to task arguments
 *	size		- size of memory block in bytes
 *
 *  Returns:
 *	taskid		- task id of new task, -1 on fail
 */
int
CreateTask( char *name, void (*proc)(void *), void *args, int size )
{
   int	index;
   int	taskid = -1;

#ifdef DEBUG
   printf("\n... create task ...\n");
#endif

   if (gbContext->numtasks == 0)
   {
      index = 0;
      taskid = gbContext->tasklist[index].taskid = 1;
   }
   else if (gbContext->numtasks < MAX_TASKS)
   {
      index = gbContext->numtasks;
      taskid = gbContext->tasklist[index - 1].taskid + 1;
      gbContext->tasklist[index].taskid = taskid;
   }
   else
   {
      printf("\ntask list full\n");
      return( -1 );
   }

   strncpy( gbContext->tasklist[index].taskname, name, SHORT_BUFF_LEN );
   gbContext->tasklist[index].proc = (void *)(proc);
   gbContext->tasklist[index].args = args;
   gbContext->tasklist[index].mem.size = size;
   gbContext->tasklist[index].mem.ptr = (char*)malloc( size );
   gbContext->tasklist[index].queue.count = 0;
   gbContext->tasklist[index].valid = TRUE;
   gbContext->tasklist[index].ready = TRUE;
   gbContext->tasklist[index].blocked = FALSE;
   gbContext->tasklist[index].suspend = FALSE;
   gbContext->numtasks++;

   return( taskid );
}


/*  DeleteTask		- delete task entry 
 *
 *  Parameters:
 *	taskid		- task id to delete
 *
 *  Returns:
 *	none
 */
void
DeleteTask( int taskid )
{
   int	index;

#ifdef DEBUG
   printf("\n... delete task ...\n");
#endif

   index = FindTaskIndex( taskid );

   strncpy( gbContext->tasklist[index].taskname, "deleted", SHORT_BUFF_LEN );
   free( gbContext->tasklist[index].mem.ptr );
   gbContext->tasklist[index].mem.size = 0;
   gbContext->tasklist[index].valid = FALSE;
   gbContext->tasklist[index].ready = FALSE;
}


/*  SuspendTask		- suspend task entry 
 *
 *  Parameters:
 *	taskid		- task id to suspend
 *
 *  Returns:
 *	none
 */
void
SuspendTask( int taskid )
{
   int	index;

#ifdef DEBUG
   printf("\n... suspend task ...\n");
#endif

   index = FindTaskIndex( taskid );

   gbContext->tasklist[index].ready = FALSE;
   gbContext->tasklist[index].suspend = TRUE;
}


/*  ResumeTask		- un-suspend task entry 
 *
 *  Parameters:
 *	taskid		- task id to resume
 *
 *  Returns:
 *	none
 */
void
ResumeTask( int taskid )
{
   int	index;

#ifdef DEBUG
   printf("\n... resume task ...\n");
#endif

   index = FindTaskIndex( taskid );

   gbContext->tasklist[index].ready = TRUE;
   gbContext->tasklist[index].suspend = FALSE;
}


/*  BlockTask		- block task entry 
 *
 *  Parameters:
 *	taskid		- task id to block
 *
 *  Returns:
 *	none
 */
void
BlockTask( int taskid )
{
   int	index;

#ifdef DEBUG
   printf("... block task ...\n");
#endif

   index = FindTaskIndex( taskid );

   gbContext->tasklist[index].ready = FALSE;
   gbContext->tasklist[index].blocked = TRUE;
}


/*  UnBlockTask		- un-block task entry 
 *
 *  Parameters:
 *	taskid		- task id to unblock
 *
 *  Returns:
 *	none
 */
void
UnBlockTask( int taskid )
{
   int	index;

#ifdef DEBUG
   printf("... unblock task ...\n");
#endif

   index = FindTaskIndex( taskid );

   gbContext->tasklist[index].ready = TRUE;
   gbContext->tasklist[index].blocked = FALSE;
}


/*  FindTaskIndex	- locate task within tasklist 
 *
 *  Parameters:
 *	taskid		- task id
 *
 *  Returns:
 *	index		- index within tasklist, -1 on fail
 */
int
FindTaskIndex( int taskid )
{
   int index = -1;

   for (index = 0; index < gbContext->numtasks; index++ )
   {
      if (gbContext->tasklist[index].taskid == taskid)
         break;
   }

   return( index );   
}


/*  ExecuteTask		- execute task function 
 *
 *  Parameters:
 *	index	- index into task list
 *
 *  Returns:
 *	none
 */
void
ExecuteTask( int index )
{
   int 	result;

#ifdef DEBUG
   printf("... execute task ...\n");
#endif

   (gbContext->tasklist[index].proc)(gbContext->tasklist[index].args);
}


/*  SequenceTaskList		- execute all tasks once
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
SequenceTaskList( void )
{
   int 	index;

   printf("\n");
   for (index = 0; index < gbContext->numtasks; index++)
   {
      if (gbContext->tasklist[index].valid)
      {
         if (gbContext->tasklist[index].blocked)
         {
            printf("... taskid %d is blocked ...\n", gbContext->tasklist[index].taskid );
         }
         else if (gbContext->tasklist[index].suspend)
         {
            printf("... taskid %d is suspended ...\n", gbContext->tasklist[index].taskid );
         }
         else if (gbContext->tasklist[index].ready)
         {
            printf("... taskid %d - ", gbContext->tasklist[index].taskid );
            ExecuteTask( index );
         }
      }
   }
}


/*  DisplayTaskList		- display task list
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
DisplayTaskList( void )
{
   int 		i;

   printf("\nTask List:\n");
   printf("   id name                 V R B S Mem  Cnt\n");

   for (i = 0; i < gbContext->numtasks; i++)
   {
      printf("   %02d %-20s  %d %d %d %d %04d %d\n", 
		gbContext->tasklist[i].taskid,
		gbContext->tasklist[i].taskname,
		gbContext->tasklist[i].valid,
		gbContext->tasklist[i].ready,
		gbContext->tasklist[i].blocked,
		gbContext->tasklist[i].suspend,
		gbContext->tasklist[i].mem.size,
		gbContext->tasklist[i].queue.count);
   }
}


/*  GetTaskId		- lookup task id by task name
 *
 *  Parameters:
 *	*name		- pointer to task name string
 *
 *  Returns:
 *	taskid		- task id of named task
 */
int
GetTaskId( char *name )
{
   int 		i, taskid = 0;

   for (i = 0; i < gbContext->numtasks; i++)
   {
      if (strcmp( name, gbContext->tasklist[i].taskname ) == 0)
      {
         taskid = gbContext->tasklist[i].taskid;
         break;
      }
   }
   return( taskid );
}


/*  GetTaskMemPtr	- lookup memory pointer by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	*mem		- pointer to memory block
 */
char *GetTaskMemPtr( int taskid )
{
   int	index;

   index = FindTaskIndex( taskid );

   return( gbContext->tasklist[index].mem.ptr );
}


/*  GetTaskMemSize	- lookup memory size by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	size		- size of memory block in bytes
 */
int
GetTaskMemSize( int taskid )
{
   int	index;

   index = FindTaskIndex( taskid );

   return( gbContext->tasklist[index].mem.size );
}


/*  ClearMessageQueue	- clear msg queue count by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	none
 */
void
ClearMessageQueue( int taskid )
{
   int	index;

   index = FindTaskIndex( taskid );

   gbContext->tasklist[index].queue.count = 0;
}


/*  CheckMessageQueue	- lookup msg queue count by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	count		- number of msgs in queue
 */
int
CheckMessageQueue( int taskid )
{
   int	index;

   index = FindTaskIndex( taskid );

   return( gbContext->tasklist[index].queue.count );
}


/*  ReadMessage		- read message from queue by index
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *	index		- index into msg queue
 *	*buf		- pointer to msg buffer for copy
 *
 *  Returns:
 *	size		- size of bytes copied
 */
int
ReadMessage( int taskid, int index, char *buf  )
{
   int	task, size;

   task = FindTaskIndex( taskid );

   size = gbContext->tasklist[task].queue.msg[index].size;

   strncpy( buf, 
	gbContext->tasklist[task].queue.msg[index].buf, size );

   return( size );
}


/*  SendMessage		- send message to another task
 *
 *  Parameters:
 *	desttaskid	- destination task id
 *	*buf		- pointer to msg buffer for copy
 *	size 		- number of bytes in buffer
 *
 *  Returns:
 *	size 		- number of bytes copied, 0 if error
 */
int
SendMessage( int desttaskid, char *buf, int size )
{
   int	index, desttask;

   desttask = FindTaskIndex( desttaskid ); 

   if ( gbContext->tasklist[desttask].queue.count < MAX_MSG_COUNT
	&& size < MAX_MSG_SIZE )
   {
      index = gbContext->tasklist[desttask].queue.count + 1;
      strncpy( gbContext->tasklist[desttask].queue.msg[index].buf,
		buf,
		size);
      gbContext->tasklist[desttask].queue.msg[index].size = size;
      gbContext->tasklist[desttask].queue.count++;
      return( size );
   }
   else
   {
      return( 0 );
   }
}


/* end of mloop.c */
