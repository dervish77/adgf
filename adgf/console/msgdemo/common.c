/********************************************************
*
* MSG client/server demo common functions
*
* File:   common.c 
*
* Rev 0.1  10/03/97  split from msg.c
* Rev 0.0  09/24/97  Originated
*
* Author: Brian Lingard
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



/* errexit - print an error message and exit */

#include <stdarg.h>

int
errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}

/*
 * MakeMsg()
 */
void
MakeMsg( MESSAGE_U_T *msg, char *dst_host, char *dst_port, MSG_ID_T id)
{
   msg->msg.id = id;

   strcpy(msg->msg.src.host, "toht");
   strcpy(msg->msg.src.port, dst_port);

   strcpy(msg->msg.dest.host, dst_host);
   strcpy(msg->msg.dest.port, dst_port);
   
   msg->msg.body.length = strlen("sample body");
   strcpy(msg->msg.body.data, "sample body");

   msg->msg.nullterm = 0;
}


/* 
 * DisplayMsg()
 */
void
DisplayMsg( MESSAGE_U_T *msg, char *label)
{
   printf("%s\n", label);
   printf("  msg id        = %d\n", msg->msg.id);
   printf("  msg src host  = %s\n", msg->msg.src.host);
   printf("  msg src port  = %s\n", msg->msg.src.port);
   printf("  msg dst host  = %s\n", msg->msg.dest.host);
   printf("  msg dst port  = %s\n", msg->msg.dest.port);
   printf("  msg body len  = %d\n", msg->msg.body.length);
   printf("  msg body data = %s\n", msg->msg.body.data);
}


/* 
 * WriteMsg()
 */
void
WriteMsg( int sock, MESSAGE_U_T *msg)
{
   int outchars;

   outchars = sizeof(MESSAGE_U_T);

   (void) write(sock, &msg->data[0], outchars);
}


/* 
 * ReadMsg()
 */
void
ReadMsg( int sock, MESSAGE_U_T *msg)
{
   int inchars, outchars;
   int n;

   outchars = sizeof(MESSAGE_U_T);

   for (inchars = 0; inchars < outchars; inchars+=n)
   {
      n = read(sock, &msg->data[inchars], outchars - inchars);
      if (n < 0)
      {
         errexit("socket read failed: %s\n", strerror(errno));
      }
   }
}

/* end of common.c */
