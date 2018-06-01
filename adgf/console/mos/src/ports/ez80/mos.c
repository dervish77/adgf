/*****************************************************************************
 *
 *	MOS library source code
 *
 *	File:	mos.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/25/2009
 *
 *	Revs:
 *	  0.0 	03/25/2009  originated
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform.h"
#include "mos.h"


#undef DEBUG


/*
 *  GLOBALS
 */
CONTEXT_S_T *gbContext;

int gbErrorCode;


/*
 *  STATICS
 */
static int FindTaskIndex(int taskid);
static int ExecuteTask(int taskid);
static void SetErrorCode(int code);



/*  mosInitTasking		- allocates a context block 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	error		- returns '0' on init fail
 *
 */
int mosInitTasking(void)
{
    int retval;
    int taskid;
    CONTEXT_S_T *context;

    context = (CONTEXT_S_T *) malloc(sizeof(CONTEXT_S_T));

    if (context == NULL)
    {
        if (gbContext->verbose) mosDbgPrint( 0, "MOS: failed to allocate task context!!\n");
        gbErrorCode = ERR_CONTEXT_CREATE_FAIL;
        retval = FALSE;
    }
    else
    {
        gbContext = context;
        gbContext->numtasks = 0;
        gbContext->ticks = 0;
        gbContext->ticktime = DEFAULT_TICK_TIME_US;
        gbContext->errorcode = ERR_NONE;
        gbContext->verbose = TRUE;
        gbContext->maxtasks = MAX_TASKS;
        gbContext->maxtaskmem = MAX_TASK_SIZE;
        gbContext->maxmsgcount = MAX_MSG_COUNT;
        gbContext->maxmsgsize = MAX_MSG_SIZE;
        retval = TRUE;

        /* create idle task */
        taskid = mosCreateTask("idle", &idle, NULL, 1);

#ifdef DEBUG
        mosDbgPrint( 1, "mosInitTasking: success\n");
#endif
    }

    return (retval);
}



/*  mosFreeTasking		- deallocate context block and memory blocks
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosFreeTasking(void)
{
    int i;

    for (i = 0; i < gbContext->numtasks; i++)
    {
        if (gbContext->tasklist[i].valid)
        {
#ifdef DEBUG
            mosDbgPrint( 1, "... freetasking %d ...\n", i);
#endif
            free(gbContext->tasklist[i].mem.ptr);
        }
    }

    free(gbContext);
}


/*  mosSetVerboseState		- deallocate context block and memory blocks
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosSetVerboseState(BOOLEAN_T state)
{
    gbContext->verbose = state;
}


/*  mosGetVersion		- return version string for MOS library
 *
 *  Parameters:
 *	*version    - pointer to version string buffer
 *
 *  Returns:
 *	none
 */
void
mosGetVersion(char *version)
{
    if (version != NULL)
    {
        sprintf(version, "%s", VERSION);
    }
}


/*  mosGetPlatform		- return platform string for MOS library
 *
 *  Parameters:
 *	*platform    - pointer to platform string buffer
 *
 *  Returns:
 *	none
 */
void
mosGetPlatform(char *platform)
{
    if (platform != NULL)
    {
        sprintf(platform, "%s", PLATFORM);
    }
}


/*  mosGetErrorCode		- returns current error code, then clears it
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	error code
 */
int mosGetErrorCode(void)
{
    int retval = gbErrorCode;
    gbErrorCode = ERR_NONE;
    return (retval);
}


/*  mosDisplayErrorCode		- displays error code text
 *
 *  Parameters:
 *	code - error code to display
 *
 *  Returns:
 *	none
 */
