/********************************************************
*  File: tcplib.h                         Date: 3/6/94   
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

#ifndef _TCPLIB_H
#define _TCPLIB_H

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif   /* INADDR_NONE */

/* comment this define out if not using BSD unix */
/*
  #define _USE_BSD	
*/

extern int  errno;
extern char *sys_errlist[];

/*
extern unsigned short  htons(), ntohs();
*/

extern unsigned long   inet_addr();

extern unsigned short  portbase;     /* port base, for non-root servers */


/* connectTCP - connect to a specified TCP service on a specified host */

extern int connectTCP( char *host, char *port);


/* connectUDP - conenct to a specified UDP service on a specified host */

extern int connectUDP( char *host, char *port);


/* connectsock - allocate and connect a socket using TCP or UDP */

extern int connectsock( char *host, char *port, char *protocol);

   
/* passiveUDP - create a passive socket for use in a UDP server */

extern int passiveUDP( char  *port );


/* passiveTCP - create a passive socket for use in a TCP server */

extern int passiveTCP( char  *port, int qlen );


/* passivesock - allocate and bind a server socket using TCP or UDP */

extern int passivesock( char *port, char *protocol, int qlen);


#endif /* _TCPLIB_H */
