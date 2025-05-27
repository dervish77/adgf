/********************************************************
*
* MSG client program example
*
* File:   msg.c 	- TCPmsg, main
*
* Rev 0.0  09/24/97  Originated
*
* Author: Brian Lingard
*
* Usage:  msg <host> [<port>]
*
*	where host = name of machine (ex. tif686)
*	      port = numeric name of msgd service (def. 50000)
*
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>

#include "tcplib.h" 	/* tcp library specific stuff */
#include "msg.h"	/* msg client/server stuff */


/* declare prompts */
char echo_cl_pmpt[] = "\nMsg id: ";



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
 *  TCPmsg -- main MSG client loop
 */
int
TCPmsg( host, port)
   char *host;
   char *port;
{
   char  buf[LINELEN+1];      /* buffer for one line of text */
   int   s, n;                /* socket, read count */
   int   outchars, inchars;   /* characters sent and received */
   MESSAGE_U_T	send_msg;     /* send message union */
   MESSAGE_U_T	recv_msg;     /* receive message union */
   int		int_id;       /* temp var */
   MSG_ID_T	id;           /* message id */
   

   /*  connect to server machine 
    */
   s = connectTCP(host, port);	
   
   /*  loop on sending messages to server 
    */
   fputs(echo_cl_pmpt, stdout);

   while (fgets(buf, sizeof(buf), stdin)) 
   {
      int_id = atoi(buf);
      id = (MSG_ID_T) int_id;

      if (id == 99)
      {
         printf("closing connection\n");
         break;
      }

      MakeMsg( &send_msg, host, port, id);
      DisplayMsg( &send_msg, "to server:" );
      WriteMsg( s, &send_msg );

      ReadMsg( s, &recv_msg );
      DisplayMsg( &recv_msg, "from server:" );

      fputs(echo_cl_pmpt, stdout);
   }

   /*  close connection to server
    */
   closeTCP( s );

   printf("connection to %s closed\n", host);
}


/* main - TCP client for MSG service */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char  *host;    		/* host of service */
   char  *port;       		/* service port */
   
   switch (argc) {
      case 3:
         host = argv[1];
         port = argv[2];
         break;
      case 2:
         host = argv[1];
         port = MSG_PORT;	/* use default port */
         break;
      default:
         fprintf(stderr, "usage: msg <host> [<port>]\n");
         exit(1);
   }

   printf("\nTCP MSG client version %s\n", MSG_VERSION);
   printf("\n(enter 99 to exit)\n");

   TCPmsg( host, port);

   exit(0);
}
      
/* end of msg.c */
     
