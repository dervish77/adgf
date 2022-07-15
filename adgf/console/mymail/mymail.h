/************************************************************************

 File:		mymail.h

 Author:	Brian Lingard 			  			

 Description:	types and defines for mymail.c

 Revision:	
   0.1 06/18/96 added structure definitions for mail file database
   0.0 05/03/95	originated	

*************************************************************************/

#ifndef _MYMAIL_H
#define _MYMAIL_H


/* check if boolean constants have been defined */
#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif


/*  define some constants 
 */
#define VERSION "1.0"		/* current version number */

#define DEBUG 1			/* general debug flag */


/*  define generic constants 
 */
#define MAXARGS 	5
#define BUFLEN 		128


#define VALID_LOGIN 	1
#define INVALID_LOGIN	0


#define MAIN_UNKNOWN	0
#define MAIN_LOGIN	1
#define MAIN_EXEC	2
#define MAIN_EXIT	3


#define USER_UNKNOWN	0
#define USER_READ	1
#define USER_SEND	2
#define USER_DELETE	3
#define USER_QUIT	4


#define EXEC_UNKNOWN	0
#define EXEC_CREATE	1
#define EXEC_DELETE	2
#define EXEC_QUIT	3


/*  define user name string type
 */
#define USER_NAME_LEN 	BUFLEN
typedef char USER_NAME_T[USER_NAME_LEN];


/*  define subject string type
 */
#define SUBJECT_LEN 	BUFLEN
typedef char SUBJECT_T[SUBJECT_LEN];


/*  define date/time string type -- format "MMM-DD-YYYY - HH:MM:SS"
 */
#define DATE_TIME_LEN 	22
typedef char DATE_TIME_T[DATE_TIME_LEN];


/*  define mail file entry structure type
 */
typedef struct mail_file_entry_s_t {
   USER_NAME_T	recipient;
   USER_NAME_T	sender;
   USER_NAME_T  reply_to;
   SUBJECT_T	subject;
   DATE_TIME_T	time_sent;
   DATE_TIME_T	time_rcvd;
   int		user_id;
   int 		msg_id;
   int		msg_length;	/* in bytes */
   char		*msg_ptr;	/* pointer to start of mail msg buffer */
} MAIL_FILE_ENTRY_S_T;


/*  define mail file structure type
 */
typedef struct mail_file_s_t {
   int			num_entries;
   MAIL_FILE_ENTRY_S_T	*mail_ptr;	/* pointer to mail file entries */
} MAIL_FILE_S_T;



/*  extern any globals
 */
extern char userlistname[BUFLEN];
extern char logfilename[BUFLEN];
extern char *userlistnameptr;
extern char *logfilenameptr;



/*  extern all function prototypes
 */
extern int DisplayWelcome();
extern int DisplayMainMenu();
extern int DisplayUserMenu();
extern int DisplayExecMenu();

extern int login_executive();
extern int HandleExecSelection();

extern int login_user();
extern int ReadUserList();
extern int HandleUserSelection();
extern int ReadUserMailDir(int userid);
extern int ReadUserMailMsg(int userid, int msgid);



#endif /* _MYMAIL_H */

/* end of mymail.h */
