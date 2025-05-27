/************************************************************************

  Simple mail program that supports multiple users of a single computer
  which are not on a network.

Author:	Brian Lingard

File:	menus.c

Revision History:
  1.0	5/3/95	originated

************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mymail.h"	 	/* typedefs and defines for this program */


/*  DisplayWelcome()
 *
 */
int
DisplayWelcome()
{
   printf("\n");
   printf("***************************************************\n");
   printf("*                                                 *\n");
   printf("*           Welcome to MY MAIL Program            *\n");
   printf("*                                                 *\n");
   printf("*                 Version %s                     *\n", VERSION);
   printf("*                                                 *\n");
   printf("***************************************************\n");

   return(0);
} /* end of DisplayWelcome() */


/*  DisplayMainMenu()
 *
 */
int
DisplayMainMenu()
{
   char selection[BUFLEN];
   int  item;

   printf("\n*************\n");
   printf("\nMain Menu ...\n\n");

   printf(" 1. Login as user\n");
   printf(" 2. Executive functions\n");
   printf("\n 3. Quit program\n");
 
   printf("\nEnter choice: ");
   gets(selection);

   if (strncmp(selection,"1",1) == 0) 
      item = MAIN_LOGIN;
   else if (strncmp(selection,"2",1) == 0) 
      item = MAIN_EXEC;
   else if (strncmp(selection,"3",1) == 0)
      item = MAIN_EXIT;
   else
      item = MAIN_UNKNOWN;

   return(item);
} /* end of DisplayMainMenu() */


/*  DisplayUserMenu()
 *
 */
int
DisplayUserMenu()
{
   char selection[BUFLEN];
   int  item;

   printf("\n*************\n");
   printf("\nUser Menu ...\n\n");

   printf(" 1. Read Mail\n");
   printf(" 2. Send Mail\n");
   printf(" 3. Delete Mail\n");
   printf("\n 4. Quit\n");
 
   printf("\nEnter choice: ");
   gets(selection);

   if (strncmp(selection,"1",1) == 0) 
      item = USER_READ;
   else if (strncmp(selection,"2",1) == 0) 
      item = USER_SEND;
   else if (strncmp(selection,"3",1) == 0)
      item = USER_DELETE;
   else if (strncmp(selection,"4",1) == 0)
      item = USER_QUIT;
   else
      item = USER_UNKNOWN;

   return(item);
} /* end of DisplayUserMenu() */


/*  DisplayExecMenu()
 *
 */
int
DisplayExecMenu()
{
   char selection[BUFLEN];
   int  item;

   printf("\n******************\n");
   printf("\nExecutive Menu ...\n\n");

   printf(" 1. Create Account\n");
   printf(" 2. Delete Account\n");
   printf("\n 3. Quit\n");
 
   printf("\nEnter choice: ");
   gets(selection);

   if (strncmp(selection,"1",1) == 0) 
      item = EXEC_CREATE;
   else if (strncmp(selection,"2",1) == 0) 
      item = EXEC_DELETE;
   else if (strncmp(selection,"3",1) == 0)
      item = EXEC_QUIT;
   else
      item = EXEC_UNKNOWN;

   return(item);
} /* end of DisplayExecMenu() */


/* end of menus.c */