void mosDisplayErrorCode(int code)
{
    switch (code)
    {
        case ERR_NONE:
            mosDbgPrint( 0, "Error code - ERR_NONE\n");
            break;
        case ERR_INVALID_TASK_ID:
            mosDbgPrint( 0, "Error code - ERR_INVALID_TASK_ID\n");
            break;
        case ERR_INVALID_TASK_INDEX:
            mosDbgPrint( 0, "Error code - ERR_INVALID_TASK_INDEX\n");
            break;
        case ERR_ALLOC_MEM_FAIL:
            mosDbgPrint( 0, "Error code - ERR_ALLOC_MEM_FAIL\n");
            break;
        case ERR_SEND_MSG_ERROR:
            mosDbgPrint( 0, "Error code - ERR_SEND_MSG_ERROR\n");
            break;
        case ERR_BCAST_MSG_ERROR:
            mosDbgPrint( 0, "Error code - ERR_BCAST_MSG_ERROR\n");
            break;
        case ERR_CONTEXT_CREATE_FAIL:
            mosDbgPrint( 0, "Error code - ERR_CONTEXT_CREATE_FAIL\n");
            break;
        case ERR_TASK_LIST_IS_FULL:
            mosDbgPrint( 0, "Error code - ERR_TASK_LIST_IS_FULL\n");
            break;
        default:
            mosDbgPrint( 0, "Error code - unknown\n");
            break;
    }
}


/*  mosCreateTask		- create task entry 
 *
 *  Parameters:
 *	*name		- pointer to task name string
 *	*proc		- pointer to task function
 *	*args		- pointer to task arguments
 *	size		- size of memory block in bytes
 *
 *  Returns:
 *	taskid		- task id of new task, INVALID_TASK_ID on fail
 */
int mosCreateTask(char *name, void *proc, void *args, int size)
{
    int index;
    int taskid = INVALID_TASK_ID;

#ifdef DEBUG
    mosDbgPrint( 2, "... create task ...\n");
#endif

    gbErrorCode = ERR_NONE;

    if (gbContext->numtasks == 0)
    {
        index = 0;
        taskid = 1;
        gbContext->tasklist[index].taskid = taskid;
    }
    else if (gbContext->numtasks < gbContext->maxtasks)
    {
        index = gbContext->numtasks;
        taskid = gbContext->tasklist[index - 1].taskid + 1;
        gbContext->tasklist[index].taskid = taskid;
    }
    else
    {
        if (gbContext->verbose) mosDbgPrint( 0, "MOS: task list full!!\n");
        gbErrorCode = ERR_TASK_LIST_IS_FULL;
        return (TASK_CREATE_FAIL);
    }

    strncpy(gbContext->tasklist[index].taskname, name, SHORT_BUFF_LEN);
    gbContext->tasklist[index].proc = (void *) (proc);
    gbContext->tasklist[index].args = args;

    gbContext->tasklist[index].queue.count = 0;
    gbContext->tasklist[index].valid = TRUE;
    gbContext->tasklist[index].ready = TRUE;
    gbContext->tasklist[index].blocked = FALSE;
    gbContext->tasklist[index].suspend = FALSE;

    gbContext->tasklist[index].mem.size = size;
    gbContext->tasklist[index].mem.ptr = NULL;

    if (size > 0 && size <= gbContext->maxtaskmem)
    {
        gbContext->tasklist[index].mem.ptr = (char *) malloc(size);
        if (NULL == gbContext->tasklist[index].mem.ptr)
        {
            if (gbContext->verbose) mosDbgPrint( 0, "MOS: failed to allocate task memory!!\n");
            gbErrorCode = ERR_ALLOC_MEM_FAIL;
            return (TASK_CREATE_FAIL);
        }
    }

    gbContext->numtasks++;

    return (taskid);
}


/*  mosDeleteTask		- delete task entry 
 *
 *  Parameters:
 *	taskid		- task id to delete
 *
 *  Returns:
 *	none
 */
