/*****************************************************************************
 *
 *	MOS Demo program header file.
 *
 *	File:	demo.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/

#ifndef _DEMO_H
#define _DEMO_H


#define VERSION_MAJOR	0
#define VERSION_MINOR	9


/*  define prompt and buffer type
 */
#define PROMPT			"mos>"	

#define MAX_CMD_ARGS		21


/*  define main database structure 
 */
typedef struct database_s_t {
   int		temp1;
   int		temp2;
} DATABASE_S_T;   


/*  declare prototypes for all functions
 */
extern void DemoInit( DATABASE_S_T *mdata );
extern void DemoClose( DATABASE_S_T *mdata );
extern void DemoInteractive( DATABASE_S_T *mdata );
extern void DemoRun( DATABASE_S_T *mdata );
extern void DemoVersion( void );
extern void DemoHelp( void );

extern void ErrorUsage( void );

extern int ParseString(char *string, char *args[]);

#endif 	/* _DEMO_H */
