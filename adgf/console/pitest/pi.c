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
 *    0.2   05/15/2025  added new calc methods
 *	  0.1	03/10/98    added support for command line options
 *	  0.0 	11/02/95    originated
 *
 *  Notes:
 *    see https://en.wikipedia.org/wiki/Pi for more info
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "pi.h"



//#define DEBUG



/*  CalcPiNilakantha - calculate and output PI to screen
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
BOOLEAN_T CalcPiNilakantha( int digits )
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


/*  CalcPiGregoryLeibniz - calculate and output PI to screen
 *
 *  method is using the Gregory-Leibniz series
 *
 *  where pi = (4/1)-(4/3)+(4/5)-(4/7)+(4/9)-(4/11)+(4/13)-(4/15) ⋯
 *
 *  Parameters:
 *	digits	- number of digits of PI
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T CalcPiGregoryLeibniz( int digits )
{
   float a;
   float sum = 0.0f;
   int n = 0;
   int doadd = 1;

   #ifdef DEBUG
   printf("%d , %f\n", n, sum);
   #endif
	
   for (n = 1; n <= digits; n=n+2)
   {
	  a = 4.0f / ( (float)n );
	  
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
 *  method is using simple ratio approximation
 *
 *  where pi = 22/7 or 333/106 or 355/113
 *
 *  Parameters:
 *	digits	- number of digits of PI
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T CalcPiDiv( int digits )
{
   float sum = 3.0;
	  
   sum = 355.0f / 113.0f;

   printf("PI = %f\n", sum);

   return(FALSE);
}

/* end of pi.c */
