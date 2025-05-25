/*****************************************************************************
 *
 *  Utility for generating a binary file with specified number of bytes.
 *
 *	File:	bingen.c
 *
 *	Usage:	bingen [-h] [-n bytes] [-a | -c | -d data] [-o file]
 *
 *	Options:
 *		-h	  - get options help
 *		-n bytes  - num bytes to generate (default "256")
 *		-a        - pattern is alphabetic
 *		-c        - pattern is numeric counting
 *		-d data   - generated data (default "0x00")
 *		-o file   - output file name (default "file.bin")
 *		-s        - suppress verbose output
 *
 *	Date:	08/24/2000
 *
 *	Revisions:
 *	  0.0 08/24/2000  Originated
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


typedef char BOOLEAN_T;

#define MODE_ALPHA	1
#define MODE_COUNT	2
#define MODE_DATA	3


/*  define global variables
 */
int		base = 0;


/*  GenData	- counts bytes in binary file 
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *	size		- num bytes to prepend
 *	data		- prepend data
 *	mode		- pattern mode
 *
 *  RETURNS:
 *	size		- number of bytes converted
 */
int 
GenData(FILE *out_file_p, int size, int data, int mode)
{
   char c = 0;
   int i, count = 0;

   if (mode == MODE_ALPHA)
      c = 0x40;

   for (i = 0; i < size; i++) 
   {
      switch(mode)
      {
         case MODE_ALPHA:
            c++;
            if ( c > 'Z' ) c = 0x41;
            break;

         case MODE_COUNT:
            c++;
            break;

         case MODE_DATA:
            c = (char) data;
            break;

         default:
            fprintf(stderr, "Unknown data mode\n");
            exit(1); 
            break;
      }

      fputc(c, out_file_p);
      count++;
   }

   return(count);
}


/*  main	- main program
 *
 *  PARAMETERS:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  RETURNS:
 *	none
 */
int 
main(int argc, char **argv)
{
   int		i, mode = MODE_DATA, data = 0, size = 0, count;

   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-n bytes] [-a | -c | -d data] [-o file] [-s]\n", argv[0]);
         exit(1);

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'a':
                     mode = MODE_ALPHA;
                     break;

                  case 'c':
                     mode = MODE_COUNT;
                     break;

                  case 'd':
                     data = atoi(argv[i+1]);
                     mode = MODE_DATA;
                     i++;
                     break;

                  case 'h':
                     fprintf(stderr, 
			"Usage:  %s [-h] [-n bytes] [-a | -c | -d data] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -n bytes  num bytes to generate\n");
                     fprintf(stderr,"    -a        alpha data\n");
                     fprintf(stderr,"    -c        counting data\n");
                     fprintf(stderr,"    -d data   binary data\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'o':
                     strcpy(output_file_name, argv[i+1]);
                     i++;
                     break;

                  case 'n':
                     size = atoi(argv[i+1]);
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-d data] [-o file]  [-s]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-d data] [-o file]  [-s]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbingen -- Generating binary file with %d bytes of 0x%02x\n",
	size, data );

   if (verbose) printf("bingen -- opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   count = GenData(out_file_p, size, data, mode);

   if (verbose) printf("bingen -- generated %d bytes\n\n", count);

   fclose(out_file_p);

   exit(0);
}


/* end of bingen.c */
