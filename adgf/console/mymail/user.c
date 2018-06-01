/************************************************************************

  This file contains routines related to handling user requests.

Author:	Brian Lingard

File:	user.c

Revision History:
  1.0	5/4/95	originated

************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mymail.h"	 	/* typedefs and defines for this program */


/*  login_user()
 *
 */
int
login_user()
{
   char username[BUFLEN];
   char password[BUFLEN];

   int error_flag;


   error_flag = ReadUserList();

   if (!error_flag) {
      printf("\nPlease login ...\n\n");

      printf("Username: ");
      gets(username);

      printf("Password: ");
      gets(password);

      /* check if username is in user list */

      /* check if valid password entered */

   }
   else { /* error reading in user list file */
      fprintf(stderr,"Error while reading in user list\n");
      exit(1);
   }

   return(VALID_LOGIN);
} /* end of login_user() */


/*  ReadUserList() - opens the user list file, reads in all records, closes file
 *
 *  format of file:
 *	num_of_users
 *	userid username password
 *	userid username password
 */
int
ReadUserList()
{

   return(FALSE);
} /* end of ReadUserList() */


/*  HandleUserSelection()
 *
 */
int
HandleUserSelection()
{

   return(0);
} /* end of HandleUserSelection() */


/*  ReadUserMailDir() - opens the user mail directory file, reads in all 
 *  	records, closes file
 *
 *  format of file:
 *	num_of_msgs
 *	msgid from_user to_user date time subject
 *
 *  where:
 *	date has format YYMMDD
 *	time has format HHMM
 */
int
ReadUserMailDir(int userid)
{

   return(FALSE);
} /* end of ReadUserMailDir() */


/*  ReadUserMailMsg() - opens the user mail msg file, reads in all 
 *  	contents, closes file
 *
 *  format of file:
 *	msgid
 *	text lines
 */
int
ReadUserMailMsg(int userid, int msgid)
{

   return(FALSE);
} /* end of ReadUserMailMsg() */


/* end of user.c */