void mosDeleteTask(int taskid)
{
    int index;

#ifdef DEBUG
    mosDbgPrint( 2, "... delete task ...\n");
#endif
    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        strncpy(gbContext->tasklist[index].taskname, "deleted", SHORT_BUFF_LEN);
        free(gbContext->tasklist[index].mem.ptr);
        gbContext->tasklist[index].mem.size = 0;
        gbContext->tasklist[index].valid = FALSE;
        gbContext->tasklist[index].ready = FALSE;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosSuspendTask		- suspend task entry 
 *
 *  Parameters:
 *	taskid		- task id to suspend
 *
 *  Returns:
 *	none
 */
void mosSuspendTask(int taskid)
{
    int index;

#ifdef DEBUG
    mosDbgPrint( 3, "... suspend task ...\n");
#endif
    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        gbContext->tasklist[index].ready = FALSE;
        gbContext->tasklist[index].suspend = TRUE;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosResumeTask		- un-suspend task entry 
 *
 *  Parameters:
 *	taskid		- task id to resume
 *
 *  Returns:
 *	none
 */
void mosResumeTask(int taskid)
{
    int index;

#ifdef DEBUG
    mosDbgPrint( 3, "... resume task ...\n");
#endif
    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        gbContext->tasklist[index].ready = TRUE;
        gbContext->tasklist[index].suspend = FALSE;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosBlockTask		- block task entry 
 *
 *  Parameters:
 *	taskid		- task id to block
 *
 *  Returns:
 *	none
 */
void mosBlockTask(int taskid)
{
    int index;

#ifdef DEBUG
    mosDbgPrint( 3, "... block task ...\n");
#endif
    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        gbContext->tasklist[index].ready = FALSE;
        gbContext->tasklist[index].blocked = TRUE;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosUnBlockTask		- un-block task entry 
 *
 *  Parameters:
 *	taskid		- task id to unblock
 *
 *  Returns:
 *	none
 */
void mosUnBlockTask(int taskid)
{
    int index;

#ifdef DEBUG
    mosDbgPrint( 3, "... unblock task ...\n");
#endif
    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        gbContext->tasklist[index].ready = TRUE;
        gbContext->tasklist[index].blocked = FALSE;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosSequenceTaskListOnce		- execute all tasks once
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosSequenceTaskListOnce(void)
{
    int index;

    for (index = 0; index < gbContext->numtasks; index++)
    {
        // execute task if it is valid
        if (gbContext->tasklist[index].valid)
        {
            if (gbContext->tasklist[index].blocked)
            {
                if (gbContext->verbose) mosPrint("... taskid %d is blocked ...\n", gbContext->tasklist[index].taskid);
                gbContext->tasklist[index].ready = TRUE;
                gbContext->tasklist[index].blocked = FALSE;
            }
            else if (gbContext->tasklist[index].suspend)
            {
                if (gbContext->verbose) mosPrint("... taskid %d is suspended ...\n", gbContext->tasklist[index].taskid);
                gbContext->tasklist[index].ready = TRUE;
                gbContext->tasklist[index].suspend = FALSE;
            }
            else if (gbContext->tasklist[index].ready)
            {
                if (gbContext->verbose) mosPrint("... taskid %d - ", gbContext->tasklist[index].taskid);
                ExecuteTask(index);
            }
        }
     
        // simulate an OS time tick
        usleep(gbContext->ticktime);
    }
}


/*  mosSequenceTasks		- execute all tasks forever
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosSequenceTasks(void)
{
    int index;

    while (1)
    {
        // execute all tasks once
        mosSequenceTaskListOnce();
    }
}


/*  mosGetTaskId		- lookup task id by task name
 *
 *  Parameters:
 *	*name		- pointer to task name string
 *
 *  Returns:
 *	taskid		- task id of named task, INVALID_TASK_ID on fail
 */
int mosGetTaskId(char *name)
{
    int i, taskid = INVALID_TASK_ID;

    gbErrorCode = ERR_NONE;

    for (i = 0; i < gbContext->numtasks; i++)
    {
        if (strcmp(name, gbContext->tasklist[i].taskname) == 0)
        {
            taskid = gbContext->tasklist[i].taskid;
            break;
        }
    }

    if (taskid == INVALID_TASK_ID)
    {
        gbErrorCode = ERR_INVALID_TASK_ID;
    }

    return (taskid);
}


/*  mosIsTaskValid	- lookup whether task is valid or not by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	valid		- '1' if valid, '0' if not
 */
int mosIsTaskValid(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].valid);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (INVALID_TASK_INDEX);
    }
}


/*  mosIsTaskSuspended	- lookup whether task is suspended or not by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	valid		- '1' if suspended, '0' if not
 */
int mosIsTaskSuspended(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].suspend);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (INVALID_TASK_INDEX);
    }
}


