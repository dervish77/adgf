/***********************************************************************

 Header file for client/server stuff.

   File:  	multi.h

   Author: 	Brian Lingard

   Date:	3/29/96

   Revisions:
	0.0	01/30/98	Originated

***********************************************************************/

#ifndef _MULTI_H
#define _MULTI_H

#ifndef _TCPLIB_H
#include "tcplib.h"
#endif


/* 
 *  server defines
 */
#define QLEN 		5        /* maximum connection queue length */
#define BUFSIZE 	4096


/* 
 *  client defines
 */
#define LINELEN      	128


/*
 *  buffer defines
 */
#define MBUFFER_LEN	80
typedef char MBUFFER_T[MBUFFER_LEN];



/*
 *  port defines 
 */
#define OTHELLO_PORT1	"60010"		/* default port */
#define OTHELLO_PORT2	"70010"		/* alt port 1 */
#define OTHELLO_PORT3	"80010"		/* alt port 2 */


/* 
 *  remote host structure 
 */
typedef struct host_s_t {
   int		client;
   int		server;
   MBUFFER_T	login_name;
   MBUFFER_T	remote_host_ip;
   MBUFFER_T	remote_port;
   int		remote_socket;
} HOST_S_T;



#endif /* _MULTI_H */
/* end of multi.h */
