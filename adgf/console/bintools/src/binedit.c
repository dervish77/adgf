/*****************************************************************************
 *
 *  Utility for generating a binary file with specified number of bytes.
 *
 *	File:	binedit.c
 *
 *	Usage:	binedit [-h] [-n bytes] [-a | -c | -d data] [-o file]
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


/*  GenEdit	- counts bytes in binary file 
 *
 *  PARAMETERS:
 *	out_file_p	- output file pointer
 *	size		- num bytes to edit
 *
 *  RETURNS:
 *	size		- number of bytes converted
 */
int 
GenEdit(FILE *out_file_p, int size)
{
   char data = 0;
   int i, ecount = 0;

   printf("binedit - edit phase, %d bytes:\n", size);

   for (i = 0; i < size; i++) 
   {
	   printf("enter byte: ");
	   scanf("%x", &data);
	  
	   fputc(data, out_file_p);
       ecount++;
   }
   
   printf("ec %d\n", ecount);
   return(ecount);
}


/*  GenData	- counts bytes in binary file 
 *
 *  PARAMETERS:
 *	out_file_p	- output file pointer
 *	size		- num bytes to fill
 *	data		- fill data
 *	mode		- pattern mode
 *
 *  RETURNS:
 *	size		- number of bytes converted
 */
int 
GenData(FILE *out_file_p, int size, int data, int mode)
{
   char c = 0;
   int i, fcount = 0;

   printf("binedit - fill phase, %d bytes:\n", size);

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
      fcount++;
   }

   return(fcount);
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
   int		i, mode = MODE_DATA, data = 0;
   int 		editsize = 0, totalsize = 0, fillsize = 0;
   int		count, count1, count2;

   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   char 	answer;

   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-e bytes] [-n bytes] [-a | -c | -d data] [-o file] [-s]\n", argv[0]);
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
			"Usage:  %s [-h] [-e bytes] [-n bytes] [-a | -c | -d data] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -e bytes  num bytes to edit\n");
                     fprintf(stderr,"    -n bytes  total file size in bytes\n");
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

                  case 'e':
                     editsize = atoi(argv[i+1]);
                     i++;
                     break;

                  case 'n':
                     totalsize = atoi(argv[i+1]);
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-e bytes] [-n bytes] [-d data] [-o file]  [-s]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-e bytes] [-n bytes] [-d data] [-o file]  [-s]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbinedit -- Generating binary file with %d bytes of 0x%02x\n", totalsize, data );

   if (verbose) printf("binedit -- opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   count1 = GenEdit(out_file_p, editsize);

   fillsize = totalsize - editsize;
   count2 = GenData(out_file_p, fillsize, data, mode);

   count = count1 + count2;
   printf("c1 %d c2 %d c %d\n", count1, count2, count);
   
   if (verbose) printf("binedit -- generated %d bytes\n\n", count);

   fclose(out_file_p);
   
   exit(0);
}


/* end of binedit.c */
