/*****************************************************************************
 *
 *	MOS Demo main program.
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
 *	Usage:	mosdemo [-d | -h | -i | -l] 
 *
 * 		-d 	- show interactive command help
 *		-h	- show command line usage help
 *		-i	- enter interactive mode
 *		-l	- show task list
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mos.h"

#include "demo.h"


#define DEBUG



/*
 *  GLOBALS
 */
DATABASE_S_T *data;


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
int main(int argc, char **argv)
{
   DATABASE_S_T		mdata;


   printf("MOS Demo - version %d.%d\n", VERSION_MAJOR, VERSION_MINOR);


   printf("--initializing demo...\n");
   DemoInit(&mdata);
   data = &mdata;


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
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'd') )
         {
            DemoHelp();
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'l') )
         {
            mosDisplayTaskList();
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'h') )
         {
            ErrorUsage();
         }
         else if ( (argv[1][0] EQ '-') AND (argv[1][1] EQ 'v') )
         {
            DemoVersion();
         }
         else
         {
            ErrorUsage();
            exit(0);
         }
         break;

      default:
         ErrorUsage();
         exit(0);
         break;
   }

   printf("--closing demo...\n");
   DemoClose(&mdata);

   printf("done.\n");

   exit(0);
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

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */


/* end of main.c */
