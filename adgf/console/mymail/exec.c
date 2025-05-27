/************************************************************************

  This file contains routines for handling executive function requests.

Author:	Brian Lingard

File:	exec.c

Revision History:
  1.0	5/4/95	originated

************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mymail.h"	 	/* typedefs and defines for this program */



/*  login_executive()
 *
 */
int
login_executive()
{
   char password[BUFLEN];


   printf("\nPlease enter executive password ...\n\n");

   printf("Password: ");
   gets(password);

   /* check if valid executive password entered */


   return(VALID_LOGIN);
} /* end of login_executive() */


/*  HandleExecSelection()
 *
 */
int
HandleExecSelection()
{

   return(0);
} /* end of HandleExecSelection() */



/* end of menus.c */

