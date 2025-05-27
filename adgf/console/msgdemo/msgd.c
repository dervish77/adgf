/********************************************************
*
* MSG server program example
*
* File:   msgd.c 	- TCPmsgd, main
*
* Rev 0.0  09/24/97   Originated
*
* Author: Brian Lingard
*
* Usage:  msgd <port>
*
*	where port = numeric name of msgd service (ex. 50001)
*
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>

#include "tcplib.h" 	/* tcp library specific stuff */
#include "msg.h"	/* msg client/server stuff */



/*
#define TCPMSGD_DEBUG
*/



int reaper();


/* errexit - print an error message and exit */

#include <stdarg.h>

static int
errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}



/* 
 *  TCPmsgd - MSG server 
 */
int
TCPmsgd(int fd)
{
   char  rbuf[BUFSIZE];
   char  wbuf[BUFSIZE];
   int   cc;

#ifdef TCPMSGD_DEBUG
   MESSAGE_U_T *msgptr;
#endif    

   /*  main loop
    */
   while (cc = read(fd, rbuf, sizeof rbuf)) 
   {
      if (cc < 0)
      {
         errexit("msgd read: %s\n", strerror(errno));
      }

#ifdef TCPMSGD_DEBUG
      msgptr = (MESSAGE_U_T *)&rbuf[0];
      DisplayMsg( msgptr, "from client:" );
#endif

      cc = sizeof(MESSAGE_U_T);
      memcpy(wbuf, rbuf, cc);

#ifdef TCPMSGD_DEBUG
      msgptr = (MESSAGE_U_T *)&wbuf[0];
      DisplayMsg( msgptr, "to client:" );
#endif

      if (write(fd, wbuf, cc) < 0)
      {
         errexit("msgd write: %s\n", strerror(errno));
      }
   }
   return 0;
}



/*  
 *  main - concurrent TCP server for MSG service 
 *
 */
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
      case 1:
         port = MSG_PORT;
         break;
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: msgd [<port>]\n");
         exit(1);
   }
   
   msock = passiveTCP(port, QLEN);
   
   (void) signal(SIGCHLD, reaper);
         
   printf("\n\nTCP MSG Server %s is now running.\n\n", MSG_VERSION);

   while (1) 
   {
      alen = sizeof(fsin);
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0) 
      {
         if (errno == EINTR)
            continue;
         errexit("accept: %s\n", strerror(errno));
      }

      switch(fork()) 
      {
         case 0:     /* child */
            (void) close(msock);
            exit(TCPmsgd(ssock));
         default:    /* parent */
            (void) close(ssock);
            break;
         case -1:
            errexit("fork: %s\n", strerror(errno));
      }
   }
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

/* end of msgd.c */


