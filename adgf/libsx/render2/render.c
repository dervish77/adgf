/***********************************************************************

   File:  	render.c

   Author: 	Brian Lingard

   Date:	6/11/95


***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "render.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif



/* #define RENDER_DEBUG 1
*/


/******************************************************************************
*  ComputeEyeLocation - computes eye location from current longitude,         *
*                       latitude, and zoom values                             *
******************************************************************************/
void 
ComputeEyeLocation(void *data)
{
   MyProgram 	*me=data;

   double 	long_r, lat_r;	/* angle in radians */
   float	range;		/* computed range */

   long_r = DEG2RADS(me->longitude);
   lat_r = DEG2RADS(me->latitude);

   range = DEFAULT_RANGE * (me->zoom / 100);

   me->data.view.eyeloc.x = range * ((float) sin(long_r));

   me->data.view.eyeloc.y = range * ((float) sin(lat_r));

   me->data.view.eyeloc.z = range * ((float) cos(long_r));
}


/******************************************************************************
*  ParseString - parses list of strings into array of strings                 *
******************************************************************************/
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */



/* end of render.c */
