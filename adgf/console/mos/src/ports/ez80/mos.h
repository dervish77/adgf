/*****************************************************************************
 *
 *	MOS library source code
 *
 *	File:	mos.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/

#ifndef _MOS_H
#define _MOS_H

#include "types.h"


#define VERSION "0.96"


/*  define task tunables
 */
#define MAX_TASKS		        10      /* max number of tasks */
#define MAX_TASK_SIZE		    1024    /* max size of task memory block in bytes */

#define DEFAULT_TICK_TIME_US    100     /* tick time in microseconds */
#if 0
#define DEFAULT_TICK_TIME_US    50000   /* tick time in microseconds */
#endif

/*  define messaging tunables
 */
#define MAX_MSG_COUNT		    5
#define MAX_MSG_SIZE		    32


/*  define scheduler related types
 */
#define SCHED_RR                1
#define SCHED_FIFO              2


/*  define return codes
 */
#define INVALID_TASK_ID         -1
#define INVALID_TASK_INDEX      0
#define SEND_MSG_ERROR          0
#define TASK_CREATE_FAIL       -1


/*  define error codes
 */
#define ERR_NONE                    0
#define ERR_INVALID_TASK_ID         101
#define ERR_INVALID_TASK_INDEX      102
#define ERR_ALLOC_MEM_FAIL          103
#define ERR_SEND_MSG_ERROR          104
#define ERR_BCAST_MSG_ERROR         105
#define ERR_CONTEXT_CREATE_FAIL     106
#define ERR_TASK_LIST_IS_FULL       107
#define ERR_DEVICE_OPEN_FAIL        108
#define ERR_DEVICE_READ_FAIL        109
#define ERR_DEVICE_WRITE_FAIL       110
#define ERR_DEVICE_CLOSE_FAIL       111
#define ERR_READ_MSG_INDEX_ERROR    112


/*  define argument structure type
 */
typedef struct arg_struct
{
    int arg1;
    int arg2;
    int arg3;
} ARG_STRUCT;


/*  define memory block structure type
 */
typedef struct memblock_s_t
{
    int size;                   /* size in bytes */
    char *ptr;                  /* pointer to start of block */
} MEMBLOCK_S_T;


/*  define message structure type
 */
typedef struct msg_s_t
{
    int size;                   /* size of message in bytes */
    char buf[MAX_MSG_SIZE];     /* message buffer */
} MSG_S_T;


/*  define message queue structure type
 */
typedef struct msgq_s_t
{
    int count;                  /* number of messages */
    MSG_S_T msg[MAX_MSG_COUNT]; /* array of messages */
} MSGQ_S_T;


/*  define task structure type
 */
typedef struct task_s_t
{
    int taskid;                 /* task id */
    SHORT_BUFFER_T taskname;    /* task name */
    int (*proc) (void *);       /* pointer to task function */
    void *args;                 /* pointer to task arguments */
    MEMBLOCK_S_T mem;           /* memory block */
    MSGQ_S_T queue;             /* message queue */
    BOOLEAN_T valid;
    BOOLEAN_T ready;
    BOOLEAN_T blocked;
    BOOLEAN_T suspend;
} TASK_S_T;


/*  define main database structure 
 */
typedef struct context_s_t
{
    int numtasks;               /* number of tasks */
    TASK_S_T tasklist[MAX_TASKS];       /* array of tasks */
    int ticks;                  /* count of ticks */
    int ticktime;               /* time per tick (in ms) */
    int errorcode;              /* current error code */
    int maxtasks;               /* max number of tasks */
    int maxtaskmem;             /* max size of task memory block */
    int maxmsgcount;            /* max message count in queue */
    int maxmsgsize;             /* max message size per msg */
    BOOLEAN_T verbose;          /* verbose output state */
} CONTEXT_S_T;



/*  declare prototypes for PUBLIC functions
 */
extern int mosInitTasking(void);
extern void mosFreeTasking(void);

extern void mosSetVerboseState(BOOLEAN_T state);

extern void mosGetVersion(char *version);
extern void mosGetPlatform(char *platform);

extern int mosGetErrorCode(void);
extern void mosDisplayErrorCode(int code);

extern int mosCreateTask(char *name, void *proc, void *args, int size);
extern void mosDeleteTask(int taskid);

extern void mosSuspendTask(int taskid);
extern void mosResumeTask(int taskid);

extern void mosBlockTask(int taskid);
extern void mosUnBlockTask(int taskid);

extern int mosGetTaskId(char *name);

extern int mosIsTaskValid(int taskid);
extern int mosIsTaskSuspended(int taskid);
extern int mosIsTaskBlocked(int taskid);

extern char *mosGetTaskMemPtr(int taskid);
extern int mosGetTaskMemSize(int taskid);

extern void mosSequenceTaskListOnce(void);
extern void mosSequenceTasks(void);

extern void mosDisplayTaskList(void);

extern void mosClearMessageQueue(int taskid);
extern int mosCheckMessageQueue(int taskid);
extern int mosReadMessage(int taskid, int index, char *buf);
extern int mosSendMessage(int desttaskid, char *buf, int size);
extern int mosSendBroadcast(char *buf, int size);


/* PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  PRIVATE  */

/*  declare prototypes for PRIVATE functions
 */
extern void idle(void *args);

#endif /* _MOS_H */
