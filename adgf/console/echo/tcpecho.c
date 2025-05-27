/********************************************************
*
* ECHO client program example
*
* File:   tcpecho.c 	- TCPecho, main
*
* Rev 4   4/04/96  added cli prompts for client and server text
* Rev 3   1/30/96  separated from tcplib.h
* Rev 0   3/06/94  Originated
*
* Author: Brian Lingard
*
* Usage:  tcpecho <host> <port>
*
*	where host = name of machine (ex. tif686)
*	      port = numeric name of echo service (ex. 50001)
*
* Unix Compile string:	cc tcpecho.c -O -o tcpecho -lsocket -lnsl
*
* Notes:  While ECHO client is connected to ECHO service
*	  all text entered at command line and terminated
*	  by a <CR> will be sent to ECHO service and returned 
*	  unchanged.  You will have to <CTRL-C> to exit.
*
*********************************************************/

/* this program accesses the TCP service ECHO on a remote host */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN      128

#include "tcplib.h"           /* not just header stuff */


/* declare echo prompts */
char echo_cl_pmpt[] = "\nEcho client: ";
char echo_sv_pmpt[] = "Echo server: ";



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



/* TCPecho */
int
TCPecho( host, port)
   char *host;
   char *port;
{
   char  buf[LINELEN+1];      /* buffer for one line of text */
   int   s, n;                /* socket, read count */
   int   outchars, inchars;   /* characters sent and received */
   
   s = connectTCP(host, port);	/* connect to server machine */
   
   fputs(echo_cl_pmpt, stdout);

   while (fgets(buf, sizeof(buf), stdin)) {
      buf[LINELEN] = '\0';    /* insure line null-terminated */
      outchars = strlen(buf);
      (void) write(s, buf, outchars);
      
      /* read it back */
      for (inchars = 0; inchars < outchars; inchars+=n ) {
         n = read(s, &buf[inchars], outchars - inchars);
         if (n < 0)
            errexit("socket read failed: %s\n", sys_errlist[errno]);
      }

      fputs(echo_sv_pmpt, stdout);

      fputs(buf, stdout);

      fputs(echo_cl_pmpt, stdout);
   }
   if (shutdown(s, 2) == -1)     /* shutdown connection */
      errexit("shutdown failed: %s\n", sys_errlist[errno]);
   if (close(s) == -1)           /* close connection to server machine */
      errexit("close failed: %s\n", sys_errlist[errno]);
}


/* main - TCP client for ECHO service */
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
      default:
         fprintf(stderr, "usage: tcpecho <host> <port>\n");
         exit(1);
   }
   TCPecho( host, port);
   exit(0);
}
      
     
