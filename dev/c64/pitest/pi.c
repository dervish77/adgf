/*****************************************************************************
 *
 *	Test program for calculating PI.
 *
 *	File:	pi.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/02/95
 *
 *	Revs:
 *	  0.1	03/10/98  added support for prep phrase
 *	  0.0 	11/02/95  originated
 *
 *	Usage:	pi [number of digits]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "pi.h"



//#define DEBUG



/*  CalcPi64	- calculate and output PI to screen
 *   
 *  method is using the Nilakantha series
 *
 *  where pi = 3+4/(2·3·4)-4/(4·5·6)+4/(6·7·8)-4/(8·9·10)+4/(10·11·12)-4/(12·13·14) ⋯
 *
 *  Parameters:
 *	digits	- number of digits of PI
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T CalcPi64( int digits )
{
   float a;
   float sum = 3.0f;
   int n = 0;
   int doadd = 1;

   #ifdef DEBUG
   printf("%d , %f\n", n, sum);
   #endif
	
   for (n = 2; n <= digits; n=n+2)
   {
	  a = 4.0f / ( (float)n * (float)(n+1) * (float)(n+2) );
	  
	  if ( doadd )
	  {
		sum = sum + a;
		doadd = 0;
	  }
	  else
	  {
		sum = sum - a;
		doadd = 1;
	  }

	  #ifdef DEBUG
	  printf("%d , %f %f\n", n, a, sum);
	  #endif
   }

   printf("PI = %f\n", sum);

   return(FALSE);
}


/*  CalcPiDiv	- calculate and output PI to screen
 *
 *  Parameters:
 *	digits	- number of digits of PI
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T CalcPiDiv( int digits )
{
   //float a,b;
   float sum = 3.0;
   //int n = 0;
	  
   sum = 22.0f / 7.0f;

   printf("PI = %f\n", sum);

   return(FALSE);
}


/* end of pi.c */
