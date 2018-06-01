/************************************************************************

  Simple mail program that supports multiple users of a single computer
  which are not on a network.

Author:	Brian Lingard

File:	mymail.c

Usage:	mymail [-u file][-l logfile]

Options:
  -u file   default "userlist"  user list file
  -l file   default "logfile"   debug log file


Revision History:
   0.1 06/18/96 added structure definitions for mail file database
   0.0 05/03/95	originated

************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mymail.h"	 	/* typedefs and defines for this program */


/*  define any globals variables
 */
char userlistname[BUFLEN];
char logfilename[BUFLEN];
char *userlistnameptr;
char *logfilenameptr;



/** MAIN function **/
int 
main(argc, argv)
   int argc;
   char *argv[];
{
   int i;
   int inputflag = FALSE;
   int logflag = FALSE;

   int main_item = MAIN_UNKNOWN;
   int exec_item = EXEC_UNKNOWN;
   int user_item = USER_UNKNOWN;



/* check command line arguments */
   switch(argc) {
     case 1:			/* use defaults */
        sprintf(userlistname, "userlist");
        sprintf(logfilename, "logfile");
        userlistnameptr = &userlistname[0];
        logfilenameptr = &logfilename[0];
        break;
     default:			/* check args and parse */
        if (argc > MAXARGS) {
           fprintf(stderr,"usage: mymail [-u file][-l file]");
           exit(1);
        }
        else {                  /* parse argument inputs */
           i = 1;
           while (i < argc) {
              switch(argv[i][1]) {	/* switch on dash option */

                 case 'u':
                    userlistnameptr = argv[i+1];
                    i++;
                    inputflag = TRUE;
                    break;

                 case 'l':
                    logfilenameptr = argv[i+1];
                    i++;
                    logflag = TRUE;
                    break;

                 default:
                    fprintf(stderr,"Main: unknown option(s) specified");
                    exit(1);
              } /* end inner switch */
              i++;
           } /* end while */
        } /* end else */
     break;
   } /*end outer switch */


   DisplayWelcome();


   while (main_item != MAIN_EXIT) {

      main_item = DisplayMainMenu();


      if (main_item == MAIN_LOGIN) {

         if (login_user() == VALID_LOGIN) {

            while (user_item != USER_QUIT) {

               user_item = DisplayUserMenu();

               HandleUserSelection(user_item);
            }
         }
         else {
            printf("\nUser login failed.\n\n");
         }
      }
      else if (main_item == MAIN_EXEC) {

         if (login_executive() == VALID_LOGIN) {

            while (exec_item != EXEC_QUIT) {

               exec_item = DisplayExecMenu();
 
               HandleExecSelection(exec_item);
            }
         }
         else {
            printf("\nExecutive login failed.\n\n");
         }
      }
      else if (main_item == MAIN_EXIT) {
         printf("\nExiting program\n\n");
      }
      else {
         printf("\nPlease re-enter a valid selection\n\n");
      }

   } /* end while not exit */

   exit(0);
} /* end of main() */


/* end of mymail.c */

