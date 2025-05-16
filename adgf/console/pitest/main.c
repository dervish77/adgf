/*****************************************************************************
 *
 *	Test program for calculating PI.
 *
 *	File:	main.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/02/95
 *
 *	Revs:
 *    0.2   05/15/2025  split into main.c, added new calc methods
 *	  0.1	03/10/98    added support for prep phrase
 *	  0.0 	11/02/95    originated
 *
 *	Usage:	pi [-h] [-d | -g | -n] [-i [iterations]]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "pi.h"


//#define DEBUG


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
   int iterations = 10;
   int method = DIV;

   switch (argc)
   {
      case 1:
         fprintf(stderr, "Usage:  %s [-h] [-d | -g | -n] [-i NNN] \n", argv[0]);
         exit(0);

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'h':
                     fprintf(stderr, "Usage:  %s [-h]  [-d | -g | -n] [-i NNN] \n", argv[0]);
                     fprintf(stderr,"    -h      get help\n");
                     fprintf(stderr,"    -i NNN  number of iterations\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'd':
				     method = DIV;
					 break;
					 
                  case 'g':
				     method = GREG;
					 break;
					 
				  case 'n':
				     method = NILAK;
					 break;

                  case 'i':
                     iterations = atoi(argv[i+1]);
                     i++;
                     break;

                  default:
                     fprintf(stderr, "Usage: %s [-h] [-d | -g | -n] [-i NNN] \n", argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */


   /*  calculate pi
    */
   switch(method)
   {
       case GREG:
		  CalcPiGregoryLeibniz( iterations );
	      break;
	   case NILAK:
		  CalcPiNilakantha( iterations );
	      break;
       default:
	      CalcPiDiv( iterations );
		  break;
   }

   exit(0);
}

/* end of main.c */
