/********************************************************
*
* test program which will be called via a 'rcmd'
*
* File:   test.c 
*
* Rev 0.0  02/02/96  Originated
*
* Author: Brian Lingard
*
* Usage:  test <arg_list>
*
*	where arg_list = list of arguments
*
* Notes:  Test simply accepts a list of arguments and then 
*	  prints them out to a log file.
*
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#define _USE_LOGFILE
*/

#define LINELEN		128
#define MAX_ARGS	9


static char *log_file_name = "test.log";


/*  main - test application 
 */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   int i;

   FILE *log_file;


#ifdef _USE_LOGFILE
   log_file = fopen(log_file_name, "w");
   if (log_file == (FILE *) NULL)
   {
      exit(1);
   }
#else
   log_file = stdout;
#endif

   if (argc > MAX_ARGS)
   {
      fprintf(log_file, "test: too many arguments, %d\n", argc);

#ifdef _USE_LOGFILE
      fclose(log_file);
#endif

      exit(1);
   }
   else if (argc > 1)
   {
      fprintf(log_file, "test: was called with args -");

      for (i = 0; i < argc; i++)
      {
         fprintf(log_file, " %s", argv[i]);
      }

      fprintf(log_file, "\n");
   }
   else
   {
      fprintf(log_file, "test: was called with no args\n");
   }

#ifdef _USE_LOGFILE
   fclose(log_file);
#endif

   exit(0);
}
      
     
