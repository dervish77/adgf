/*****************************************************************************
 *
 *	Main Loop program header file.
 *
 *	File:	mloop.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/

#ifndef _MLOOP_H
#define _MLOOP_H


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

typedef int 		BOOLEAN_T;
typedef unsigned char 	UBYTE_T;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef unsigned long int	UINT32;
typedef long int		INT32;
typedef unsigned short int	UINT16;
typedef short int		INT16;
typedef unsigned char		UINT8;
typedef char			INT8;


/*  define buffer type
 */
#define SHORT_BUFF_LEN	40
#define LONG_BUFF_LEN	120

typedef char SHORT_BUFFER_T[SHORT_BUFF_LEN];
typedef char LONG_BUFFER_T[LONG_BUFF_LEN]; 


/*  define file name string type
 */
#define FILE_NAME_LEN		30
typedef char FILENAME_T[FILE_NAME_LEN];   


/*  define task related types
 */
#define MAX_TASKS		10
#define MAX_TASK_SIZE		1024

#define MAX_MSG_COUNT		4
#define MAX_MSG_SIZE		32

#define DEFAULT_TICK_TIME	10


/*  define argument structure type
 */
typedef struct arg_struct {
   int			arg1;
   int			arg2;
   int			arg3;
} ARG_STRUCT;


/*  define memory block structure type
 */
typedef struct memblock_s_t {
   int			size;		/* size in bytes */
   char			*ptr;		/* pointer to start of block */
} MEMBLOCK_S_T;


/*  define message structure type
 */
typedef struct msg_s_t {
   int			size;			/* size of message in bytes */
   char			buf[MAX_MSG_SIZE];	/* message buffer */
} MSG_S_T;


/*  define message queue structure type
 */
typedef struct msgq_s_t {
   int			count;			/* number of messages */
   MSG_S_T		msg[MAX_MSG_COUNT];	/* array of messages */
} MSGQ_S_T;


/*  define task structure type
 */
typedef struct task_s_t {
   int				taskid;		/* task id */
   SHORT_BUFFER_T	taskname;	/* task name */
   void	 			(* proc)(void *); /* pointer to task function */
   void				*args;		/* pointer to task arguments */
   MEMBLOCK_S_T		mem;		/* memory block */
   MSGQ_S_T			queue;		/* message queue */
   BOOLEAN_T		valid;
   BOOLEAN_T		ready;
   BOOLEAN_T		blocked;
   BOOLEAN_T		suspend;
} TASK_S_T;


/*  define main database structure 
 */
typedef struct context_s_t {
   int			numtasks;		/* number of tasks */
   TASK_S_T		tasklist[MAX_TASKS];	/* array of tasks */
   int			ticks;			/* count of ticks */
   int			ticktime;		/* time per tick */
} CONTEXT_S_T;   



/*  declare prototypes for all functions
 */
extern int  InitTasking( void );
extern void FreeTasking( void );

extern int  CreateTask( char *name, void *proc, void *args, int size );
extern void DeleteTask( int taskid );

extern void SuspendTask( int taskid );
extern void ResumeTask( int taskid );

extern void BlockTask( int taskid );
extern void UnBlockTask( int taskid );

extern void ExecuteTask( int taskid );

extern int  GetTaskId( char *name );
extern char *GetTaskMemPtr( int taskid );
extern int  GetTaskMemSize( int taskid );

extern void SequenceTaskList( void );

extern void DisplayTaskList( void );

extern void ClearMessageQueue( int taskid );
extern int  CheckMessageQueue( int taskid );
extern int  ReadMessage( int taskid, int index, char *buf );
extern int  SendMessage( int desttaskid, char *buf, int size );

#endif 	/* _MLOOP_H */