/*  mosIsTaskBlocked	- lookup whether task is blocked or not by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	valid		- '1' if blocked, '0' if not
 */
int mosIsTaskBlocked(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].valid);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (INVALID_TASK_INDEX);
    }
}


/*  mosGetTaskMemPtr	- lookup memory pointer by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	*mem		- pointer to memory block
 */
char *mosGetTaskMemPtr(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].mem.ptr);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (NULL);
    }
}


/*  mosGetTaskMemSize	- lookup memory size by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	size		- size of memory block in bytes
 */
int mosGetTaskMemSize(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].mem.size);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (INVALID_TASK_INDEX);
    }
}


/*  mosClearMessageQueue	- clear msg queue count by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	none
 */
void mosClearMessageQueue(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        gbContext->tasklist[index].queue.count = 0;
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }
}


/*  mosCheckMessageQueue	- lookup msg queue count by task id
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *
 *  Returns:
 *	count		- number of msgs in queue
 */
int mosCheckMessageQueue(int taskid)
{
    int index;

    gbErrorCode = ERR_NONE;

    index = FindTaskIndex(taskid);

    if (index != INVALID_TASK_INDEX)
    {
        return (gbContext->tasklist[index].queue.count);
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (INVALID_TASK_INDEX);
    }
}


/*  mosReadMessage		- read message from queue by index
 *
 *  Parameters:
 *	taskid		- task id to lookup
 *	index		- index into msg queue
 *	*buf		- pointer to msg buffer for copy
 *
 *  Returns:
 *	size		- size of bytes copied
 */
int mosReadMessage(int taskid, int index, char *buf)
{
    int task, size;
    int msgindex = index;

    gbErrorCode = ERR_NONE;

    task = FindTaskIndex(taskid);

    if (task != INVALID_TASK_INDEX)
    {
        if (msgindex < gbContext->tasklist[task].queue.count)
        {
            size = gbContext->tasklist[task].queue.msg[msgindex].size;
            strncpy(buf, gbContext->tasklist[task].queue.msg[msgindex].buf, size);
	    }
	    else
	    {
            size = 0;
            buf[0] = '\0';
            gbErrorCode = ERR_READ_MSG_INDEX_ERROR;
	    }
    }
    else
    {
        size = 0;
        buf[0] = '\0';
        gbErrorCode = ERR_INVALID_TASK_INDEX;
    }

    return (size);
}


/*  mosSendMessage		- send message to another task
 *
 *  Parameters:
 *	desttaskid	- destination task id
 *	*buf		- pointer to msg buffer for copy
 *	size 		- number of bytes in buffer
 *
 *  Returns:
 *	size 		- number of bytes copied, 0 if error
 */
int mosSendMessage(int desttaskid, char *buf, int size)
{
    int msgindex, taskindex;

    gbErrorCode = ERR_NONE;

    taskindex = FindTaskIndex(desttaskid);

    // if destination task is valid and msg queue is not full and msg size is valid
    // then send the message
    //
    if (taskindex != INVALID_TASK_INDEX)
    {
        if ((gbContext->tasklist[taskindex].valid) 
                && (gbContext->tasklist[taskindex].queue.count < gbContext->maxmsgcount) 
                && (size < gbContext->maxmsgsize))
        {
            msgindex = gbContext->tasklist[taskindex].queue.count;
            strncpy(gbContext->tasklist[taskindex].queue.msg[msgindex].buf, buf, size);
            gbContext->tasklist[taskindex].queue.msg[msgindex].size = size;
            gbContext->tasklist[taskindex].queue.count++;
            return (size);
        }
        else
        {
            gbErrorCode = ERR_SEND_MSG_ERROR;
            return (SEND_MSG_ERROR);
        }
    }
    else
    {
        gbErrorCode = ERR_INVALID_TASK_INDEX;
        return (SEND_MSG_ERROR);
    }
}


