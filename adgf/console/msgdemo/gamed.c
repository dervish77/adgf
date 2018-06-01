/********************************************************
*
* Game server program example - using Pthreads
*
* File:   gamed.c 	- TCPmsgd, main
*
* Rev 0.0  10/21/97   Originated
*
* Author: Brian Lingard
*
* Usage:  gamed <port>
*
*	where port = numeric name of gamed service (ex. 50001)
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
#define TCPGAMED_DEBUG
*/

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


/* 
 * GLOBALS
 */
int die_game_engine = 0;
int die_broadcast = 0;




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
 *  GameEngine - main GAME engine 
 */
void
GameEngine(int *gameflag)
{
   int i;

   printf("gamed: game_engine_thread active\n");

   while (*gameflag)
   {
      if (die_game_engine)
         break;
   }

   printf("gamed: game_engine_thread inactive\n");
}



/* 
 *  Broadcast - Broadcast msgs to all clients 
 */
void
Broadcast(int *bcflag)
{
   int i;

   printf("gamed: broadcast_thread active\n");

   while (*bcflag)
   {
      if (die_broadcast)
         break;
   }

   printf("gamed: broadcast_thread inactive\n");
}



/* 
 *  TCPgamed - GAME server 
 */
void
TCPgamed(TH_MSG_T *th_msg)
{
   char  rbuf[BUFSIZE];
   char  wbuf[BUFSIZE];
   char  string[128];
   int   cc;
   int   fd;
 

   printf("gamed: msg_thread %d active\n", th_msg->count);

   fd = th_msg->ssock;

   while (cc = read(fd, rbuf, sizeof rbuf)) 
   {
      if (cc < 0)
      {
         sprintf(string, "gamed read: %s\n", strerror(errno));
         fprintf(stderr, "%s", string);
         th_msg->status = TH_ERROR;
         break;
      }

      cc = sizeof(MESSAGE_U_T);
      memcpy(wbuf, rbuf, cc);

      if (write(fd, wbuf, cc) < 0)
      {
         sprintf(string, "gamed write: %s\n", strerror(errno));
         fprintf(stderr, "%s", string);
         th_msg->status = TH_ERROR;
         break;
      }
   }

   printf("gamed: msg_thread %d inactive\n", th_msg->count);

   th_msg->status = TH_DONE;  
}



/*  
 *  main - concurrent TCP server for GAME service 
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

   pthread_t	game_thread, broadcast_thread;
   int		game_flag = 1, broadcast_flag = 1;
   int		rtn;

   
   switch (argc) {
      case 1:
         port = MSG_PORT;
         break;
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: gamed [<port>]\n");
         exit(1);
   }

   printf("\n\nMulti-threaded TCP GAME Server %s is now running.\n\n", 
		MSG_VERSION);

   msock = passiveTCP(port, QLEN);
       
   for (i = 0; i < MAX_THREADS; i++)
   {
      th_msg_array[i].active = 0;
      th_msg_array[i].count = i;
   }


   rtn = pthread_create(&game_thread, 
                           NULL,
                           (void *) GameEngine,
                           (void *) &game_flag);
   if (rtn)
   {
      fprintf(stderr, "Error: phread_create ");
      if (rtn == EAGAIN)
         fprintf(stderr, "Insufficent resources\n");
      else if (rtn == EINVAL)
         fprintf(stderr, "Invalid arguments\n");
      else
         fprintf(stderr, "Failed\n");
      exit(1);
   }
 
   rtn = pthread_create(&broadcast_thread, 
                           NULL,
                           (void *) Broadcast,
                           (void *) &broadcast_flag);

   if (rtn)
   {
      fprintf(stderr, "Error: phread_create ");
      if (rtn == EAGAIN)
         fprintf(stderr, "Insufficent resources\n");
      else if (rtn == EINVAL)
         fprintf(stderr, "Invalid arguments\n");
      else
         fprintf(stderr, "Failed\n");
      exit(1);
   }


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
                           (void *) TCPgamed,
                           (void *) &th_msg_array[i]);

            break;
         }
      }

      if (i == MAX_THREADS)
      {
         fprintf(stderr, "gamed: couldn't start new thread\n");
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
               fprintf(stderr, "gamed: thread %d found error\n",
			th_msg_array[i].count);
               exit(1);
            }
         }
      }

   } /* end while (1) */
} /* end main */



/* end of gamed.c */


