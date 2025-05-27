/********************************************************
*
* Example of using pipes between a parent and child process.
*
* File:   pipe_exam.c
*
* Rev 0   3/6/94   Originated
*
* Author: Brian Lingard
*
* Usage:  pipe_example
*
* Unix Compile string:	cc pipe_exam.c -O -o pipe_exam
*
*********************************************************/

#include <stdio.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

main()
{
   char inbuf[MSGSIZE];
   int p[2], j, pid;
  
/* open pipe */
   if (pipe(p) < 0) {
      perror("pipe call");
      exit(1);
   }

   switch(pid = fork()) {
      case -1: /* couldn't fork */
         perror("fork failed");
         exit(1);
      case 0: /* child process */
         close(p[1]);	/* close write side of the pipe */
         for (j = 0; j < 3; j++) {
            read(p[0], inbuf, MSGSIZE);
            printf("%s\n", inbuf);
         }
         exit(0);
      default: /* parent process */
         close(p[0]);	/* close read side of the pipe */
         write(p[1], msg1, MSGSIZE);
         write(p[1], msg2, MSGSIZE);
         write(p[1], msg3, MSGSIZE);
         wait((int *)0);
         exit(0);
   }
}
