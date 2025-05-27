/********************************************************
*
* ECHO server program example
*
* File:   tcpechod.c 	- TCPechod, main
*
* Rev 3   1/30/96  separated from tcplib.h
* Rev 0   3/6/94   Originated
*
* Author: Brian Lingard
*
* Usage:  tcpechod <port>
*
*	where port = numeric name of echo service (ex. 50001)
*
* Unix Compile string:	cc tcpechod.c -O -o tcpechod -lsocket -lnsl
*
* Notes:  While ECHO server is running, all incoming text 
*	  messages from an ECHO client will be simply sent
*	  back to the ECHO client unchanged.
*
*********************************************************/


#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "tcplib.h"           /* not just header stuff */

#define QLEN         5        /* maximum connection queue length */
#define BUFSIZE      4096

int reaper();




/* errexit - print an error message and exit */

#include <varargs.h>

static int
errexit( format, va_alist)
char *format;
va_dcl
{
   va_list args;
   va_start(args);
   _doprnt(format, args, stderr);
   va_end(args);
   exit(1);
}



/* main - concurrent TCP server for ECHO service */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char     *port;               /* service name or port number */
   struct   sockaddr_in fsin;    /* the address of a client */
   int      alen;                /* length of client's address */
   int      msock;               /* master server socket */
   int      ssock;               /* slave server socket */
   
   switch (argc) {
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: TCPechod <port>\n");
         exit(1);
   }
   
   msock = passiveTCP(port, QLEN);
   
   (void) signal(SIGCHLD, reaper);
   
   while (1) {
      alen = sizeof(fsin);
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0) {
         if (errno == EINTR)
            continue;
         errexit("accept: %s\n", sys_errlist[errno]);
      }
      switch(fork()) {
         case 0:     /* child */
            (void) close(msock);
            exit(TCPechod(ssock));
         default:    /* parent */
            (void) close(ssock);
            break;
         case -1:
            errexit("fork: %s\n", sys_errlist[errno]);
      }
   }
}


/* TCPechod - echo data until end of file */
int
TCPechod(fd)
   int fd;
{
   char  buf[BUFSIZE];
   int   cc;
   
   while (cc = read(fd, buf, sizeof buf)) {
      if (cc < 0)
         errexit("echo read: %s\n", sys_errlist[errno]);
      if (write(fd, buf, cc) < 0)
         errexit("echo write: %s\n", sys_errlist[errno]);
   }
   return 0;
}


/* reaper - clean up zombie children */
int
reaper()
{
/*
   union wait  status;
   
   while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0) 
   {
 
   }
*/
}
