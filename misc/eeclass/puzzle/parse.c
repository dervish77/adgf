/* parse.c - command string parsing test program */

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define START 0
#define SEND  1
#define SOLVE 2
#define DONE  3
#define STOP  4
#define BTIME 5
#define STIME 6
#define DTIME 7
#define ABORT 8

#define BUFLEN 128


/* parsestring - parses list of strings into array of strings */
int 
parsestring(string, args)
   char *string;
   char *args[];
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
}


/* ParseCmdBuf - parse command buffer string received, return cmd code */
int
ParseCmdBuf(buf, faces, timeval)
   char *buf;
   int  faces[];
   long *timeval;
{
   char *argarray[7];
   int i, cmdcode;

/* translate command string to command code */
   cmdcode = 99;

   if (strncmp(buf, "strt", 4) == 0)
      cmdcode = START;
   if (strncmp(buf, "send", 4) == 0)
      cmdcode = SEND;
   if (strncmp(buf, "solv", 4) == 0)
      cmdcode = SOLVE;
   if (strncmp(buf, "done", 4) == 0)
      cmdcode = DONE;
   if (strncmp(buf, "stop", 4) == 0)
      cmdcode = STOP;
   if (strncmp(buf, "btim", 4) == 0)
      cmdcode = BTIME;
   if (strncmp(buf, "stim", 4) == 0)
      cmdcode = STIME;
   if (strncmp(buf, "dtim", 4) == 0)
      cmdcode = DTIME;
   if (strncmp(buf, "abrt", 4) == 0)
      cmdcode = ABORT;

/* further parse command string if necessary */
   switch(cmdcode) {
      case SEND:
         parsestring(buf, argarray);
         for (i=1; i<7; i++)
             faces[i-1] = atoi(argarray[i]);
         break;
      case BTIME:
      case STIME:
      case DTIME:
         parsestring(buf, argarray);
         *timeval = atol(argarray[1]);
         break;
      default:
         break;		/* no further parsing necessary */
   }

   return(cmdcode);
}


/* main */
int
main(argc, argv)
   int argc;
   char *argv[];
{
   char buffer[BUFLEN];
   char *buf;
   char *elementstr = "";
   char *timestr = "";
   char *space = " ";
   
   int faces[6];
   unsigned short elements[6];
   long timeval, timeparsed;
   int command;
   int i;

   if (argc != 2) {
      printf("usage: %s cmdstring\n", argv[0]);
      exit(1);
   }

   elements[0] = 10;
   elements[1] = ~10;
   elements[2] = 30;
   elements[3] = ~30;
   elements[4] = 50;
   elements[5] = ~50;

   buf = strcpy(buffer, argv[1]);

   if (strcmp(argv[1], "send") == 0) {
      buf = strcat(buf, space);
      for (i=0; i<6; i++) {
         sprintf(elementstr, "%u ", elements[i]);
         buf = strcat(buf, elementstr);
      }
   }

   time(&timeval);
   sprintf(timestr, " %u ", timeval);

   if (strcmp(argv[1], "btim") == 0) {
      buf = strcat(buf, timestr);
   }
   if (strcmp(argv[1], "stim") == 0) {
      buf = strcat(buf, timestr);
   }
   if (strcmp(argv[1], "dtim") == 0) {
      buf = strcat(buf, timestr);
   }

   printf("command string = %s\n", buf);

   command = ParseCmdBuf(buf, faces, &timeparsed);

   printf("command code returned = %d\n", command);

   switch(command) {
      case START:
      case SOLVE:
      case DONE:
      case STOP:
      case ABORT:
         printf("parsed cmd: %d with no args\n", command);
         break;
      case SEND:
         printf("parsed cmd: %d with ", command);
         for (i=0; i<6; i++)
            printf("%d ", faces[i]);
         printf("\n");
         break;
      case BTIME:
      case STIME:
      case DTIME:
         printf("parsed cmd: %d with %d aka %s", command, 
                                   timeparsed, ctime(&timeparsed));
         break;
      default:
         printf("unknown command\n");
         break;
   }
   exit(0);
}
