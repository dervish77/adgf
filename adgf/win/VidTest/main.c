/*****************************************************************************
 *
 *	VidTest main program.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *	Date:	10/21/2003
 *
 *
 *****************************************************************************/
/*****************************************************************************
 *
 *	Usage:	vidtest [-a|-d|-f|-g|-h|-i|-l|-m|-p|-s|-t|-v|-x|-z]
 *
 *		-g <pattern>		display graphics pattern
 *		-j <1|0>		enables/disables video pass-through
 *		-k <scalew> <scaleh>	sets scaling for video pass-through
 *		-h			display help
 *		-v			display version
 *
 * other options:
 *		-a		run all tests in default mode
 *		-d		display list of tests in default mode
 *		-f <s> <e>	flash dump
 *		-h		display help
 *		-i		display info/status
 *		-l <c> #	loop on test number <c> times
 *		-m <s> <e>	memory dump
 *		-p <select>	probe registers <all,ata,cpu,eth,pci,usb>
 *		-s <select>	scan devices <pci,usb>
 *		-t #		execute test number
 *		-v		display version
 *              -x <script>	load and run script file 
 *		-z		reset cpu
 *
 *           <pattern>
 *               0       Edwin's anim demo
 *               1       line boxes
 *               2       color gradient
 *               3       multi shading
 *               4       color bars
 *               5       circles
 *               6       horizontal lines
 *               7       vertical lines
 *               8       blit boxes
 *               9       gradient
 *               77      fast loop on patterns
 *               88      slow loop on patterns
 *               99      clear screen
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "config.h"
#include "video.h"
#include "mon.h"


#define DEBUG



/*
 *  GLOBALS
 */
DATABASE_S_T *data;

extern void Usage( FILE *fp, char *program );



/*
 *  STATICS
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
int 
main(int argc, char **argv)
{
   DATABASE_S_T		mondata;
   unsigned long	start, end;
   int			count;
   MON_LONG_BUFFER_T	cmd, cmdstring;	
   char 		*buffer;
   char			*cmdargs[MAX_CMD_ARGS];
   int			i, argcount;


   MonDisplayVersion();

   MonInit(&mondata);
   data = &mondata;


   /*  parse command line args
    */
   switch (argc)
   {
      case 1:
         MonInteractive(&mondata, TRUE, 0 );
         break;

      case 2:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'a') )
         {
            MonRun(&mondata);
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'd') )
         {
            MonList(&mondata);
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'f') )
         {
            MonDumpFlash( 0xff000000, 0xff000200 );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'h') )
         {
            Usage(stdout, argv[0]);
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'i') )
         {
            MonDisplayInfo();
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'm') )
         {
            MonDumpMemory( 0x0, 0x200 );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'v') )
         {
            printf("\n");
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'z') )
         {
            MonSoftReset();
         }
         else
         {
            Usage(stderr, argv[0]);
         }
         break;

      case 3:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'g') )
         {
            count = atoi( argv[2] );
            MonVideo( count );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'j') )
         {
            count = atoi( argv[2] );
            MonVidPass( count );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'p') )
         {
            if ( strcmp( argv[2], "all" ) == 0 )
            {
               MonCpuProbe();
               MonAtaProbe();
               MonEthProbe();
               MonPciProbe();
               MonUsbProbe();
            }
            else if ( strcmp( argv[2], "ata" ) == 0 )
            {
               MonAtaProbe();
            }
            else if ( strcmp( argv[2], "cpu" ) == 0 )
            {
               MonCpuProbe();
            }
            else if ( strcmp( argv[2], "eth" ) == 0 )
            {
               MonEthProbe();
            }
            else if ( strcmp( argv[2], "pci" ) == 0 )
            {
               MonPciProbe();
            }
            else if ( strcmp( argv[2], "usb" ) == 0 )
            {
               MonUsbProbe();
            }
            else 
            {
               Usage(stderr, argv[0]);
            }
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 's') )
         {
            if ( strcmp( argv[2], "pci" ) == 0 )
            {
               MonPciScan();
            }
            else if ( strcmp( argv[2], "usb" ) == 0 )
            {
               MonUsbScan();
            }
            else 
            {
               Usage(stderr, argv[0]);
            }
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 't') )
         {
            sprintf( cmd, "test %s\n", argv[2] );
            strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
            buffer = &cmdstring[0];
            cmdstring[MON_LONG_BUFF_LEN - 1] = '\0';
            argcount = MonParseString( buffer, cmdargs );

            MonConfig(&mondata);
            MonTestExecute( argcount, cmdargs );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'x') )
         {
            sprintf( cmd, "%s", argv[2] );
            strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
            MonInteractive(&mondata, FALSE, cmdstring );
         }
         else
         {
            Usage(stderr, argv[0]);
         }
         break;
         
      case 4:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'f') )
         {
            start = strtoul( argv[2], NULL, 16 );
            end = strtoul( argv[3], NULL, 16 );
            MonDumpFlash( start, end );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'k') )
         {
            start = atoi( argv[2] );
            end = atoi( argv[3] );
            MonVidScale( start, end );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'l') )
         {
            count = atoi( argv[2] );
            sprintf( cmd, "loop %s\n", argv[3] );
            strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
            buffer = &cmdstring[0];
            cmdstring[MON_LONG_BUFF_LEN - 1] = '\0';
            argcount = MonParseString( buffer, cmdargs );

            MonConfig(&mondata);
            MonTestLoop( argcount, cmdargs, count );
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'm') )
         {
            start = strtoul( argv[2], NULL, 16 );
            end = strtoul( argv[3], NULL, 16 );
            MonDumpMemory( start, end );
         }
         else
         {
            Usage(stderr, argv[0]);
         }
         break;

      case 5:
      case 6:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'l') )
         {
            count = atoi( argv[2] );

            sprintf( cmd, "loop" );
            for (i=3; i<argc; i++)
            {
               sprintf( cmd, " %s", argv[i] );
            }
            sprintf( cmd, "\n" );

            strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
            buffer = &cmdstring[0];
            cmdstring[MON_LONG_BUFF_LEN - 1] = '\0';
            argcount = MonParseString( buffer, cmdargs );

            MonConfig(&mondata);
            MonTestLoop( argcount, cmdargs, count );
         }
         else
         {
            Usage(stderr, argv[0]);
         }
         break;

      default:
         Usage(stderr, argv[0]);
         break;
   }

   MonClose(&mondata);

   exit(0);
}


/* end of main.c */
