/********************************************************
*  File: tcplib.c                         Date: 3/6/94   
*
*  Rev 3    1/30/96  separated from tcplib.h
*  Rev 2    3/26/94  replaced service name with port number
*  Rev 1    3/7/94   added passive routines
*  Rev 0    3/6/94   Originated
*
*  This file contains library routines for TCP connections
*  using both TCP and UDP protocols.  Refer to the book
*  "Internetworking with TCP/IP Vol 3" by Comer and Stevens
*  for programming details of these routines.
*
*********************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcplib.h"


/*
unsigned short  htons(), ntohs();
*/

unsigned long   inet_addr();

unsigned short  portbase = 0;     /* port base, for non-root servers */



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




/* connectTCP - connect to a specified TCP service on a specified host */

int
connectTCP( char *host, char *port)
/* host - name of host to which connection is desired */
/* port - port associated with the desired port */
{
   return connectsock( host, port, "tcp");
}


/* connectUDP - conenct to a specified UDP service on a specified host */

int
connectUDP( char *host, char *port)
/* host - name of host to which connection is desired */
/* port - service associated with the desired port */
{
   return connectsock( host, port, "udp");
}


/* connectsock - allocate and connect a socket using TCP or UDP */

int
connectsock( char *host, char *port, char *protocol)
/* host     - name of host to which connection is desired */
/* port     - service associated with the desired port */
/* protocol - name of protocol to use ("tcp" or "udp") */
{
   struct hostent    *phe;    /* pointer to host information entry */
   struct servent    *pse;    /* pointer to service information entry */
   struct protoent   *ppe;    /* pointer to protocol information entry */
   struct sockaddr_in   sin;  /* an Internet endpoint address */
   int   s, type;             /* socket descriptor and socket type */
   

#ifdef _USE_BSD
   bzero((char *)&sin, sizeof(sin));
#else
   memset((char *)&sin, 0, sizeof(sin));
#endif

   sin.sin_family = AF_INET;
   
/* map service name to port number */
   sin.sin_port = atoi(port);
      
/* map host name to IP address, allowing for dotted decimal */
#ifdef _USE_BSD
   if ( phe = gethostbyname(host) )
      bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length);
#else
   if ( phe = gethostbyname(host) )
      memcpy((char *)&sin.sin_addr, phe->h_addr, phe->h_length);
#endif
   else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
      errexit("Can't get \"%s\"host entry\n", host);
      
/* map protocol name to protocol number */
   if ( (ppe = getprotobyname(protocol)) == 0)
      errexit("Can't get \"%s\" protocol entry\n", protocol);
      
/* use protocol to choose a socket type */
   if (strcmp(protocol, "udp") == 0)
      type = SOCK_DGRAM;
   else
      type = SOCK_STREAM;
      
/* allocate a socket */
   s = socket(PF_INET, type, ppe->p_proto);
   if (s < 0)
      errexit("Can't create socket: %s\n", sys_errlist[errno]);
      
/* connect the socket */
   if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      errexit("Can't connect to %s.%s: %s\n", host, port, 
                                    sys_errlist[errno]);
   
   return s;
}

   
/* passiveUDP - create a passive socket for use in a UDP server */

int
passiveUDP( char  *port )
/* port - service associated with the desired port */
{
   return passivesock( port, "udp", 0);
}


/* passiveTCP - create a passive socket for use in a TCP server */

int
passiveTCP( char  *port, int qlen )
/* port - service associated with the desired port */
/* qlen - maximum server request queue length */
{
   return passivesock( port, "tcp", qlen);
}


/* passivesock - allocate and bind a server socket using TCP or UDP */

int
passivesock( char *port, char *protocol, int qlen)
/* port     - service associated with the desired port */
/* protocol - name of protocol to use ("tcp" or "udp") */
/* qlen     - maximum length of the server request queue */
{
   struct servent    *pse;    /* pointer to service information entry */
   struct protoent   *ppe;    /* pointer to protocol information entry */
   struct sockaddr_in sin;    /* an Internet endpoint address */
   int   s, type;             /* socket descriptor and socket type */
   
#ifdef _USE_BSD
   bzero((char *)&sin, sizeof(sin));
#else
   memset((char *)&sin, 0, sizeof(sin));
#endif

   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = INADDR_ANY;
   
/* map service port to port number */
   sin.sin_port = atoi(port);
      
/* map protocol name to protocol number */
   if ( (ppe = getprotobyname(protocol)) == 0)
      errexit("Can't get \"%s\" protocol entry\n", protocol);
      
/* use protocol to choose a socket type */
   if (strcmp(protocol, "udp") == 0)
      type = SOCK_DGRAM;
   else
      type = SOCK_STREAM;
      
/* allocate socket */
   s = socket(PF_INET, type, ppe->p_proto);
   if (s < 0)
      errexit("Can't create socket: %s\n", sys_errlist[errno]);
      
/* bind the socket */
   if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      errexit("Can't bind to %s port: %s\n",port,sys_errlist[errno]);
      
   if (type == SOCK_STREAM && listen(s, qlen) < 0)
      errexit("Can't listen on %s port: %s\n",port,sys_errlist[errno]);
      
   return s;
}
   
   


