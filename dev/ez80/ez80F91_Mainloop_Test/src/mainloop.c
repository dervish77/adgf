/*****************************************************************************
 *
 *	Main Loop Demo main program.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *	Usage:	mainloop [-h]
 *
 *****************************************************************************/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
extern DATABASE_S_T *data;


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
mainloop(void)
{
   DATABASE_S_T		mdata;


   printf("\nMain Loop Demo - version %d.%d\n", VERSION_MAJOR, VERSION_MINOR);


   printf("--initializing demo...\n");
   DemoInit(&mdata);
   data = &mdata;

#if 0
   /*  parse command line args
    */
   switch (argc)
   {
      case 1:
            printf("--running demo...\n");
            DemoRun(&mdata);
         break;

      case 2:
         if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'i') )
         {
            printf("--starting up interactive demo...\n");
            DemoInteractive(&mdata);
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'h') )
         {
            DemoHelp();
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
#endif

#if 0
   printf("--running demo...\n");
   DemoRun(&mdata);
   DemoRun(&mdata);
   DemoRun(&mdata);
#endif

#if 1
   printf("--starting up interactive demo...\n");
   DemoInteractive(&mdata);
#endif

   printf("--closing demo...\n");
   DemoClose(&mdata);

//   exit(0);
}


/*  ParseString	- general purpose string parser
 *
 *  Parameters:
 *	string	- pointer to string to be parsed
 *	args	- pointer to parsed array of strings
 *
 *  Returns:
 *	count	- count of substrings in array
 */
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;
//   printf("Parsing %s\n", argstart);

   for (; *string != '\0'; string++) {
      c = *string;
//	  printf("%02x %c\n", c, c);
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
//         printf("Parsing %s arglen %d\n", argstart, arglen);
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */


/* end of main.c */