/*  mosSendBroadcast		- send message to all tasks
 *
 *  Parameters:
 *	*buf		- pointer to msg buffer for copy
 *	size 		- number of bytes in buffer
 *
 *  Returns:
 *	size 		- number of bytes copied, SEND_MSG_ERROR if error
 */
int mosSendBroadcast(char *buf, int size)
{
    int i;
    int result = size;
    int msgindex;

#ifdef DEBUG
    mosDbgPrint( 4, "... broadcasting message - %s ...\n", buf);
#endif

    gbErrorCode = ERR_NONE;

    // loop through all the tasks
    for (i = 0; i < gbContext->numtasks; i++)
    {
        // if destination task is valid and msg queue is not full and msg size is valid
        // then send the message
        //
        if ((gbContext->tasklist[i].valid) 
                && (gbContext->tasklist[i].queue.count < gbContext->maxmsgcount) 
                && (size < gbContext->maxmsgsize))
        {
            msgindex = gbContext->tasklist[i].queue.count;
            strncpy(gbContext->tasklist[i].queue.msg[msgindex].buf, buf, size);
            gbContext->tasklist[i].queue.msg[msgindex].size = size;
            gbContext->tasklist[i].queue.count++;
        }   
        else
        {
            gbErrorCode = ERR_BCAST_MSG_ERROR;
            result = SEND_MSG_ERROR;
        }
    }

    return (result);
}


/*  mosDisplayTaskList		- display task list
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosDisplayTaskList(void)
{
    int i;

    SetErrorCode( ERR_NONE );

    mosPrint("Task List:\n");
    mosPrint("   Id Name                 V R B S Mem  Cnt\n");
    mosPrint("   -- ----                 - - - - ---  ---\n");

    for (i = 0; i < gbContext->numtasks; i++)
    {
        mosPrint("   %02d %-20s %d %d %d %d %04d %d\n",
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



/* PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  */

/*  FindTaskIndex	- locate task within tasklist 
 *
 *  Parameters:
 *	taskid		- task id
 *
 *  Returns:
 *	index		- index within tasklist, INVALID_TASK_INDEX on fail
 */
static int FindTaskIndex(int taskid)
{
    int index = INVALID_TASK_INDEX;
    int ii;

    for (ii = 0; ii < gbContext->numtasks; ii++)
    {
        if (gbContext->tasklist[ii].taskid == taskid)
        {
            index = ii;
            break;
        }
    }

    return (index);
}

/*  ExecuteTask		- execute task function 
 *
 *  Parameters:
 *	index	- index into task list
 *
 *  Returns:
 *	none
 */
static int ExecuteTask(int index)
{
    int result;

#ifdef DEBUG
    mosDbgPrint( 5, "... execute task ...\n");
#endif

    result = (gbContext->tasklist[index].proc) (gbContext->tasklist[index].args);

    return (result);
}

/*  SetErrorCode	- sets the error code global 
 *
 *  Parameters:
 *	code	- error code to set
 *
 *  Returns:
 *	none
 */
static void SetErrorCode(int code)
{
    gbErrorCode = code;
}

/*  idle		- idle task 
 *
 *  Parameters:
 *	args	- arguments
 *
 *  Returns:
 *	none
 */
void idle(void *args)
{
    int id = mosGetTaskId("idle");
    if (gbContext->verbose) mosPrint("idle task, id = %d, args NONE\n", id);
}

/* end of mos.c */
