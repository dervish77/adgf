/*****************************************************************************
 *
 *	MOS cli test main program.
 *
 *	File:	mosapp.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *	Usage:	
 *              mosapp           loop forever 
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mos.h"

#include "apptasks.h"


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
   int	taskid;
   char version[10];
   char platform[10];

   mosPrint("Cli Test App\n");

   mosInitTasking();
   mosGetVersion( version );
   mosGetPlatform( platform );
   mosSetVerboseState( FALSE );

   mosPrint("MOS %s on %s\n", version, platform);

   taskid = mosCreateTask( "getid", &getid, &dummyargs, 256 );
   taskid = mosCreateTask( "cmdtask", &cmdtask, &dummyargs, 32 );
   taskid = mosCreateTask( "kbdtask", &kbdtask, &dummyargs, 32 );

   // execute the tasks until user says 'done'      
   mosSequenceTasks();

   mosFreeTasking();

   mosPrint("done.\n");
   exit(0);
}


/* end of appmain.c */
