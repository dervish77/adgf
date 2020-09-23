/********************************************************
*
* MSG server program example - using Pthreads
*
* File:   thmsgd.c 	- TCPmsgd, main
*
* Rev 0.0  10/20/97   Originated
*
* Author: Brian Lingard
*
* Usage:  thmsgd <port>
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

#include <pthread.h>

#include <errno.h>

#include "tcplib.h" 	/* tcp library specific stuff */
#include "msg.h"	/* msg client/server stuff */



/*
#define TCPMSGD_DEBUG
*/


#define TCPMSGD_ECHO



typedef struct th_msg_t {
   int		active;		/* boolean flag */
   pthread_t	th;		/* thread id */
   int		ssock;		/* slave socket file descriptor */
   int		count;		/* thread count */
   int  	status;		/* return value */
} TH_MSG_T;

#define TH_DONE		0
#define TH_RUN		1
#define TH_ERROR	2

#define MAX_THREADS	16


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
void
TCPmsgd(TH_MSG_T *th_msg)
{
   char  rbuf[BUFSIZE];
   char  wbuf[BUFSIZE];
   char  string[128];
   int   cc;
   int   fd;
 

   printf("thmsgd: msg_thread %d active\n", th_msg->count);

   fd = th_msg->ssock;

   while (cc = read(fd, rbuf, sizeof rbuf)) 
   {
      if (cc < 0)
      {
         sprintf(string, "thmsgd read: %s\n", strerror(errno));
         fprintf(stderr, "%s", string);
         th_msg->status = TH_ERROR;
         break;
      }

#ifdef TCPMSGD_ECHO
      cc = sizeof(MESSAGE_U_T);
      memcpy(wbuf, rbuf, cc);
#else
      cc = sizeof(MESSAGE_U_T);
      HandleMsg(rbuf, wbuf, cc);
#endif

      if (write(fd, wbuf, cc) < 0)
      {
         sprintf(string, "thmsgd write: %s\n", strerror(errno));
         fprintf(stderr, "%s", string);
         th_msg->status = TH_ERROR;
         break;
      }
   }

   printf("thmsgd: msg_thread %d inactive\n", th_msg->count);

   th_msg->status = TH_DONE;  
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

   TH_MSG_T	th_msg_array[MAX_THREADS];
   int		i;

   
   switch (argc) {
      case 1:
         port = MSG_PORT;
         break;
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: thmsgd [<port>]\n");
         exit(1);
   }
      
   msock = passiveTCP(port, QLEN);
       
   for (i = 0; i < MAX_THREADS; i++)
   {
      th_msg_array[i].active = 0;
      th_msg_array[i].count = i;
   }

   printf("\n\nMulti-threaded TCP MSG Server %s is now running.\n\n", 
		MSG_VERSION);

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

      for (i = 0; i < MAX_THREADS; i++)
      {
         if (th_msg_array[i].active == 0)
         {
            th_msg_array[i].active = 1;
            th_msg_array[i].ssock = ssock;
            th_msg_array[i].status = TH_RUN;

            pthread_create(&th_msg_array[i].th, 
                           NULL,
                           (void *) TCPmsgd,
                           (void *) &th_msg_array[i]);

            break;
         }
      }

      if (i == MAX_THREADS)
      {
         fprintf(stderr, "thmsgd: couldn't start new thread\n");
      }
 
      for (i = 0; i < MAX_THREADS; i++)
      {      
         if (th_msg_array[i].status == TH_DONE)
         {
            th_msg_array[i].active = 0;
            pthread_join(th_msg_array[i].th, NULL);
         }
         else
         {
            if (th_msg_array[i].status == TH_ERROR) 
            {
               fprintf(stderr, "thmsgd: thread %d found error\n",
			th_msg_array[i].count);
               exit(1);
            }
         }
      }

   } /* end while (1) */
} /* end main */



/* end of msgd.c */


