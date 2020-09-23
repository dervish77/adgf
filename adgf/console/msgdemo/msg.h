/********************************************************
*
* MSG client/server header
*
* File:   msg.h
*
* Rev 0.1  10/03/97  added alternate message port defines
* Rev 0.0  09/24/97  Originated
*
* Author: Brian Lingard
*
*********************************************************/

#ifndef _MSG_H
#define _MSG_H


#define MSG_VERSION	"0.1"



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
 *  common defines
 */
#define MSG_PORT		"50000"		/* default msg port */
#define MSG_PORT2		"60000"		/* alt msg port */
#define MSG_PORT3		"70000"		/* alt msg port */
#define MSG_PORT4		"80000"		/* alt msg port */

#define MSG_HOSTNAME_LEN	20
#define MSG_HOSTPORT_LEN	20
#define MSG_BODY_LEN		64


/* message id type */
typedef enum {
	MSG_NULL = 0,
	MSG_ACK,
	MSG_NACK,
	MSG_ABORT,
	MSG_LOGIN,		/* player login */
	MSG_LOGOUT,		/* player logout */
	MSG_UPDATE,		/* update request */
	MSG_MAP,		/* map update */
	MSG_MOVE,		/* player movement */
	MSG_SCORE		/* score update */
} MSG_ID_T;


/* host structure */
typedef struct host_s_t {
	char 		host[MSG_HOSTNAME_LEN];
	char		port[MSG_HOSTPORT_LEN];
} HOST_S_T;


/* body structure */
typedef struct body_s_t {
	int		length;
	char		data[MSG_BODY_LEN];
} BODY_S_T;


/* message structure */
typedef struct message_s_t {
	MSG_ID_T 	id;
	HOST_S_T	src;
	HOST_S_T	dest;
	BODY_S_T	body;
	char		nullterm;
} MESSAGE_S_T;


/* message union */
typedef union message_u_t {
	char 		data[sizeof(MESSAGE_S_T)];
  	MESSAGE_S_T 	msg;
} MESSAGE_U_T;


#endif /* end _MSG_H */
