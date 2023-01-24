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

#ifndef _PI_H
#include "pi.h"
#endif



#define DEBUG



/*  CalcPi64	- calculate and output PI to screen
 *
 *  Parameters:
 *	digits	- number of digits of PI
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T CalcPi64( int digits )
{
   float a,b;
   float sum = 3.0f;
   int n = 0;

   #ifdef DEBUG
   printf("%d , %f\n", n, sum);
   #endif
	  
   for (n = 1; n <= digits; n++)
   {
	  a = 4.0f / (2.0f * (float)n - 1.0f);
	  b = 4.0f / (2.0f * (float)n + 1.0f);
      sum = sum + a - b;
	  #ifdef DEBUG
	  printf("%d , %f %f %f\n", n, a, b, sum);
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


/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
int main(int argc, char **argv)
{
   int i;
   int numdigits = 10;

   switch (argc)
   {
      case 1:
         fprintf(stderr, "Usage:  %s [-h] [-n NNN] \n", argv[0]);
         exit(1);

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'h':
                     fprintf(stderr, "Usage:  %s [-h] [-n NNN] \n", argv[0]);
                     fprintf(stderr,"    -h      get help\n");
                     fprintf(stderr,"    -n NNN  number of digits\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'n':
                     numdigits = atoi(argv[i+1]);
                     i++;
                     break;

                  default:
                     fprintf(stderr, "Usage: %s [-h] [-n NNN] \n", argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */


   /*  calculate pi
    */
   CalcPi64( numdigits );
   //CalcPiDiv( numdigits );


   exit(0);
}


#if 0
/*  ParseString	- general purpose string parser
 *
 *  Parameters:
 *	string	- pointer to string to be parsed
 *	args	- pointer to parsed array of strings
 *
 *  Returns:
 *	count	- count of substrings in array
 */
int ParseString(char *string, char *args[])
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
#endif

/* end of lang.c */
