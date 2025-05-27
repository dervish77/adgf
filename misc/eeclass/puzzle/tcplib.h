/********************************************************
*  File: tcplib.h                         Date: 3/6/94   
*
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

#ifdef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif   /* INADDR_NONE */

extern int  errno;
extern char *sys_errlist[];

u_short  htons(), ntohs();
u_long   inet_addr();

u_short  portbase = 0;     /* port base, for non-root servers */


/* connectTCP - connect to a specified TCP service on a specified host */

int
connectTCP( host, port)
   char *host;       /* name of host to which connection is desired */
   char *port;       /* port associated with the desired port */
{
   return connectsock( host, port, "tcp");
}


/* connectUDP - conenct to a specified UDP service on a specified host */

int
connectUDP( host, port)
   char *host;       /* name of host to which connection is desired */
   char *port;    /* service associated with the desired port */
{
   return connectsock( host, port, "udp");
}


/* connectsock - allocate and connect a socket using TCP or UDP */

int
connectsock( host, port, protocol)
   char *host;       /* name of host to which connection is desired */
   char *port;    /* service associated with the desired port */
   char *protocol;   /* name of protocol to use ("tcp" or "udp") */
{
   struct hostent    *phe;    /* pointer to host information entry */
   struct servent    *pse;    /* pointer to service information entry */
   struct protoent   *ppe;    /* pointer to protocol information entry */
   struct sockaddr_in   sin;  /* an Internet endpoint address */
   int   s, type;             /* socket descriptor and socket type */
   
   
   bzero((char *)&sin, sizeof(sin));
   sin.sin_family = AF_INET;
   
/* map service name to port number */
   sin.sin_port = atoi(port);
      
/* map host name to IP address, allowing for dotted decimal */
   if ( phe = gethostbyname(host) )
      bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length);
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
passiveUDP( port )
   char  *port;      /* service associated with the desired port */
{
   return passivesock( port, "udp", 0);
}


/* passiveTCP - create a passive socket for use in a TCP server */

int
passiveTCP( port, qlen )
   char  *port;      /* service associated with the desired port */
   int   qlen;          /* maximum server request queue length */
{
   return passivesock( port, "tcp", qlen);
}


/* passivesock - allocate and bind a server socket using TCP or UDP */

int
passivesock( port, protocol, qlen)
   char  *port;      /* service associated with the desired port */
   char  *protocol;     /* name of protocol to use ("tcp" or "udp") */
   int   qlen;          /* maximum length of the server request queue */
{
   struct servent    *pse;    /* pointer to service information entry */
   struct protoent   *ppe;    /* pointer to protocol information entry */
   struct sockaddr_in sin;    /* an Internet endpoint address */
   int   s, type;             /* socket descriptor and socket type */
   
   bzero((char *)&sin, sizeof(sin));
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
   
   

/* errexit - print an error message and exit */

#include <varargs.h>

int
errexit(format, va_alist)
   char *format;
va_dcl
{
   va_list args;
   va_start(args);
   _doprnt(format, args, stderr);
   va_end(args);
   exit(1);
}

